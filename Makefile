NAME = libftprintf.a
SRC = main.c \
	itoa_base.c \
	ft_putstr.c \
	ft_putchar.c \
	ft_strlen.c \
	ft_toupper.c \
	ft_isdigit.c \
	ft_tolower.c \
	ft_strcmp.c \
	ft_strcat.c \
	ft_strdup.c \
	flags.c \
	ft_atoi.c \
	check_int.c \
	check_strings.c \
	check_size.c \
	check_unicode.c \
	ft_memcpy.c \
	width.c \
	check_octal.c \
	check_hex.c

FLAGS = -c -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	gcc $(FLAGS) $(SRC) -I ft_printf.h
	ar	rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm	-rf $(OBJ)

fclean: clean
	rm	-f $(NAME)

re: fclean all