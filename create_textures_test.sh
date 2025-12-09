#!/bin/bash

# Script para crear texturas de prueba de diferentes tamaños
cd "$(dirname "$0")"

echo "Creando texturas de prueba de diferentes tamaños..."

python3 << 'PYEOF'
import struct
import zlib

def create_png(filename, width, height, color, pattern=True):
    """Crea un PNG con o sin patrón"""
    
    # Cabecera PNG
    png_header = b'\x89PNG\r\n\x1a\n'
    
    # IHDR chunk
    ihdr_data = struct.pack('>IIBBBBB', width, height, 8, 2, 0, 0, 0)
    ihdr_crc = zlib.crc32(b'IHDR' + ihdr_data)
    ihdr_chunk = struct.pack('>I', 13) + b'IHDR' + ihdr_data + struct.pack('>I', ihdr_crc)
    
    # Crear datos de imagen (RGB sin alfa)
    image_data = b''
    for y in range(height):
        image_data += b'\x00'  # Filter type
        for x in range(width):
            if pattern:
                # Crear patrón de cuadrícula
                factor = 1.0
                if (x // (width // 8) + y // (height // 8)) % 2:
                    factor = 0.7
                pixel_color = tuple(int(c * factor) for c in color[:3])
            else:
                pixel_color = color[:3]
            image_data += bytes(pixel_color)
    
    # Comprimir datos
    compressed = zlib.compress(image_data, 9)
    
    # IDAT chunk
    idat_crc = zlib.crc32(b'IDAT' + compressed)
    idat_chunk = struct.pack('>I', len(compressed)) + b'IDAT' + compressed + struct.pack('>I', idat_crc)
    
    # IEND chunk
    iend_crc = zlib.crc32(b'IEND')
    iend_chunk = struct.pack('>I', 0) + b'IEND' + struct.pack('>I', iend_crc)
    
    # Escribir archivo
    with open(filename, 'wb') as f:
        f.write(png_header + ihdr_chunk + idat_chunk + iend_chunk)

# Crear texturas con diferentes tamaños y patrones más visibles
# Norte: 128x128 - Azul con patrón de ladrillos
create_png('textures/north.png', 128, 128, (40, 80, 200), pattern=True)

# Sur: 256x256 - Rojo con patrón
create_png('textures/south.png', 256, 256, (200, 40, 40), pattern=True)

# Oeste: 64x128 - Verde (rectangular)
create_png('textures/west.png', 64, 128, (40, 200, 40), pattern=True)

# Este: 512x512 - Amarillo/naranja (alta resolución)
create_png('textures/east.png', 512, 512, (220, 180, 40), pattern=True)

print("✓ Texturas de diferentes tamaños creadas:")
print("  - north.png: 128x128 (azul)")
print("  - south.png: 256x256 (rojo)")
print("  - west.png:  64x128 (verde, rectangular)")
print("  - east.png:  512x512 (amarillo, alta res)")
PYEOF

echo ""
echo "Información de las texturas:"
file textures/*.png
