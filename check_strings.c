/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:21:58 by imarakho          #+#    #+#             */
/*   Updated: 2018/03/02 17:41:13 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	string_pl(t_par *pr)
{
	if (pr->space > pr->len && pr->pres == 1)
	{
		pr->res -= pr->len;
		pr->space -= pr->len;
	}
	make_width(pr, 's');
	if (pr->pres > 1 && pr->pres < pr->len)
	{
		pr->d = -1;
		pr->res -= pr->len;
		pr->space -= pr->len;
		pr->pres++;
		while (pr->pres-- && pr->pres > 0)
		{
			pr->pres > pr->st_sp ? pr->res++ : 0;
			ft_putchar(pr->s[++pr->d]);
		}
	}
	else
	{
		pr->space > pr->len ? pr->space -= pr->len : 0;
		if (pr->res < pr->len && pr->pres > pr->len)
			pr->res += pr->len - pr->st_sp;
		write(1, pr->s, pr->len);
	}
}

void	string_min(t_par *pr)
{
	if (pr->space > pr->len && pr->pres == 1)
	{
		pr->res -= pr->len;
		pr->space -= pr->len;
	}
	if (pr->pres > 1 && pr->pres < pr->len)
	{
		pr->d = -1;
		pr->res -= pr->len;
		pr->space -= pr->pres;
		pr->pres++;
		while (pr->pres-- && pr->pres > 0)
		{
			pr->pres > pr->st_sp ? pr->res++ : 0;
			ft_putchar(pr->s[++pr->d]);
		}
	}
	else
		write(1, pr->s, pr->len);
	make_width(pr, 's');
}

void	check_string(t_par *pr, va_list *ap)
{
	pr->st_sp = pr->space;
	if (ft_strcmp(pr->s, ""))
		free(pr->s);
	pr->s = va_arg(*ap, char *);
	if (pr->s == NULL)
	{
		free(pr->s);
		if (pr->space)
			pr->s = "";
		else
			pr->res += write(1, "(null)", 6);
		return ;
	}
	pr->len = ft_strlen(pr->s);
	pr->res += pr->len;
	make_size(pr, 's');
	if (!pr->minus)
		string_pl(pr);
	else
		string_min(pr);
}

void	ponter_min(t_par *pr)
{
	if (!pr->minus)
	{
		if (pr->space < pr->len + 2)
			pr->res += 2;
		pr->space -= 2;
		{
			make_width(pr, 'p');
		}
		ft_putstr("0x");
		make_pres(pr, 'p');
		write(1, pr->s, pr->len);
	}
	else
	{
		ft_putstr("0x");
		if (pr->space < pr->len + 2)
			pr->res += 2;
		pr->space -= 2;
		make_pres(pr, 'p');
		write(1, pr->s, pr->len);
		make_width(pr, 'p');
	}
	if (ft_strcmp(pr->s, ""))
		free(pr->s);
}

void	check_pointer(t_par *pr, va_list *ap)
{
	pr->ptr = (uintmax_t)va_arg(*ap, void *);
	if (ft_strcmp(pr->s, ""))
		free(pr->s);
	pr->s = ft_unsitoa_base(pr->ptr, 16);
	pr->len = ft_strlen(pr->s);
	if (pr->len + 2 >= pr->space)
		pr->wdth = 0;
	if (pr->pres == 0 && pr->ptr == 0)
	{
		free(pr->s);
		pr->s = "";
		pr->len = 0;
	}
	if (pr->len + 2 > pr->space)
	{
		pr->res -= pr->space;
		pr->res += pr->len;
	}
	pr->d = -1;
	while (pr->s[++pr->d] != '\0')
		pr->s[pr->d] = ft_tolower(pr->s[pr->d]);
	ponter_min(pr);
}
