#!/bin/sh
echo "
===========================================
                42 tester
===========================================
"
echo "choose project ? [exit -> e]"
find 42_tester -maxdepth 1 -mindepth 1 -type d ! -name "*.*" -printf '%f\n'
read TESTER

echo "do test on: $TESTER"

if [ "$TESTER" = "e" ]; then
    exit 0
fi

if [ ! -d "42_tester/$TESTER" ]; then
    echo "No such tester. Exiting."
    exit 1
fi

sh "42_tester/$TESTER/test.sh"