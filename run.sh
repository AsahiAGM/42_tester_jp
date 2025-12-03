#!/bin/sh 

echo "
===========================================
                42 tester
===========================================
"
echo "TEST_DIR=" > testenv.txt

echo "What is the name to the directory you want to review?"
read DIR

find ../"$DIR" || { echo "Directory not found. Exiting."; exit 1; }
sed -i '' "s/^TEST_DIR=.*$/TEST_DIR=\"../$DIR\"/" testenv.txt

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