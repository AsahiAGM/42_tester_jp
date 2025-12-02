#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ft_printf.h"
#include <limits.h>

int main(void)
{
	int len = 0;
	int *buf = calloc(1,sizeof(int));
	int *buf2 = calloc(1,sizeof(int));

	printf("\n\n // stdout ERROR test\n");
	printf("(If the result is normal, activate safe_write and try again.)\n");
	printf("\n----- ft_printf -----\n");
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
	len = ft_printf("Mixed: char=%c, str=%s, ptr=%p, int=%d, uint=%u, hex=%x, HEX=%X, percent=%%", 'Z', "Test", buf, -123, 456U, 0xabc, 0xDEF);
	printf("\n %d\n", len);

	// len が INT_MAX を超えるケース
	printf("\n // OVERFLOW ERROR test\n");
	size_t huge_len = (size_t)INT_MAX + 10;
	char *huge_str = malloc(huge_len + 1);
	memset(huge_str, 'A', huge_len);
	huge_str[huge_len] = '\0';
	//len = printf("%s", huge_str); printf(" %d\n", len); // 延々と無を出力した後にAを出力し、-1 を返す。…という動作
	//len = ft_printf("%s", huge_str); printf(" %d\n", len); // こちらはサイズ分のAをひたすら出力して -1 を返す …という動作
	
	free(buf);
	free(buf2);
	free(huge_str);
	return (0);
}

// STDOUTエラーのテストをしたい場合これを有効化
// ssize_t safe_write(int fd, const void *val, size_t size)
// {
//     (void)fd; (void)val; (void)size;
//     errno = EIO;
//     return -1;
// }
