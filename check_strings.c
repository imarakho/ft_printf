/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:21:58 by imarakho          #+#    #+#             */
/*   Updated: 2018/02/23 19:55:40 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void    check_char(t_par *pr, va_list *ap, char sz)
{
	pr->uval = va_arg(*ap, int);
	make_size(pr, sz, ap);
	if (pr->space < ft_strlen(pr->s))
		pr->res += ft_strlen(pr->s)  - pr->space;
	else if (!pr->wdth)
		pr->res++;
	if (!pr->minus)
	{
		if (pr->space > ft_strlen(pr->s))
		{
			make_width(pr , 'c');
		}
		ft_putchar(pr->uval);
	}
	else
	{
        ft_putchar(pr->uval);
		if (pr->s != NULL && pr->space > ft_strlen(pr->s))
		{
			make_width(pr , 'c');
		}
	}
}

void    check_string(t_par *pr, va_list *ap)
{
	pr->s = va_arg(*ap, char *);
	if (pr->s == NULL)
		  pr->s = concat("", "(null)");
	if (pr->space < pr->pres)
	{
		pr->wdth = 0;
		pr->space = 0;
	}
	pr->res += ft_strlen(pr->s);
	make_size(pr, 's', ap);
	if (!pr->minus)
	{
			make_width(pr , 's');
		if(pr->pres > 1 && pr->pres < ft_strlen(pr->s))
		{
			pr->d = -1;
			pr->res -= ft_strlen(pr->s);
			pr->pres++;
			while(pr->pres-- && pr->pres > 0)
			{
				pr->res++;
				ft_putchar(pr->s[++pr->d]);
			}
			pr->d = 0;
		}
		else
			ft_putstr(pr->s);
	}
	else
	{
		 if(pr->pres > 1 && ft_strcmp(pr->s, "") && pr->space && pr->space < pr->pres)
            {
                pr->space += pr->pres;
                pr->res += pr->pres;
				if (pr->space == 1)
					pr->space++;
            }
		if(pr->pres > 1 && pr->pres < ft_strlen(pr->s))
		{
			pr->d = -1;
			pr->res += pr->pres;
			pr->res -= ft_strlen(pr->s);
			pr->pres++;
			while(pr->pres-- && pr->pres > 0)
				ft_putchar(pr->s[++pr->d]);
			pr->d = 0;
		}
		else
			ft_putstr(pr->s);
			make_width(pr , 's');
	}
}

void    check_pointer(t_par *pr, va_list *ap)
{
	pr->ptr = (uintmax_t)va_arg(*ap, void *);
	pr->s = ft_unsitoa_base(pr->ptr, 16);
	pr->res += ft_strlen(pr->s);
	pr->d = -1;			
		while(pr->s[++pr->d] != '\0')
			pr->s[pr->d] = ft_tolower(pr->s[pr->d]);
		pr->d = 0;
	if(pr->space > ft_strlen(pr->s))
		pr->space -= ft_strlen(pr->s);
	if (!pr->minus)
	{
		if (pr->space > ft_strlen(pr->s))
		{
			make_width(pr , 'p');
		}
		ft_putstr("0x");
		pr->res += 2;
		make_pres(pr, 'p');
		ft_putstr(pr->s);
	}
	else
	{
		ft_putstr("0x");
		pr->res += 2;
		make_pres(pr, 'p');
        ft_putstr(pr->s);
		if (pr->space > ft_strlen(pr->s))
		{
			make_width(pr , 'p');
		}
	}
}