#!/bin/sh
GREEN="\033[32m"
RESET="\033[0m"

CCW="gcc -Wall -Wextra -Werror -g"

### GNL tester setup
printf "%b----start GNL tester.----%b\n" $GREEN $RESET
echo "change size? :"
read size
if [ "$size" != "" ]; then
	BUFFER_SIZE="$size"
else
	BUFFER_SIZE=""
fi

bonus=""
echo "bonus? [m/b, exit -> e]"
read bonus

if [ "$bonus" = "e" ]; then
	printf "%b----finish GNL tester.----%b\n" $GREEN $RESET
	exit 0
fi
if  [ "$bonus" != "m" ] && [ "$bonus" != "b" ]; then
	echo "command ERROR :(   please retry! "
	exit 1
fi

### GNL tester start
if [ "$BUFFER_SIZE" = "" ]; then
	BUFFER_SIZE="10"
fi
echo "<< GNL tester run >>"
while [ $? -eq 0 ]; do
	echo "----------------------------"
	echo "BUFFER_SIZE : $BUFFER_SIZE"
	echo "mode        : $bonus"
	echo "----------------------------"
	
		mode=""
	if [ "$bonus" = "b" ]; then
		echo "choose your test. [read txt-> t, stdin test -> s, multi test -> m, exit -> e]"
		read mode
		if [ "$bonus" = "e" ] || [ "$mode" = "e" ]; then
			exit 0
		fi	
		if [ "$mode" != "t" ] && [ "$mode" != "s" ] && [ "$mode" != "m" ]; then
			echo "nothing mode :(  please retry!) "
			exit 1
		fi
	else
		echo "choose your test. [read txt-> t, stdin test -> s, exit -> e]"
		read mode
		if [ "$bonus" = "e" ] || [ "$mode" = "e" ]; then
			exit 0
		fi
		if [ "$mode" != "t" ] && [ "$mode" != "s" ]; then
			echo "nothing mode :(  please retry!) "
			exit 1
		fi
	fi
	### test section ###
	if [ "$mode" = "t" ]; then
		### read text test
		if [ "$bonus" = "b" ]; then
			echo "$CCW -D BUFFER_SIZE=$BUFFER_SIZE get_next_line_bonus.c get_next_line_utils_bonus.c .test_bonus.c"
			$CCW -D BUFFER_SIZE=$BUFFER_SIZE get_next_line_bonus.c get_next_line_utils_bonus.c .test_bonus.c
			echo "compile status: $?"
		else
			echo "$CCW -D BUFFER_SIZE=$BUFFER_SIZE get_next_line.c get_next_line_utils.c .test.c"
			$CCW -D BUFFER_SIZE=$BUFFER_SIZE get_next_line.c get_next_line_utils.c .test.c
			echo "compile status: $?"
		fi

		while [ $? -eq 0 ]; do
			echo
			echo "choose and write test text name"
			echo "-------------------------------"
			echo "$(ls .src/ | sed 's/\.txt$//g')"
			echo
			echo "-- choose target [exit -> e] --"
			read file

			if [ "$file" = "e" ]; then
				break
			fi

			OS=$(uname)
			if [ "$OS" = "Linux" ]; then
				# Linux用の実行
				valgrind -q \
				--track-origins=yes \
				--track-fds=yes \
				--leak-check=full \
				--show-leak-kinds=all \
				--errors-for-leak-kinds=all \
				./a.out .src/$file.txt
			else
				# macOS用の実行(Linux環境以外だと valgrind が使えないため)
				leaks --atExit -- ./a.out .src/$file.txt
			fi
		done
	elif [ "$mode" = "s" ]; then
		### stdin test
		if [ "$bonus" = "b" ]; then
			echo "$CCW -D BUFFER_SIZE=$BUFFER_SIZE get_next_line_bonus.c get_next_line_utils_bonus.c .stdintest_bonus.c"
			$CCW -D BUFFER_SIZE=$BUFFER_SIZE get_next_line_bonus.c get_next_line_utils_bonus.c .stdintest_bonus.c
			echo "compile status: $?"
		else
			echo "$CCW -D BUFFER_SIZE=$BUFFER_SIZE get_next_line.c get_next_line_utils.c .stdintest.c"
			$CCW -D BUFFER_SIZE=$BUFFER_SIZE get_next_line.c get_next_line_utils.c .stdintest.c
			echo "compile status: $?"
		fi

		while [ $? -eq 0 ]; do
			OS=$(uname)
			if [ "$OS" = "Linux" ]; then
				# Linux用の実行
				valgrind -q \
				--track-origins=yes \
				--track-fds=yes \
				--leak-check=full \
				--show-leak-kinds=all \
				--errors-for-leak-kinds=all ./a.out
			else
				# macOS用の実行(Linux環境以外だと valgrind が使えないため)
				leaks --atExit -- ./a.out
			fi

			echo "exit ? [y/n]"
			read EXIT
			if [ "$EXIT" = "y" ]; then
				break
			fi
		done
	else
		### multi file test
		echo "$CCW -D BUFFER_SIZE=$BUFFER_SIZE get_next_line_bonus.c get_next_line_utils_bonus.c .runtest.c"
		$CCW -D BUFFER_SIZE=$BUFFER_SIZE get_next_line_bonus.c get_next_line_utils_bonus.c .runtest.c
		echo "compile status: $?"

		OS=$(uname)
		if [ "$OS" = "Linux" ]; then
			# Linux用の実行
			valgrind -q --track-origins=yes --track-fds=yes --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./a.out
		else
			# macOS用の実行(Linux環境以外だと valgrind が使えないため)
			leaks --atExit -- ./a.out
		fi
	fi

	echo
	echo "any other tests to do? [y/n]"
	read EXIT
	if [ "$EXIT" = "n" ]; then
		break
	fi
done
# finish test
printf "%b----finish GNL tester.----%b\n" $GREEN $RESET
rm a.out
exit 0