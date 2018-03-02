/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 15:28:28 by imarakho          #+#    #+#             */
/*   Updated: 2018/03/02 19:44:41 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	int_checks(t_par *pr)
{
	if (pr->pres == 0 && pr->val == 0)
	{
		free(pr->s);
		pr->s = "";
	}
	pr->len = ft_strlen(pr->s);
	if (pr->minus && pr->pres - pr->len == 1 && !pr->plus)
	{
		pr->res--;
		pr->space--;
	}
	if (pr->len > pr->space)
		pr->res += pr->len;
	if (pr->space > 0 && pr->pres > pr->space)
	{
		pr->wdth = 0;
		if (pr->len < pr->space)
			pr->res -= pr->len;
		else
		{
			pr->res -= pr->len;
			pr->res += (pr->len - pr->space);
		}
	}
}

void	check_int_pl2(t_par *pr)
{
	if (pr->d < 0 && (!pr->nll || pr->pres > 1))
	{
		pr->d = 0;
		pr->res < pr->pres && pr->len < pr->space ? pr->res += pr->len : 0;
		!pr->nll ? ft_putchar('-') : 0;
	}
	if (pr->plus && pr->val >= 0 && pr->pres > pr->len)
	{
		pr->plus = 0;
		ft_putchar('+');
		if (pr->space <= pr->len
		&& pr->pres <= pr->len)
			pr->res++;
	}
	make_pres(pr, 'd');
	if (pr->plus && pr->val >= 0)
	{
		ft_putchar('+');
		pr->space <= pr->len && pr->pres <= pr->len ? pr->res++ : 0;
	}
	write(1, pr->s, ft_strlen(pr->s));
}

void	check_int_pl(t_par *pr)
{
	if (pr->plus && pr->val >= 0 && (pr->nll || pr->pres > pr->len))
	{
		if (pr->nll)
		{
			pr->plus = 0;
			ft_putchar('+');
		}
		if (pr->space <= pr->len
		&& pr->pres <= pr->len && pr->val == 0)
			pr->res++;
		pr->space--;
	}
	if (pr->val < 0 && (pr->nll || pr->pres > 1))
	{
		pr->d = pr->val;
		pr->val *= -1;
		pr->s = ft_itoa_base(pr->val, 10);
		pr->len = ft_strlen(pr->s);
		pr->plus = 0;
		pr->space > pr->len ? pr->space-- : 0;
		if (pr->nll)
			ft_putchar('-');
	}
	make_width(pr, 'd');
	check_int_pl2(pr);
}

void	check_intmin(t_par *pr)
{
	if (pr->plus && pr->val >= 0)
	{
		pr->plus = 0;
		ft_putchar('+');
		pr->res--;
		pr->space -= 2;
	}
	make_pres(pr, 'd');
	write(1, pr->s, ft_strlen(pr->s));
	make_width(pr, 'd');
}

void	check_int(t_par *pr, va_list *ap, char sz)
{
	pr->st_sp = pr->space;
	pr->val = va_arg(*ap, intmax_t);
	make_size(pr, sz);
	ft_strcmp(pr->s, "") ? pr->s = "" : 0;
	pr->s = ft_itoa_base(pr->val, 10);
	int_checks(pr);
	if (pr->md_sp && !pr->plus && !pr->minus && pr->val >= 0)
	{
		ft_putchar(' ');
		pr->space--;
		pr->space <= 0 ? pr->res++ : 0;
	}
	if (!pr->minus)
		check_int_pl(pr);
	else
		check_intmin(pr);
	pr->res < pr->st_sp ? pr->res = pr->st_sp : 0;
	if (ft_strcmp(pr->s, ""))
		free(pr->s);
}
