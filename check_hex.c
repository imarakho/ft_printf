/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 19:43:37 by imarakho          #+#    #+#             */
/*   Updated: 2018/03/02 19:44:29 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_hex_pl(t_par *pr)
{
	pr->len = ft_strlen(pr->s);
	pr->space < pr->len ? pr->res += pr->len : 0;
	if (!pr->minus)
	{
		if (pr->alter && pr->nll && ft_strcmp(pr->s, "0"))
		{
			free(pr->s);
			pr->s = ft_unsitoa_base(pr->uval, 16);
			pr->space -= 2;
			write(1, "0x", 2);
		}
		make_width(pr, 'x');
		pr->d = -1;
		while (pr->s[++pr->d] != '\0')
			pr->s[pr->d] = ft_tolower(pr->s[pr->d]);
		pr->d = 0;
		make_pres(pr, 'x');
		write(1, pr->s, ft_strlen(pr->s));
	}
}

void	check_hex(t_par *pr, va_list *ap)
{
	pr->uval = va_arg(*ap, unsigned long);
	make_size(pr, 'x');
	pr->s = ft_unsitoa_base(pr->uval, 16);
	if (pr->pres == 0 && pr->uval == 0)
	{
		pr->space ? pr->res += pr->space : 0;
		free(pr->s);
		pr->s = "";
	}
	else if (pr->alter && ft_strcmp(pr->s, "0"))
	{
		pr->s = concat("0x", pr->s);
		(unsigned long)pr->res < ft_strlen(pr->s) ? pr->space -= 2 : 0;
	}
	check_hex_pl(pr);
	if (pr->minus)
	{
		pr->d = -1;
		while (pr->s[++pr->d] != '\0')
			pr->s[pr->d] = ft_tolower(pr->s[pr->d]);
		pr->d = 0;
		make_pres(pr, 'x');
		write(1, pr->s, ft_strlen(pr->s));
		make_width(pr, 'x');
	}
}

void	check_hexb_pl(t_par *pr)
{
	if (pr->alter && pr->nll && ft_strcmp(pr->s, "0"))
	{
		pr->space -= 2;
		write(1, "0X", 2);
	}
	make_width(pr, 'X');
	if (pr->alter && ft_strcmp(pr->s, "0"))
	{
		write(1, "0X", 2);
		pr->res += 2;
		pr->space -= 2;
	}
	make_pres(pr, 'X');
	write(1, pr->s, ft_strlen(pr->s));
}

void	check_hexb(t_par *pr, va_list *ap)
{
	pr->uval = va_arg(*ap, uintmax_t);
	make_size(pr, 'X');
	ft_strcmp(pr->s, "") ? free(pr->s) : 0;
	pr->s = ft_unsitoa_base(pr->uval, 16);
	if (pr->pres == 0 && pr->uval == 0)
	{
		pr->space ? pr->res += pr->space : 0;
		free(pr->s);
		pr->s = "";
	}
	pr->len = ft_strlen(pr->s);
	pr->space < pr->len ? pr->res += pr->len : 0;
	if (!pr->minus)
		check_hexb_pl(pr);
	else
	{
		make_pres(pr, 'X');
		write(1, pr->s, ft_strlen(pr->s));
		make_width(pr, 'X');
	}
	ft_strcmp(pr->s, "") ? free(pr->s) : 0;
}
