/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:23:09 by imarakho          #+#    #+#             */
/*   Updated: 2018/02/18 16:44:39 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct      s_par
{
    int             d;
    float           f;
    double          lf;
    char            *s;
    char            c;
    short           nll;
    short           flag;
    short           minus;
    short           plus;
    unsigned int    space;
    short           alter;
    char            *width;
    uintmax_t       ptr;
    int             res;
    unsigned int    pres;
    char            sz;
    intmax_t        val;
    uintmax_t       uval;
}                   t_par;

char	*ft_itoa_base(intmax_t value, int base);
char	*ft_itoa_baseptr(long value, int base);
void	ft_putstr(char const *s);
void	ft_putchar(char c);
void	ft_bzero(void *s, size_t n);
int		ft_toupper(int character);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *s);
int		ft_isdigit(int character);
int		ft_tolower(int character);
void	make_width(t_par *pr, char spec);
void    check_flags(const char *format, int *i, t_par *pr, va_list *ap);
void    check_int(t_par *pr, va_list *ap);
void    check_octal(t_par *pr, va_list *ap);
void    check_hex(t_par *pr, va_list *ap);
void    check_heX(t_par *pr, va_list *ap);
void    check_uns_int(t_par *pr, va_list *ap);
void    check_char(t_par *pr, va_list *ap);
void    check_string(t_par *pr, va_list *ap);
void    check_pointer(t_par *pr, va_list *ap);
void	print_memory(const void *addr, size_t size);
void    check_size(const char *format, t_par *pr, int *i);
void	make_size(t_par *pr, char md, va_list *ap);

/*for makefile
    $(NAME):
	gcc -c $(FLAGS) $(SRC) -I ft_printf.h
	ar	rc $(NAME) $(OBJ)
	ranlib $(NAME)

    @gcc $(FLAGS) $(OBJ) $(SRC) -o $(NAME)
	@echo "Compilation done!"
*/

#endif