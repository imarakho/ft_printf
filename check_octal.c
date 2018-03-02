/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_octal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 17:38:11 by imarakho          #+#    #+#             */
/*   Updated: 2018/03/02 17:40:21 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_char(t_par *pr, va_list *ap, char sz)
{
	pr->uval = va_arg(*ap, int);
	make_size(pr, sz);
	if (!pr->wdth)
		pr->res++;
	if (pr->space > 1 && pr->nll && pr->uval == 0 && pr->pres == 0)
		pr->space--;
	if (!pr->minus)
	{
		make_width(pr, 'c');
		ft_putchar(pr->uval);
	}
	else
	{
		ft_putchar(pr->uval);
		make_width(pr, 'c');
	}
}

void	check_uns_int(t_par *pr, va_list *ap)
{
	pr->uval = va_arg(*ap, uintmax_t);
	make_size(pr, 'u');
	if (ft_strcmp(pr->s, ""))
		free(pr->s);
	pr->s = ft_unsitoa_base(pr->uval, 10);
	if (pr->pres == 0 && pr->uval == 0)
		pr->s = "";
	pr->len = ft_strlen(pr->s);
	if (pr->space < pr->len)
		pr->res += pr->len;
	if (!pr->minus)
	{
		make_width(pr, 'u');
		make_pres(pr, 'd');
		write(1, pr->s, pr->len);
	}
	else
	{
		make_pres(pr, 'd');
		write(1, pr->s, pr->len);
		make_width(pr, 'u');
	}
	if (ft_strcmp(pr->s, ""))
		free(pr->s);
}

void	check_uns_long(t_par *pr, va_list *ap)
{
	pr->uval = va_arg(*ap, uintmax_t);
	make_size(pr, 'U');
	if (ft_strcmp(pr->s, ""))
		free(pr->s);
	pr->s = ft_unsitoa_base(pr->uval, 10);
	if (pr->pres == 0 && pr->val == 0)
	{
		free(pr->s);
		pr->s = "";
	}
	pr->len = ft_strlen(pr->s);
	if (pr->space < pr->len)
		pr->res += pr->len;
	if (!pr->minus)
	{
		make_width(pr, 'U');
		write(1, pr->s, pr->len);
	}
	else
	{
		write(1, pr->s, pr->len);
		make_width(pr, 'U');
	}
	if (ft_strcmp(pr->s, ""))
		free(pr->s);
}

void	octal_check(t_par *pr)
{
	if (pr->pres == 0 && pr->uval == 0)
	{
		pr->res += pr->space;
		free(pr->s);
		pr->s = "";
	}
	if (((pr->alter && pr->uval != 0)
	|| (pr->alter && pr->uval == 0 && pr->pres == 0)))
		pr->s = concat("0", pr->s);
	pr->len = ft_strlen(pr->s);
	pr->space < pr->len && pr->len > 0 ? pr->res += pr->len : 0;
	if (pr->space < pr->pres && pr->minus)
	{
		pr->wdth = 0;
		pr->res--;
	}
}

void	check_octal(t_par *pr, char sz, va_list *ap)
{
	pr->uval = va_arg(*ap, uintmax_t);
	make_size(pr, sz);
	ft_strcmp(pr->s, "") ? free(pr->s) : 0;
	pr->s = ft_unsitoa_base(pr->uval, 8);
	octal_check(pr);
	if (!pr->minus)
	{
		make_width(pr, 'o');
		make_pres(pr, 'o');
		write(1, pr->s, pr->len);
	}
	else
	{
		if (pr->space > (pr->pres + pr->len))
		{
			pr->space -= pr->pres;
			pr->space += pr->len;
			pr->res--;
		}
		make_pres(pr, 'o');
		write(1, pr->s, pr->len);
		make_width(pr, 'o');
	}
	ft_strcmp(pr->s, "") ? free(pr->s) : 0;
}
