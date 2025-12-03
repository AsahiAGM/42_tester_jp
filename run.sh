#!/bin/sh 
GREEN="\033[32m"
RESET="\033[0m"

echo "
======================================================
                      42 tester
======================================================
"

PWD=$(pwd)

echo "What is the name to the directory you want to review?"
echo "-------------"
find .. -maxdepth 1 -mindepth 1 -type d ! -name "*.*" -printf '%f\n'
echo "-------------"
read DIR

if [ ! -d "../$DIR" ]; then
	echo "Directory not found. Exiting."
	exit 1
fi

#echo "TEST_DIR=" > testenv.txt
#sed -i "s|^TEST_DIR=.*$|TEST_DIR=\"$PWD/$DIR\"|g" testenv.txt

echo
echo "choose project ? [exit -> e]"
echo "-------------"
find . -maxdepth 1 -mindepth 1 -type d ! -name "*.*" -printf '%f\n'
echo "-------------"
read TESTER

echo
printf "%bdo test on: %s%b\n" $GREEN "$TESTER" $RESET

if [ "$TESTER" = "e" ]; then
    exit 0
fi

if [ ! -d "$TESTER" ]; then
    echo "No such tester. Exiting."
    exit 1
fi

# copy projects and norminette
mkdir tmp
cp -Rp ../$DIR/. tmp/
cp -Rp $TESTER/. tmp/
cd tmp
echo
echo "<<run norminette...>>"
norminette .

# run test
echo
sh test.sh

# exit
cd ..
rm -rf tmp