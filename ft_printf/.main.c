#include <stdio.h>
#include <stdlib.h>
#include "ft_printf.h" // for mandatory
//#include "ft_printf_bonus.h" // for bonus
#include <limits.h>

int	main(void)
{

	int *buf = calloc(1,sizeof(int));
	int *buf2 = malloc(0);
	int len = 0;

	printf("// Mandatroy tests\n");
	printf("----- printf -----\n");
	len = printf("Hello, world!! "); printf(" %d\n", len);
	len = printf("%c", 'a'); printf(" %d\n", len);
	len = printf("%s", "Hello"); printf(" %d\n", len);
	len = printf("%s", ""); printf(" %d\n", len);
	len = printf("%p", buf); printf(" %d\n", len);
	len = printf("%p", buf2); printf(" %d\n", len);
	len = printf("%p", NULL); printf(" %d\n", len);
	len = printf("%p", (void *)0); printf(" %d\n", len);
	len = printf("%d", 12345); printf(" %d\n", len);
	len = printf("%i", -42); printf(" %d\n", len);
	len = printf("%i", INT_MIN); printf(" %d\n", len);
	len = printf("%u", 2025); printf(" %d\n", len);
	len = printf("%u", -2025); printf(" %d\n", len);
	len = printf("%x", 0xFF); printf(" %d\n", len);
	len = printf("%x", 0x0); printf(" %d\n", len);
	len = printf("%X", 0xFF); printf(" %d\n", len);
	len = printf("%X", 0x0); printf(" %d\n", len);
	len = printf("%%"); printf(" %d\n", len);
	//len = printf("%"); printf(" %d\n", len); // 本家の”単体%”は静的エラーでコンパイル時にエラーを出す
	//len = printf("%f", 3.14159265359); printf(" %d\n", len);  //f は今回作らない
	//len = printf("%%%"); printf(" %d\n", len); // 奇数個の％はコンパイルエラー
	len = printf("Mixed: char=%c, str=%s, ptr=%p, int=%d, uint=%u, hex=%x, HEX=%X, percent=%%", 'Z', "Test", buf, -123, 456U, 0xabc, 0xDEF);
	printf("\n %d\n", len);
	printf("\n----- ft_printf -----\n");
	len = ft_printf("Hello, world!! "); printf(" %d\n", len);
	len = ft_printf("%c", 'a'); printf(" %d\n", len);
	len = ft_printf("%s", "Hello"); printf(" %d\n", len);
	len = ft_printf("%s", ""); printf(" %d\n", len);
	len = ft_printf("%p", buf); printf(" %d\n", len);
	len = ft_printf("%p", buf2); printf(" %d\n", len);
	len = ft_printf("%p", NULL); printf(" %d\n", len);
	len = ft_printf("%p", (void *)0); printf(" %d\n", len);
	len = ft_printf("%d", 12345); printf(" %d\n", len);
	len = ft_printf("%i", -42); printf(" %d\n", len);
	len = ft_printf("%i", INT_MIN); printf(" %d\n", len);
	len = ft_printf("%u", 2025); printf(" %d\n", len);
	len = ft_printf("%u", -2025); printf(" %d\n", len);
	len = ft_printf("%x", 0xFF); printf(" %d\n", len);
	len = ft_printf("%x", 0x0); printf(" %d\n", len);
	len = ft_printf("%X", 0xFF); printf(" %d\n", len);
	len = ft_printf("%X", 0x0); printf(" %d\n", len);
	len = ft_printf("%%"); printf(" %d\n", len);
	printf("(ft only, 'only %%')\n"); fflush(stdout);
	len = ft_printf("%"); printf(" %d\n", len); // 静的エラーにできないので未定義動作ハンドリング
	//len = ft_printf("%f", 3.14159265359); printf(" %d\n", len);
	printf("(ft only, 'odd %%') \n"); fflush(stdout);
	len = ft_printf("%%%"); printf(" %d\n", len); // 静的エラーにできないので未定義動作ハンドリング
	//mixed test
	len = ft_printf("Mixed: char=%c, str=%s, ptr=%p, int=%d, uint=%u, hex=%x, HEX=%X, percent=%%", 'Z', "Test", buf, -123, 456U, 0xabc, 0xDEF);
	printf("\n %d\n<with ERR>\n", len);
	len = ft_printf("Mixed: char=%c, str=%s, ptr=%p, int=%d, uint=%u, hex=%x, HEX=%X, percent=%%, err=%%%", 'Z', "Test", buf, -123, 456U, 0xabc, 0xDEF);
	printf("\n %d\n", len);

	printf("\n\n// BONUS tests\n");
	// flags, width, precision, length modifiers tests can be added here
	len = printf("----- printf -----\n");
	len = printf("|%8d|", 42); printf("  (%d)\n", len);// Example of left-justified and precision
	len = printf("|%-8d|", 42); printf("  (%d)\n", len);// Example of left-justified
	//len = printf("|%08.3d|", 42); printf("  (%d)\n", len);// Example of no zero-padding and precision 静的エラー
	len = printf("|%08u|", 42); printf("  (%d)\n", len);// Example of zero-padding
	len = printf("|%-8s|", "left"); printf("  (%d)\n", len);// Example of left-justified string
	len = printf("%.5s|", "truncate"); printf("  (%d)\n", len);// Example of string precision
	len = printf("%.2s|", "a"); printf("  (%d)\n", len);// Example of string precision
	len = printf("%#.7x", 65535); printf("  (%d)\n", len);// precision for hex
	len = printf("%#.7X", 65535); printf("  (%d)\n", len);// precision for HEX
	len = printf("|%p|", buf); printf("  (%d)\n", len);
	len = printf("|%20p|", buf); printf("  (%d)\n", len);// Example of pointer with width
	len = printf("|%15p|", NULL);  printf("  (%d)\n", len);
	len = printf("|%-15p|", NULL);  printf("  (%d)\n", len);// NULL pointer
	len = printf("%#x", 255); printf("  (%d)\n", len);// Example of add header for hex 
	len = printf("%#X", 255); printf("  (%d)\n", len);// Example of add header for HEX
	// len = printf("%#d", 255); printf("  (%d)\n", len);// # affect only x or X [KO]
	// len = printf("%#u", 255); printf("  (%d)\n", len);// # affect only x or X [KO]
	len = printf("%#x", 0); printf("  (%d)\n", len);// ０ no header
	len = printf("%#X", 0); printf("  (%d)\n", len);// ０ no header
	len = printf("|% d|", 42); printf("  (%d)\n", len);  // => | 42|  add space
	len = printf("|% d|", -42); printf("  (%d)\n", len); // => |-42|  prioritize sign
	len = printf("|%+d|", 42); printf("  (%d)\n", len);  // => |+42|  add plus
	len = printf("|%+d|", -42); printf("  (%d)\n", len); // => |-42|  prioritize sign
	//%[flags][width][.precision][length]specifier
	// len = printf("mix: |%#- +08.5x|", 255); printf("  (%d)\n", len);//
	// len = printf("mix: |%- +0#8.5x|", 255); printf("  (%d)\n", len);//
	// len = printf("mix: |% +0#-8.5x|", 255); printf("  (%d)\n", len);//
	// len = printf("mix: |%+0#- 8.5x|", 255); printf("  (%d)\n", len);//
	// len = printf("mix: |%0#- +8.5x|", 255); printf("  (%d)\n", len);//
	// len = printf("mix: |%0# +8.5k%|", 255); printf("  (%d)\n", len);//[KO]　出力無し
	// len = printf("mix: |% -  1d|", 123); printf("  (%d)\n", len);
	// len = printf("mix: |% -  2d|", 123); printf("  (%d)\n", len);
	// len = printf("mix: |% -  3d|", 123); printf("  (%d)\n", len);
	// len = printf("mix: |% -  4d|", 123); printf("  (%d)\n", len); //[KO]　記号と数字の間にスペース
	// len = printf("mix: |% +  1d|", 123); printf("  (%d)\n", len);
	// len = printf("mix: |% +  2d|", 123); printf("  (%d)\n", len);
	// len = printf("mix: |% +  3d|", 123); printf("  (%d)\n", len);
	// len = printf("mix: |% +  4d|", 123); printf("  (%d)\n", len); //[KO]　記号と数字の間にスペース
	// len = printf("mix: |% -  5d|", 123); printf("  (%d)\n", len); //[KO]　最後のスペース１個多い
	// len = printf("mix: |%-   5d|", 123); printf("  (%d)\n", len); //[KO]　最後のスペース１個多い
	// len = printf("mix: |% +  5d|", 123); printf("  (%d)\n", len); //[KO]　記号の間にスペース
	// len = printf("mix: |%+   5d|", 123); printf("  (%d)\n", len); //[KO]　記号の間にスペース
	// len = printf("mix: |%+   5%d|", 123); printf("  (%d)\n", len);

	printf("\n----- ft_printf -----\n");
	len = ft_printf("|%8d|", 42);  printf("  (%d)\n", len);// Example of left-justified and precision
	len = ft_printf("|%-8d|", 42);  printf("  (%d)\n", len);// Example of left-justified
	//len = ft_printf("|%08.3d|", 42);  printf("  (%d)\n", len);// Example of no zero-padding and precision
	len = ft_printf("|%08u|", 42);  printf("  (%d)\n", len);// Example of zero-padding
	len = ft_printf("|%-8s|", "left");  printf("  (%d)\n", len);// Example of left-justified string
	len = ft_printf("%.5s|", "truncate");  printf("  (%d)\n", len);// Example of string precision
	len = ft_printf("%.2s|", "a");  printf("  (%d)\n", len);// Example of string precision
	len = ft_printf("%#.7x", 65535);  printf("  (%d)\n", len);// precision for hex
	len = ft_printf("%#.7X", 65535);  printf("  (%d)\n", len);// precision for HEX
	len = ft_printf("|%p|", buf);  printf("  (%d)\n", len);
	len = ft_printf("|%20p|", buf);  printf("  (%d)\n", len);// Example of pointer with width
	len = ft_printf("|%15p|", NULL);  printf("  (%d)\n", len);
	len = ft_printf("|%-15p|", NULL);  printf("  (%d)\n", len);// NULL pointer
	len = ft_printf("%#x", 255);  printf("  (%d)\n", len);// Example of add header for hex
	len = ft_printf("%#X", 255);  printf("  (%d)\n", len);// Example of add header for HEX
	// len = ft_printf("%#d", 255);  printf("  (%d)\n", len);// # affect only x or X
	// len = ft_printf("%#u", 255);  printf("  (%d)\n", len);// # affect only x or X
	len = ft_printf("%#x", 0);  printf("  (%d)\n", len);// ０ no header
	len = ft_printf("%#X", 0);  printf("  (%d)\n", len);// ０ no header
	len = ft_printf("|% d|", 42); printf("  (%d)\n", len);  // => | 42|  add space
	len = ft_printf("|% d|", -42);  printf("  (%d)\n", len); // => |-42|  prioritize sign
	len = ft_printf("|%+d|", 42);  printf("  (%d)\n", len);   // => |+42|  add plus
	len = ft_printf("|%+d|", -42); printf("  (%d)\n", len); // => |-42|  prioritize sign
	// %[flags][width][.precision][length]specifier
	printf("mix: \n");
	len = ft_printf("|%#- +08.5x|", 255); printf("  (%d)\n", len);
	len = ft_printf("|%- +0#8.5x|", 255); printf("  (%d)\n", len);
	len = ft_printf("|% +0#-8.5x|", 255); printf("  (%d)\n", len);
	len = ft_printf("|%+0#- 8.5x|", 255); printf("  (%d)\n", len);
	len = ft_printf("|%0#- +8.5x|", 255); printf("  (%d)\n", len);
	// len = ft_printf("|%0# +8.5k%|", 255); printf("  (%d)\n", len);
	len = ft_printf("|% -  1d|", 123);  printf("  (%d)\n", len);
	len = ft_printf("|% -  2d|", 123);  printf("  (%d)\n", len);
	len = ft_printf("|% -  3d|", 123);  printf("  (%d)\n", len);
	len = ft_printf("|% -  4d|", 123);  printf("  (%d)\n", len);
	len = ft_printf("|% +  1d|", 123);  printf("  (%d)\n", len);
	len = ft_printf("|% +  2d|", 123);  printf("  (%d)\n", len);
	len = ft_printf("|% +  3d|", 123);  printf("  (%d)\n", len);
	len = ft_printf("|% +  4d|", 123);  printf("  (%d)\n", len);
	len = ft_printf("|% -  5d|", 123);  printf("  (%d)\n", len);
	len = ft_printf("|%-   5d|", 123);  printf("  (%d)\n", len);
	len = ft_printf("|% +  5d|", 123);  printf("  (%d)\n", len);
	len = ft_printf("|%+   5d|", 123);  printf("  (%d)\n", len);
	len = ft_printf("|%+   5%d|", 123);  printf("  (%d)\n", len);

	// check fracinette
	// printf("<<< francinette >>>\n");
	// printf("----- printf -----\n");
	// //len = printf("%"); printf(" len: %d\n", len); seg fault
	// len = printf("%5%\n"); //printf(" len: %d\n", len);
	// len = printf("%-5%\n"); //printf(" len: %d\n", len);
	// len = printf("%-05%\n"); //printf(" len: %d\n", len);
	// // Cの標準規格では％を表示したくても上のような指定方法は実装依存（未定義）。
	// // ５つ幅寄せされた％を出力したいのなら、printf("%5s", "%") とすべき。（なので、リテラル見つけたら表示でいい）
	// len = printf("%.c\n", 'a'); //printf(" len: %d\n", len); 
	// len = printf("%-s\n", NULL); //printf(" len: %d\n", len);
	// len = printf("%23s\n", NULL); //printf(" len: %d\n", len);
	// //len =  printf("%s\n", NULL); // seg fault
	// len = printf("%32s\n", "abc"); //printf(" len: %d\n", len);
	// len = printf("%16s\n", "nark nark"); //printf(" len: %d\n", len);
	// len = printf("%.0s\n", "hello"); //printf(" len: %d\n", len);
	// len = printf("%.5s%7s\n", "yo", "boi"); //printf(" len: %d\n", len);
	// len = printf("%7.5s\n", "yolo"); //printf(" len: %d\n", len);
	// len = printf("%7.5s\n", "bombastic"); //printf(" len: %d\n", len);
	// len = printf("%7.7s%7.7s\n", "hello", "world"); //printf(" len: %d\n", len);
	// len = printf("%3.7s%7.7s\n", "hello", "world"); //printf(" len: %d\n", len);
	// len = printf("%7.7s%3.7s\n", "hello", "world"); //printf(" len: %d\n", len);
	// len = printf("%7.3s%7.7s\n", "hello", "world"); //printf(" len: %d\n", len);
	// len = printf("%3.3s%7.7s\n", "hello", "world"); //printf(" len: %d\n", len);
	// len = printf("%7.3s%3.7s\n", "hello", "world"); //printf(" len: %d\n", len);
	// len = printf("%7.7s%7.3s\n", "hello", "world"); //printf(" len: %d\n", len);
	// printf("----- ft_printf -----\n");
	// //len = ft_printf("%"); printf(" len: %d\n", len);
	// len = ft_printf("%5%\n"); //printf(" len: %d\n", len);
	// len = ft_printf("%-5%\n"); //printf(" len: %d\n", len);
	// len = ft_printf("%-05%\n"); //printf(" len: %d\n", len); 
	// len = ft_printf("%.c\n", 'a'); //printf(" len: %d\n", len);
	// len = ft_printf("%-s\n", NULL); //printf(" len: %d\n", len);
	// len = ft_printf("%23s\n", NULL); //printf(" len: %d\n", len);
	// //len = ft_printf("(seg fault) %s\n", NULL); // seg fault
	// len = ft_printf("%32s\n", "abc"); //printf(" len: %d\n", len);
	// len = ft_printf("%16s\n", "nark nark"); //printf(" len: %d\n", len);
	// len = ft_printf("%.0s\n", "hello"); //printf(" len: %d\n", len);
	// len = ft_printf("%.5s%7s\n", "yo", "boi"); //printf(" len: %d\n", len);
	// len = ft_printf("%7.5s\n", "yolo"); //printf(" len: %d\n", len);
	// len = ft_printf("%7.5s\n", "bombastic"); //printf(" len: %d\n", len);
	// len = ft_printf("%7.7s%7.7s\n", "hello", "world"); //printf(" len: %d\n", len);
	// len = ft_printf("%3.7s%7.7s\n", "hello", "world"); //printf(" len: %d\n", len);
	// len = ft_printf("%7.7s%3.7s\n", "hello", "world"); //printf(" len: %d\n", len);
	// len = ft_printf("%7.3s%7.7s\n", "hello", "world"); //printf(" len: %d\n", len);
	// len = ft_printf("%3.3s%7.7s\n", "hello", "world"); //printf(" len: %d\n", len);
	// len = ft_printf("%7.3s%3.7s\n", "hello", "world"); //printf(" len: %d\n", len);
	// len = ft_printf("%7.7s%7.3s\n", "hello", "world"); //printf(" len: %d\n", len);

	free(buf);
	free(buf2);
	printf("\n					[end]\n");
	return (0);
}

/*
Makefile こういう書き方あるらしいけど、なんか通らなかった。
# ifeq ($(MAKECMDGOALS), bonus)
# SRCS	=ft_printf_bonus.c \
# 		printfunc_str_bonus.c \
# 		printfunc_num_bonus.c \
# 		initflags_bonus.c \
# 		buffer_process_bonus.c \
# 		utilfunc_a_bonus.c \
# 		utilfunc_b_bonus.c \
# 		utilfunc_c_bonus.c \
# 		ft_libft.c
# OBJS  	=$(SRCS:.c=.o)
# else
# SRCS	=ft_printf.c \
# 		printfunc_str.c \
# 		printfunc_num.c \
# 		ft_libft.c
# OBJS	=$(SRCS:.c=.o)
# endif
*/