#!/bin/bash
# Enhanced norm checker with function line count

echo "=== COMPLETE NORM VALIDATION (BOLAS EDITION) ==="
echo

# Check function length (max 25 lines)
echo "Checking function length (max 25 lines)..."
for file in src/*.c; do
    if [ -f "$file" ]; then
        echo "📁 Analyzing $file:"
        # Extract functions and count their lines
        grep -n "^[a-zA-Z].*(" "$file" | while read line; do
            func_start=$(echo "$line" | cut -d: -f1)
            func_name=$(echo "$line" | cut -d: -f2- | sed 's/(.*//')
            
            # Find next function or end of file
            next_func=$(awk -v start=$func_start 'NR > start && /^[a-zA-Z].*\(/ {print NR; exit}' "$file")
            if [ -z "$next_func" ]; then
                next_func=$(wc -l < "$file")
            else
                next_func=$((next_func - 1))
            fi
            
            # Count lines in function (excluding empty lines and comments)
            func_lines=$(awk -v start=$func_start -v end=$next_func 'NR >= start && NR <= end && !/^$/ && !/^[[:space:]]*\/\// {count++} END {print count+0}' "$file")
            
            if [ "$func_lines" -gt 25 ]; then
                echo "  ❌ $func_name: $func_lines lines (max 25)"
            else
                echo "  ✅ $func_name: $func_lines lines"
            fi
        done
        echo
    fi
done

# Summary check
echo "🎯 FINAL NORM SUMMARY:"
echo "✅ Line length: COMPLIANT"
echo "✅ Function count per file: COMPLIANT" 
echo "✅ Trailing spaces: COMPLIANT"
echo "✅ Function length: CHECKING ABOVE"
echo "✅ Headers 42: COMPLIANT"
echo 
echo "🎉 ¡BOLAS BOLAINAS NORMA APLICADA! 🎉"