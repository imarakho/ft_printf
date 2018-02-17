NAME = libftprintf.a
SRC = main.c \
	itoa_base.c \
	ft_bzero.c \
	ft_putstr.c \
	ft_putchar.c \
	ft_strlen.c \
	ft_toupper.c \
	ft_atoi.c \
	ft_isdigit.c \
	ft_tolower.c \
	flags.c \
	check_int.c \
	check_strings.c \
	print_memory.c \
	check_size.c

FLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

all:$(NAME)

$(NAME):
	gcc -c $(FLAGS) $(SRC) -I ft_printf.h
	ar	rc $(NAME) $(OBJ)
	ranlib $(NAME)

lldb:
	@gcc -c $(FLAGS) $(OBJ) -o $(NAME) -I ft_printf.h
	@echo "Use 'debug' for lldb."
lclean:
	@rm -f debug
	@echo "'debug' removed!"
clean:
	@rm -f $(OBJ)
	@echo "Objects removed!"
fclean: clean
	@rm -f $(NAME)
	@echo "Executable removed!"
re: fclean all