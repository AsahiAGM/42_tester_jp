#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ft_printf_bonus.h"
#include <limits.h>

#define GREEN "\x1b[32m" 
#define RESET "\x1b[0m" 

int main(void)
{
	int len = 0;
	// len が INT_MAX を超えるケース
	printf("%s//OVERFLOW ERROR test%s\n", GREEN, RESET);
	size_t huge_len = (size_t)INT_MAX + 10;
	char *huge_str = malloc(huge_len + 1);
	memset(huge_str, 'A', huge_len);
	huge_str[huge_len] = '\0';
	//len = printf("%s", huge_str); printf(" %d\n", len); // 延々と無を出力した後にAを出力し、-1 を返す。…という動作
	len = ft_printf("%s", huge_str); printf(" %d\n", len); // こちらはサイズ分のAをひたすら出力して -1 を返す …という動作

	free(huge_str);
	return (0);
}

