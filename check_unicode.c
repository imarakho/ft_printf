/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_unicode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 19:20:41 by imarakho          #+#    #+#             */
/*   Updated: 2018/03/02 19:42:47 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	symb_checks(t_par *pr, char md, va_list *ap)
{
	if (md == 'C')
	{
		pr->uval = va_arg(*ap, unsigned int);
		make_size(pr, 'C');
	}
	else
		make_size(pr, 'S');
	pr->mask[0] = 0;
	pr->mask[1] = 49280;
	pr->mask[2] = 14712960;
	pr->mask[3] = 4034953344;
	if (md == 'C')
	{
		pr->v = pr->uval;
		pr->len = ft_strlen(ft_unsitoa_base(pr->uval, 2));
		ft_strcmp(pr->s, "") ? free(pr->s) : 0;
		pr->s = ft_unsitoa_base(pr->uval, 2);
	}
	else
	{
		pr->v = *pr->unval;
		pr->len = ft_strlen(ft_unsitoa_base(*pr->unval, 2));
		ft_strcmp(pr->s, "") ? free(pr->s) : 0;
		pr->s = ft_unsitoa_base(*pr->unval, 2);
	}
}

void	check_s_size(t_par *pr)
{
	if (pr->len <= 11 && pr->len > 7)
	{
		pr->o[1] = (pr->v << 26) >> 26;
		pr->o[0] = ((pr->v >> 6) << 27) >> 27;
		pr->octet = (pr->mask[1] >> 8) | pr->o[0];
		pr->res += write(1, &pr->octet, 1);
		pr->octet = ((pr->mask[1] << 24) >> 24) | pr->o[1];
		pr->res += write(1, &pr->octet, 1);
	}
	else if (pr->len <= 16 && pr->len > 11)
	{
		pr->o[2] = (pr->v << 26) >> 26;
		pr->o[1] = ((pr->v >> 6) << 26) >> 26;
		pr->o[0] = ((pr->v >> 12) << 28) >> 28;
		pr->octet = (pr->mask[2] >> 16) | pr->o[0];
		pr->res += write(1, &pr->octet, 1);
		pr->octet = ((pr->mask[2] << 16) >> 24) | pr->o[1];
		pr->res += write(1, &pr->octet, 1);
		pr->octet = ((pr->mask[2] << 24) >> 24) | pr->o[2];
		pr->res += write(1, &pr->octet, 1);
	}
}

void	check_symbol(t_par *pr, va_list *ap, char md)
{
	symb_checks(pr, md, ap);
	if (pr->len <= 7)
	{
		if (md == 'C')
			pr->octet = pr->uval;
		else
			pr->octet = *pr->unval;
		pr->res += write(1, &pr->octet, 1);
	}
	check_s_size(pr);
	if (pr->len > 16)
	{
		pr->o[3] = (pr->v << 26) >> 26;
		pr->o[2] = ((pr->v >> 6) << 26) >> 26;
		pr->o[1] = ((pr->v >> 12) << 26) >> 26;
		pr->o[0] = ((pr->v >> 18) << 29) >> 29;
		pr->octet = (pr->mask[3] >> 24) | pr->o[0];
		pr->res += write(1, &pr->octet, 1);
		pr->octet = ((pr->mask[3] << 8) >> 24) | pr->o[1];
		pr->res += write(1, &pr->octet, 1);
		pr->octet = ((pr->mask[3] << 16) >> 24) | pr->o[2];
		pr->res += write(1, &pr->octet, 1);
		pr->octet = ((pr->mask[3] << 24) >> 24) | pr->o[3];
		pr->res += write(1, &pr->octet, 1);
	}
}

void	check_uncode(t_par *pr, va_list *ap, char md)
{
	int len;

	len = 0;
	pr->d = -1;
	pr->unval = va_arg(*ap, wchar_t*);
	if (pr->unval == NULL)
	{
		write(1, "(null)", 6);
		pr->res += 6;
		return ;
	}
	while (pr->unval[len])
		len++;
	if (pr->pres < len && pr->pres > 1)
	{
		pr->pres--;
		len = pr->pres;
	}
	while (++pr->d < len)
	{
		check_symbol(pr, ap, md);
		pr->unval++;
	}
}
