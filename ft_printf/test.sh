#!/bin/sh
mode=""

echo "mode ? [m/b  e->exit]"
read mode

if [ "$mode" = "m" ]; then
    mode="all"
else
    mode="bonus"
fi
if [ "$mode" = "e" ]; then
    exit
fi

if [ "$mode" = "all" ]; then
    make -s all
else
    make -s bonus
fi
if [ $? -ne 0 ]; then
    echo "Make failed. Exiting."
    exit 1
fi

echo "<< choose your test >>"
echo "1 : main test"
echo "2 : custom test (only one value)"
echo "3 : strict case test"
echo "other -> exit"
read test

### maintest
if [ "$test" = "1" ]; then
    echo "compiling main test..."
    if [ "$mode" = "all" ]; then
        echo "compiling custom test on Mandatory..."
        cc -g -Wall -Wextra -Wall .main.c libftprintf.a
    else
        echo "compiling custom test on Bonus..."
        cc -g -Wall -Wextra -Wall .main_bonus.c libftprintf.a
    fi
    if [ "$(uname)" = "Linux" ]; then
		# Linux用の実行
		valgrind -q \
        --track-origins=yes \
        --track-fds=yes \
        --leak-check=full \
        --show-leak-kinds=all \
        --errors-for-leak-kinds=all \
        ./a.out
        # -q ... error時以外の出力を抑制
        # --track-origins=yes ... 未初期化メモリを使った場合に、どこでその値が生成されたかを追跡
        # --track-fds=yes ... ファイルディスクリプタの開閉を追跡
        # --leak-check=full ... メモリリークを詳細にチェック。どこでメモリが解放されなかったかを表示する
        # --show-leak-kinds=all ... リークの種類をすべて表示。[definite]未解放 [indirect]間接的リーク など
        # --errors-for-leak-kinds=all ... 指定した種類のリークがある場合、終了コードを非ゼロに設定
	else
		# macOS用の実行(Linux環境以外だと valgrind が使えないため)
		leaks --atExit -- ./a.out
	fi
    make fclean
    rm a.out
    exit 0
elif [ "$test" = "2" ]; then
### custom test
    if [ "$mode" = "all" ]; then
        echo "compiling custom test on Mandatory..."
        cc -g -Wall -Wextra -Wall .test.c libftprintf.a
    else
        echo "compiling custom test on Bonus..."
        cc -g -Wall -Wextra -Wall .test_bonus.c libftprintf.a
    fi
elif [ "$test" = "3" ]; then
### strict case test
    if [ "$mode" = "all" ]; then
        echo "compiling strict case test on Mandatory..."
        cc -g -Wall -Wextra -Wall --whole-file .errormain.c libftprintf.a
    else
        echo "compiling strict case test on Bonus..."
        cc -g -Wall -Wextra -Wall --whole-file .errormain_bonus.c libftprintf.a
    fi
    if [ "$(uname)" = "Linux" ]; then
		# Linux用の実行
		valgrind -q \
        --track-origins=yes \
        --track-fds=yes \
        --leak-check=full \
        --show-leak-kinds=all \
        --errors-for-leak-kinds=all \
        ./a.out
        # -q ... error時以外の出力を抑制
        # --track-origins=yes ... 未初期化メモリを使った場合に、どこでその値が生成されたかを追跡
        # --track-fds=yes ... ファイルディスクリプタの開閉を追跡
        # --leak-check=full ... メモリリークを詳細にチェック。どこでメモリが解放されなかったかを表示する
        # --show-leak-kinds=all ... リークの種類をすべて表示。[definite]未解放 [indirect]間接的リーク など
        # --errors-for-leak-kinds=all ... 指定した種類のリークがある場合、終了コードを非ゼロに設定
	else
		# macOS用の実行(Linux環境以外だと valgrind が使えないため)
		leaks --atExit -- ./a.out
	fi
    make fclean
    rm a.out
    exit 0
else
    make fclean
    exit 0
fi

if [ $? -ne 0 ]; then
    echo "Link failed. Exiting."
    exit 1
fi

while true; do
    echo "Input format string [end -> 'exit']: "
    read input

    if [ "$input" = "exit" ]; then
        make fclean
        rm a.out
        exit 0
    fi

    echo "Input value: " 
    read value
    
    valgrind -q --leak-check=full ./a.out "$input" $value
    echo
done