#!/bin/bash
# Simple norm checker script

echo "=== BASIC NORM VALIDATION ==="
echo

# Check line length (max 80 characters)
echo "Checking line length (max 80 chars)..."
long_lines=$(find src/ includes/ -name "*.c" -o -name "*.h" | xargs grep -n ".\{81,\}" || true)
if [ -n "$long_lines" ]; then
    echo "❌ Lines exceeding 80 characters found:"
    echo "$long_lines"
else
    echo "✅ All lines within 80 characters"
fi
echo

# Check function count per file (max 5)
echo "Checking function count per file (max 5)..."
for file in src/*.c; do
    if [ -f "$file" ]; then
        count=$(grep -c "^[a-zA-Z].*(" "$file" || echo "0")
        if [ "$count" -gt 5 ]; then
            echo "❌ $file has $count functions (max 5 allowed)"
        else
            echo "✅ $file has $count functions"
        fi
    fi
done
echo

# Check for trailing spaces
echo "Checking for trailing spaces..."
trailing=$(find src/ includes/ -name "*.c" -o -name "*.h" | xargs grep -n " $" || true)
if [ -n "$trailing" ]; then
    echo "❌ Trailing spaces found:"
    echo "$trailing"
else
    echo "✅ No trailing spaces found"
fi
echo

echo "=== NORM CHECK COMPLETED ==="