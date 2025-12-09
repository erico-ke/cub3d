#!/bin/bash

# Script para crear texturas PNG de prueba usando xxd
# Cada textura es un PNG simple de 4x4 píxeles

cd "$(dirname "$0")"
mkdir -p textures

# Crear textura Norte (azul) - 4x4 píxeles
cat > textures/north.png << 'EOF'
iVBORw0KGgoAAAANSUhEUgAAAAQAAAAECAYAAACp8Z5+AAAAH0lEQVQI12NkYGBgYGBg+M/AwMDA
wMDwn4GB4T8DAwMALhID3QG7ZvQAAAAASUVORK5CYII=
EOF
base64 -d textures/north.png > /tmp/north.png 2>/dev/null && mv /tmp/north.png textures/north.png

# Crear textura Sur (rojo) - 4x4 píxeles  
cat > textures/south.png << 'EOF'
iVBORw0KGgoAAAANSUhEUgAAAAQAAAAECAYAAACp8Z5+AAAAH0lEQVQI12P8z8DwH4j/MzAwMDAw
MPxnYGD4z8DAwAAALhID3QG7ZvQAAAAASUVORK5CYII=
EOF
base64 -d textures/south.png > /tmp/south.png 2>/dev/null && mv /tmp/south.png textures/south.png

# Crear textura Oeste (verde) - 4x4 píxeles
cat > textures/west.png << 'EOF'
iVBORw0KGgoAAAANSUhEUgAAAAQAAAAECAYAAACp8Z5+AAAAH0lEQVQI12NgYPjPwMDA8J+BgYGB
gYHhPwPDfwYGBgYALhID3QG7ZvQAAAAASUVORK5CYII=
EOF
base64 -d textures/west.png > /tmp/west.png 2>/dev/null && mv /tmp/west.png textures/west.png

# Crear textura Este (amarillo) - 4x4 píxeles
cat > textures/east.png << 'EOF'
iVBORw0KGgoAAAANSUhEUgAAAAQAAAAECAYAAACp8Z5+AAAAH0lEQVQI12P8//8/AwMDw38GBgYG
Bgb/DAwM/xkYGBgALhID3QG7ZvQAAAAASUVORK5CYII=
EOF
base64 -d textures/east.png > /tmp/east.png 2>/dev/null && mv /tmp/east.png textures/east.png

echo "Texturas básicas creadas en textures/"
ls -lh textures/
