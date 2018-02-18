/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:21:58 by imarakho          #+#    #+#             */
/*   Updated: 2018/02/18 18:01:33 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void    check_char(t_par *pr, va_list *ap)
{
	pr->uval = va_arg(*ap, int);
	make_size(pr,'c', ap);
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
	make_size(pr, 's', ap);
	if (!pr->minus)
	{
		if (pr->space > ft_strlen(pr->s))
			make_width(pr , 's');
		ft_putstr(pr->s);
	}
	else
	{
        ft_putstr(pr->s);
		if(pr->space > ft_strlen(pr->s))
			make_width(pr , 's');
	}
}

void    check_pointer(t_par *pr, va_list *ap)
{
	pr->ptr = (uintmax_t)va_arg(*ap, void *);
	pr->s = ft_unsitoa_base(pr->ptr, 16);
	pr->d = -1;			
		while(pr->s[++pr->d] != '\0')
			pr->s[pr->d] = ft_tolower(pr->s[pr->d]);
		pr->d = 0;
	if(pr->space > 0)
		pr->space -= 6;
	if (!pr->minus)
	{
		if (pr->space > ft_strlen(pr->s))
		{
			make_width(pr , 'p');
		}
        ft_putstr("0x");
		ft_putstr(pr->s);
	}
	else
	{
        ft_putstr("0x");
        ft_putstr(pr->s);
		if (pr->space > ft_strlen(pr->s))
		{
		//	printf("pzd\n");
			make_width(pr , 'p');
		}
	}
}