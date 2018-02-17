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

OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror
all: $(NAME)

$(NAME): $(OBJ)
	gcc -c $(FLAGS) $(SRC) -I ft_printf.h
	ar	rc $(NAME) $(OBJ)
	ranlib $(NAME)
	
lldb:
	@gcc -g $(FLAGS) $(OBJ) -o $(NAME)
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