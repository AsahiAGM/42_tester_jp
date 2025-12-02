NAME		=libftprintf.a
CC			=cc
CFLAGS		=-Wall -Werror -Wextra
LIBFT_SRCS	=libft/ft_atoi.c libft/ft_isalpha.c libft/ft_itoa.c libft/ft_memmove.c libft/ft_putnbr_fd.c libft/ft_strdup.c libft/ft_strlcpy.c libft/ft_strnstr.c libft/ft_tolower.c \
libft/ft_bzero.c libft/ft_isascii.c libft/ft_memchr.c libft/ft_memset.c libft/ft_putstr_fd.c libft/ft_striteri.c libft/ft_strlen.c libft/ft_strrchr.c libft/ft_toupper.c \
libft/ft_calloc.c libft/ft_isdigit.c libft/ft_memcmp.c  libft/ft_putchar_fd.c libft/ft_split.c libft/ft_strjoin.c libft/ft_strmapi.c libft/ft_strtrim.c \
libft/ft_isalnum.c libft/ft_isprint.c libft/ft_memcpy.c  libft/ft_putendl_fd.c libft/ft_strchr.c libft/ft_strlcat.c libft/ft_strncmp.c libft/ft_substr.c
LIBFT_OBJS	=$(LIBFT_SRCS:.c=.o)
MAKEFLAGS 	+= --no-print-directory

SRCS	=ft_printf.c \
		printfunc_str.c \
		printfunc_num.c \
		utilfunc.c \
		safewrite.c
ifdef WITH_BONUS
SRCS	=ft_printf_bonus.c \
		printfunc_str_bonus.c \
		printfunc_num_bonus.c \
		initflags_bonus.c \
		buffer_process_bonus.c \
		utilfunc_a_bonus.c \
		utilfunc_b_bonus.c \
		safewrite_bonus.c
endif
OBJS  	=$(SRCS:.c=.o)

all:$(NAME)

bonus:
	@$(MAKE) WITH_BONUS=1

$(NAME):$(OBJS) $(LIBFT_OBJS)
	ar rcs $(NAME) $^

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f libft/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
