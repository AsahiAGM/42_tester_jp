#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ft_printf_bonus.h"
#include <limits.h>

int main(void)
{
	int len = 0;
	int *buf = calloc(1,sizeof(int));

	printf("\n\n // stdout ERROR test\n");
	len = printf("Mixed: char=%c, str=%s, ptr=%p, int=%d, uint=%u, hex=%x, HEX=%X, percent=%%", 'Z', "Test", buf, -123, 456U, 0xabc, 0xDEF);
	printf("\n %d\n", len);
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
