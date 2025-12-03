#!/bin/sh 

echo "
===========================================
                42 tester
===========================================
"

PWD=$(pwd)

echo "What is the name to the directory you want to review?"
find .. -maxdepth 1 -mindepth 1 -type d ! -name "*.*" -printf '%f\n'
echo "--------------------------------------------"
read DIR

if [ ! -d "../$DIR" ]; then
	echo "Directory not found. Exiting."
	exit 1
fi

#echo "TEST_DIR=" > testenv.txt
#sed -i "s|^TEST_DIR=.*$|TEST_DIR=\"$PWD/$DIR\"|g" testenv.txt

echo "choose project ? [exit -> e]"
echo 
find . -maxdepth 1 -mindepth 1 -type d ! -name "*.*" -printf '%f\n'
echo "--------------------------------------------"
read TESTER

echo "do test on: $TESTER"

if [ "$TESTER" = "e" ]; then
    exit 0
fi

if [ ! -d "$TESTER" ]; then
    echo "No such tester. Exiting."
    exit 1
fi

# copy projects
mkdir tmp
cp -Rp ../$DIR/. tmp/
cp -Rp $TESTER/. tmp/
cd tmp

# run test
ls -la
sh test.sh

# exit
cd ..
rm -rf tmp