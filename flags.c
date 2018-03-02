/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 13:44:58 by imarakho          #+#    #+#             */
/*   Updated: 2018/03/02 19:30:12 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	start_flags(t_par *pr)
{
	pr->alter = 0;
	pr->minus = 0;
	pr->plus = 0;
	pr->space = 0;
	pr->nll = 0;
	pr->wdth = 0;
	pr->flag = 1;
	pr->pres = 1;
	pr->md_sp = 0;
	pr->s = "";
	pr->d = 0;
	pr->sz = 0;
}

void	check_flags3(const char *format, int *i, t_par *pr, va_list *ap)
{
	if (format[*i] == '.')
	{
		*i += 1;
		if (ft_isdigit(format[*i]))
		{
			pr->pres = ft_atoi(&format[*i]);
			*i += ft_strlen(ft_itoa_base(pr->pres, 10));
		}
		else if (format[*i] == '*')
		{
			pr->pres = va_arg(*ap, int);
			*i += 1;
		}
		else
			pr->pres = 0;
	}
	else if (ft_isdigit(format[*i]) && format[*i] != '0')
		parse_width(i, pr, format);
	else
		pr->flag = 0;
}

void	check_flags2(const char *format, int *i, t_par *pr, va_list *ap)
{
	if (format[*i] == '-')
	{
		pr->minus = 1;
		*i += 1;
	}
	else if (format[*i] == '#')
	{
		pr->alter = 1;
		*i += 1;
	}
	else if (format[*i] == '0')
	{
		pr->nll = 1;
		*i += 1;
	}
	else if (format[*i] == '*')
	{
		pr->space = va_arg(*ap, int);
		pr->wdth = 1;
		pr->res < pr->space ? pr->res += pr->space : 0;
		*i += ft_strlen(ft_itoa_base(pr->space, 10));
	}
	else
		check_flags3(format, i, pr, ap);
}

void	check_flags(const char *format, int *i, t_par *pr, va_list *ap)
{
	start_flags(pr);
	while (pr->flag)
	{
		if (format[*i] == '+')
		{
			pr->plus = 1;
			*i += 1;
		}
		else if (format[*i] == ' ')
		{
			pr->md_sp = 1;
			while (format[*i] == ' ')
				*i += 1;
		}
		else
			check_flags2(format, i, pr, ap);
	}
}
