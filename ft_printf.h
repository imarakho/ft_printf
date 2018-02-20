/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:23:09 by imarakho          #+#    #+#             */
/*   Updated: 2018/02/20 17:50:09 by imarakho         ###   ########.fr       */
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
    short           wdth;
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

char	*ft_itoa_base(long long int value, int base);
char	*ft_unsitoa_base(unsigned long int value, int base);
char	*ft_itoa_baseptr(long value, int base);
char*   concat(char *s1, char *s2);
void	ft_putstr(char const *s);
void	ft_putchar(char c);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_bzero(void *s, size_t n);
int		ft_toupper(int character);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *s);
int		ft_isdigit(int character);
int		ft_tolower(int character);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n);
void	make_width(t_par *pr, char spec);
void    check_flags(const char *format, int *i, t_par *pr, va_list *ap);
void    check_int(t_par *pr, va_list *ap);
void    check_octal(t_par *pr, va_list *ap);
void    check_hex(t_par *pr, va_list *ap);
void    check_heX(t_par *pr, va_list *ap);
void    check_uns_long(t_par *pr, va_list *ap);
void    check_uns_int(t_par *pr, va_list *ap);
void    check_char(t_par *pr, va_list *ap);
void    check_string(t_par *pr, va_list *ap);
void    check_pointer(t_par *pr, va_list *ap);
void	print_memory(const void *addr, size_t size);
char	*ft_strcat(char *restrict s1, const char *restrict s2);
void    check_size(const char *format, t_par *pr, int *i);
void	make_size(t_par *pr, char md, va_list *ap);
void    start_flags(t_par *pr);

/*for makefile
    $(NAME):
	gcc -c $(FLAGS) $(SRC) -I ft_printf.h
	ar	rc $(NAME) $(OBJ)
	ranlib $(NAME)

    @gcc $(FLAGS) $(SRC) -o $(NAME)
	@echo "Compilation done!"
*/

#endif