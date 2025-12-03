#!/bin/sh
GREEN="\033[32m"
RESET="\033[0m"

### ft_printf tester setup
printf "%b----start ft_printf tester.----%b\n" $GREEN $RESET

mode=""

echo "mode ? [m/b  e->exit]"
read mode

if [ "$mode" = "e" ]; then
    printf "%b----finish ft_printf tester.----%b\n" $GREEN $RESET
    exit 0
fi

if [ "$mode" = "m" ]; then
    mode="all"
else
    mode="bonus"
fi

### make test
echo
printf "%b<< make file check >>%b\n" $GREEN $RESET
echo "make ft_printf in $mode mode... 3 times"
echo
if [ "$mode" = "all" ]; then
    make all
    make all
    make all
else
    make bonus
    make bonus
    make bonus
fi
if [ $? -ne 0 ]; then
    echo "Make failed. Exiting."
    exit 1
fi

while [ $? -eq 0 ]; do
	echo "----------------------------"
	echo "mode        : $mode"
	echo "----------------------------"
    echo "<< choose your test >>"
    echo "1 : main test"
    echo "2 : custom test (only one value)"
    echo "3 : strict case test"
    echo "other -> exit"
    echo "----------------------------"
    read test
    echo

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
        if [ $? -ne 0 ]; then
            echo "Link failed. Exiting."
            exit 1
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
    elif [ "$test" = "2" ]; then
    ### custom test
        if [ "$mode" = "all" ]; then
            echo "compiling custom test on Mandatory..."
            cc -g -Wall -Wextra -Wall .test.c libftprintf.a
        else
            echo "compiling custom test on Bonus..."
            cc -g -Wall -Wextra -Wall .test_bonus.c libftprintf.a
        fi
        if [ $? -ne 0 ]; then
            echo "Link failed. Exiting."
            exit 1
        fi
        echo "-------------------------------------"
        while true; do 
            echo "Input format string [end -> 'exit']: "
            read input

            if [ "$input" = "exit" ]; then
                break
            fi

            echo "Input value: " 
            read value           
            valgrind -q --leak-check=full ./a.out "$input" "$value"
        done
    elif [ "$test" = "3" ]; then
    ### strict case test
        # ERROR write case
        if [ "$mode" = "all" ]; then
            echo "compiling ERROR write case test on Mandatory..."
            cc -g -Wall -Wextra -Wall --whole-file .errormain.c libftprintf.a
        else
            echo "compiling ERROR write case test on Bonus..."
            cc -g -Wall -Wextra -Wall --whole-file .errormain_bonus.c libftprintf.a
        fi
        if [ $? -ne 0 ]; then
            echo "Link failed. Exiting."
            exit 1
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

        # HUGE value case
        echo
        if [ "$mode" = "all" ]; then
            echo "compiling huge value case test on Mandatory..."
            cc -g -Wall -Wextra -Wall --whole-file .hugemain.c libftprintf.a
        else
            echo "compiling huge value case test on Bonus..."
            cc -g -Wall -Wextra -Wall --whole-file .hugemain_bonus.c libftprintf.a
        fi
        if [ $? -ne 0 ]; then
            echo "Link failed. Exiting."
            exit 1
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
    else
    ### exit
        make fclean
        printf "%b----finish ft_printf tester.----%b\n" $GREEN $RESET
        exit 0
    fi
done

make fclean
rm a.out
printf "%b----finish ft_printf tester.----%b\n" $GREEN $RESET