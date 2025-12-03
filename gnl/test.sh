#!/bin/sh

echo "change size? :"
read size
if [ "$size" != "" ]; then
	BUFFER_SIZE="BUFFER_SIZE=$size"
else
	BUFFER_SIZE=""
fi

bonus=""
echo "bonus? [m/b, exit -> e]"
read bonus
if [ "$bonus" != "e" ] && [ "$bonus" != "m" ] && [ "$bonus" != "b" ]; then
	echo "nothing bonus :(  please retry!) "
	exit 1
fi

mode=""
if [ "$bonus" = "b" ]; then
	echo "mode? [read txt-> t, stdin test -> s, multi test -> m, exit -> e]"
	read mode
	if [ "$mode" != "t" ] && [ "$mode" != "s" ] && [ "$mode" != "m" ]; then
		echo "nothing mode :(  please retry!) "
		exit 1
	fi
else
	echo "mode? [read txt-> t, stdin test -> s, exit -> e]"
	read mode
	if [ "$mode" != "t" ] && [ "$mode" != "s" ]; then
		echo "nothing mode :(  please retry!) "
		exit 1
	fi
fi

if [ "$bonus" = "e" ] || [ "$mode" = "e" ]; then
	exit 0
fi

if [ "$mode" = "t" ]; then
	### read text test
	if [ "$bonus" = "b" ]; then
		gcc -Wall -Wextra -Werror -g get_next_line_bonus.c get_next_line_utils_bonus.c .test.c
	else
		gcc -Wall -Wextra -Werror -g get_next_line.c get_next_line_utils.c .test.c
	fi

	while [ $? -eq 0 ]; do
		echo "choose and write test text name"
		echo "$(ls .src/)"
		echo "<< choose target [exit -> e] >>"
		read file

		if [ "$file" = "e" ]; then
			break
		fi

		OS=$(uname)
		if [[ "$OS" == "Linux" ]]; then
			# Linux用の実行
			valgrind --track-origins=yes --track-fds=yes --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./a.out .src/$file
		else
			# macOS用の実行(Linux環境以外だと valgrind が使えないため)
			leaks --atExit -- ./a.out .src/$file
		fi
	done
elif [ "$mode" = "s" ]; then
	### stdin test
	if [ "$bonus" = "b" ]; then
		gcc -Wall -Wextra -Werror -g get_next_line_bonus.c get_next_line_utils_bonus.c .stdintest.c
	else
		gcc -Wall -Wextra -Werror -g get_next_line.c get_next_line_utils.c .stdintest.c
	fi
	# GREEN="\x1b[32m"
	# RESET="\x1b[0m"
	# echo -e "$GREEN<< stdin test >>$RESET"

	while [ $? -eq 0 ]; do
		OS=$(uname)
		if [ "$OS" = "Linux" ]; then
			# Linux用の実行
			valgrind -q --track-origins=yes --track-fds=yes --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./a.out .src/$file
		else
			# macOS用の実行(Linux環境以外だと valgrind が使えないため)
			leaks --atExit -- ./a.out .src/$file
		fi

		echo "exit ? [y/n]"
		read EXIT
		if [ "$EXIT" = "y" ]; then
			break
		fi
	done
else
	### multi file test
	gcc -Wall -Wextra -Werror -g get_next_line_bonus.c get_next_line_utils_bonus.c .runtest.c

	OS=$(uname)
	if [ "$OS" = "Linux" ]; then
		# Linux用の実行
		valgrind -q --track-origins=yes --track-fds=yes --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./a.out
	else
		# macOS用の実行(Linux環境以外だと valgrind が使えないため)
		leaks --atExit -- ./a.out
	fi
fi

# finish test
echo "----finish GNL tester.----"
rm a.out
exit 0