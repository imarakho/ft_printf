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

LIBOBJ = libft/*.o

INC = -I ft_printf.h

CFLAGS = -c -Wall -Wextra -Werror

LIBCR = make -C libft/

LIBINC = -I libft/includes/libft.h -L./libft -lft

all: $(NAME)

$(NAME): $(OBJ)
	$(LIBCR) all
	ar rc $(NAME) $(OBJ) $(LIBOBJ)
	ranlib $(NAME)

%.o: %.c
	gcc $(INC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

liball:
	$(LIBCR) all

libclean:
	$(LIBCR) clean

libre:
	$(LIBCR) re 