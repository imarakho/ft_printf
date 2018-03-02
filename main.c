/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:41:31 by imarakho          #+#    #+#             */
/*   Updated: 2018/03/02 19:02:22 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf3(const char *format, int *i, t_par *pr, va_list *ap)
{
	if ((pr->sz == 'l' && format[*i] == 'c') || format[*i] == 'C')
		if (MB_CUR_MAX == 1)
			check_char(pr, ap, 'c');
		else
			check_symbol(pr, ap, 'C');
	else if (format[*i] == 'c')
		check_char(pr, ap, 'c');
	else if (format[*i] == 'p')
		check_pointer(pr, ap);
	else
	{
		pr->res++;
		ft_putchar(format[*i]);
	}
}

void	ft_printf2(const char *format, int *i, t_par *pr, va_list *ap)
{
	if (format[*i] == '%')
	{
		if (!pr->space || pr->res == 0)
		{
			pr->res++;
		}
		if (!pr->minus)
		{
			make_width(pr, '%');
			ft_putchar(format[*i]);
		}
		else
		{
			ft_putchar(format[*i]);
			make_width(pr, '%');
		}
	}
	else if (format[*i] == 'S' || (pr->sz == 'l' && format[*i] == 's'))
		check_uncode(pr, ap, 'S');
	else if ((format[*i] == 's'))
		check_string(pr, ap);
	else
		ft_printf3(format, i, pr, ap);
}

void	ft_printf1(const char *format, int *i, t_par *pr, va_list *ap)
{
	*i += 1;
	check_flags(format, i, pr, ap);
	check_size(format, pr, i);
	if (format[*i] == 'd' || format[*i] == 'i')
		check_int(pr, ap, 'd');
	else if (format[*i] == 'D')
		check_int(pr, ap, 'D');
	else if (format[*i] == 'u')
		check_uns_int(pr, ap);
	else if (format[*i] == 'U')
		check_uns_long(pr, ap);
	else if (format[*i] == 'x')
		check_hex(pr, ap);
	else if (format[*i] == 'X')
		check_hexb(pr, ap);
	else if (format[*i] == 'o')
		check_octal(pr, 'o', ap);
	else if (format[*i] == 'O')
		check_octal(pr, 'O', ap);
	else
		ft_printf2(format, i, pr, ap);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	int			i;
	t_par		pr;

	pr.res = 0;
	va_start(ap, format);
	i = -1;
	if (!ft_strcmp(format, "%"))
		return (0);
	while (format[++i] != '\0')
	{
		if (format[i] == '%')
			ft_printf1(format, &i, &pr, &ap);
		else
		{
			pr.res++;
			ft_putchar(format[i]);
		}
	}
	va_end(ap);
	return (pr.res);
}
