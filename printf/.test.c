#include "ft_printf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char has_symbol(const char *format)
{
    size_t  index;
    int     hasPercent;
    char    c;

    index = 0;
    hasPercent = 0;
    while (format[index] != '\0')
    {
        if (format[index++] == '%')
        {
            hasPercent = 1;
            break;
        }
    }
    if (hasPercent == 0)
        return (0);
    while (format[index] != '\0')
    {
		c = format[index];
		if (c == 'c' || c == 's'
			|| c == 'p' || c == 'd'
			|| c == 'i' || c == 'u'
			|| c == 'x' || c == 'X'
			|| c == '%')
			return (c);
        index++;
    }
    return (0);
}

int main(int argc, char **argv)
{
    int len = 0;

    if (argc != 3)
        return 1;

    char *format = argv[1];
    char *value = argv[2];
    char symbol = has_symbol(format);

    printf("\n<< run test >>\n");
    printf("format:[%s]\n", format);
    printf("value :[%s]\n", value);
    printf("----------------------------\n");

    if (symbol == 'c'){
        char c = value[0];
        printf("(symbol 'c' check)\n");
        printf("your output:\n\"");
        fflush(stdout);
        len = ft_printf(format, c);
        printf("\" (%d)\n", len);

        printf("expected:\n\"");
        len = printf(format, c);
        printf("\" (%d)\n", len);
    }

    if (symbol == 'd' || symbol == 'i'){
        int d = atoi(value);
        printf("(symbol 'd', 'i' check)\n");
        printf("your output:\n\"");
        fflush(stdout);
        len = ft_printf(format, d);
        printf("\" (%d)\n", len);

        printf("expected:\n\"");
        len = printf(format, d);
        printf("\" (%d)\n", len);
    }

    if (symbol == 'u'){
        unsigned int u = (unsigned int)strtoul(value, NULL, 10);
        printf("(symbol 'u' check)\n");
        printf("your output:\n\"");
        fflush(stdout);
        len = ft_printf(format, u);
        printf("\" (%d)\n", len);

        printf("expected:\n\"");
        len = printf(format, u);
        printf("\" (%d)\n", len);
    }

    if (symbol == 'x' || symbol == 'X'){
        long l = strtol(value, NULL, 16);
        printf("(symbol 'x','X' check)\n");
        printf("your output:\n\"");
        fflush(stdout);
        len = ft_printf(format, l);
        printf("\" (%d)\n", len);

        printf("expected:\n\"");
        len = printf(format, l);
        printf("\" (%d)\n", len);
    }

    if (symbol == 'p'){
        void *ptr = NULL;
        if (strcmp(value, "NULL") != 0)
            ptr = value;

        printf("(symbol 'p' check)\n");
        printf("your output:\n\"");
        fflush(stdout);
        len = ft_printf(format, ptr);
        printf("\" (%d)\n", len);

        printf("expected:\n\"");
        len = printf(format, ptr);
        printf("\" (%d)\n", len);
    }

    if (symbol == '%'){
        printf("(symbol '%%' check)\n");
        printf("your output:\n\"");
        fflush(stdout);
        len = ft_printf(format);
        printf("\" (%d)\n", len);

        printf("expected:\n\"");
        len = printf(format, 0);
        printf("\" (%d)\n", len);
    }

    if (symbol == 's'){
        char *str = NULL;
        if (strcmp(value, "NULL") != 0)
            str = value;

        printf("(symbol 's' check)\n");
        printf("your output:\n\"");
        fflush(stdout);
        len = ft_printf(format, str);
        printf("\" (%d)\n", len);

        printf("expected:\n\"");
        len = printf(format, str);
        printf("\" (%d)\n", len);
    }

    if (symbol == 0){
        printf("(no symbol check)\n");
        printf("your output:\n\"");
        fflush(stdout);
        len = ft_printf(format);
        printf("\" (%d)\n", len);

        printf("expected:\n\"");
        len = printf(format, 0);
        printf("\" (%d)\n", len);
    }

    printf("----------------------------\n");
    return 0;
}
