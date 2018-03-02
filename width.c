/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 19:28:45 by imarakho          #+#    #+#             */
/*   Updated: 2018/03/02 19:32:15 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*concat(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(len1 + len2 + 1);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2 + 1);
	return (result);
}

void	make_pres(t_par *pr, char spec)
{
	if (spec == 0)
		return ;
	if ((unsigned long)pr->pres <= ft_strlen(pr->s))
	{
		if ((unsigned long)pr->res < ft_strlen(pr->s))
			pr->res = ft_strlen(pr->s);
		return ;
	}
	if (pr->pres > 1)
	{
		if ((unsigned long)pr->pres >= ft_strlen(pr->s))
		{
			pr->pres -= ft_strlen(pr->s);
			pr->res += pr->pres;
		}
		while (pr->pres > 0 && pr->pres--)
			ft_putchar('0');
	}
}

void	width_check(t_par *pr, char spec)
{
	if (spec != 's')
		pr->space -= pr->pres;
	else
		pr->space -= ft_strlen(pr->s);
	if ((unsigned long)pr->res > ft_strlen(pr->s))
		pr->res -= ft_strlen(pr->s);
}

void	parse_width(int *i, t_par *pr, const char *format)
{
	pr->wdth = 1;
	if (!ft_isdigit(format[*i]) || format[*i + 1] == '\0')
		return ;
	pr->space = ft_atoi(&format[*i]);
	if (pr->res < pr->space)
		pr->res += pr->space;
	*i += ft_strlen(ft_itoa_base(pr->space, 10));
}

void	make_width(t_par *pr, char spec)
{
	if (!pr->wdth)
		return ;
	if ((unsigned long)pr->space < ft_strlen(pr->s) && spec != 's')
	{
		pr->res -= pr->space;
		return ;
	}
	if ((unsigned long)pr->pres > ft_strlen(pr->s))
		width_check(pr, spec);
	else if (spec != 's')
		pr->space -= ft_strlen(pr->s);
	else if (pr->pres > 1 && (unsigned long)pr->pres < ft_strlen(pr->s))
		pr->space -= pr->pres;
	spec == '%' && pr->nll ? pr->space-- : 0;
	if (pr->nll && !pr->minus && pr->pres <= 1)
		while (pr->space > 0 && pr->space--)
			ft_putchar('0');
	else
		while (pr->space > 0 && pr->space--)
		{
			pr->pres == 0 && pr->val == 0 && spec == 'd' ? pr->res++ : 0;
			ft_putchar(' ');
		}
}
