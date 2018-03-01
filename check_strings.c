/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:21:58 by imarakho          #+#    #+#             */
/*   Updated: 2018/03/01 19:05:11 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void    check_char(t_par *pr, va_list *ap, char sz)
{
	pr->uval = va_arg(*ap, int);
	make_size(pr, sz, ap);
	if (!pr->wdth)
		pr->res++;
	if(pr->space > 1 && pr->nll && pr->uval == 0 && pr->pres == 0)
		pr->space--;
	if (!pr->minus)
	{
		{
			make_width(pr , 'c');
		}
		ft_putchar(pr->uval);
	}
	else
	{
        ft_putchar(pr->uval);
		{
			make_width(pr , 'c');
		}
	}
}

void    check_string(t_par *pr, va_list *ap)
{
	int st_sp = pr->space;

	pr->s = va_arg(*ap, char *);
	if (pr->s ==  NULL)
		if (pr->space)
			pr->s = "";
		else
			{
		 		 pr->s = concat("", "(null)");
			}
	if(pr->pres == 0)
		pr->s = "";
	pr->len = ft_strlen(pr->s);
	pr->res += pr->len;
	make_size(pr, 's', ap);
	if (!pr->minus)
	{
		if(pr->space > pr->len && pr->pres == 1)
		{
			pr->res -= pr->len;
			pr->space -= pr->len;
		}
			make_width(pr , 's');
		if(pr->pres > 1 && pr->pres < pr->len)
		{
			pr->d = -1;
			pr->res -= pr->len;
			pr->space -= pr->len;
			pr->pres++;
			while(pr->pres-- && pr->pres > 0)
			{
				if(pr->pres > st_sp)
				pr->res++;
				ft_putchar(pr->s[++pr->d]);
			}
			pr->d = 0;
		}
		else
		{	
			if(pr->space > pr->len)
				pr->space -= pr->len;
			if (pr->res < pr->len && pr->pres > pr->len)
				pr->res += pr->len - st_sp;
			write(1, pr->s, pr->len);
		}
	}
	else
	{
		if(pr->space > pr->len && pr->pres == 1)
		{
			pr->res -= pr->len;
			pr->space -= pr->len;
		}
		if(pr->pres > 1 && pr->pres < pr->len)
		{
			pr->d = -1;
			pr->res -= pr->len;
			pr->space -= pr->len;
			pr->space += pr->pres;
			pr->pres++;
			while(pr->pres-- && pr->pres > 0)
			{
				if(pr->pres > st_sp)
				pr->res++;
				ft_putchar(pr->s[++pr->d]);
			}
			pr->d = 0;
		}
		else
			write(1, pr->s, pr->len);
			make_width(pr , 's');
	}
}

void    check_pointer(t_par *pr, va_list *ap)
{
	pr->ptr = (uintmax_t)va_arg(*ap, void *);
	pr->s = ft_unsitoa_base(pr->ptr, 16);
	pr->len = ft_strlen(pr->s);
	if(pr->len + 2 >= pr->space)
		pr->wdth = 0;
	if (pr->pres == 0 && pr->ptr == 0)
	{
		free(pr->s);
		pr->s = "";
		pr->len = 0;
		
	}
	if(pr->len + 2 > pr->space)
	{
		pr->res -= pr->space;
		pr->res += pr->len;
	}
	pr->d = -1;			
		while(pr->s[++pr->d] != '\0')
			pr->s[pr->d] = ft_tolower(pr->s[pr->d]);
		pr->d = 0;
	if (!pr->minus)
	{
		if(pr->space < pr->len + 2)
			pr->res += 2;
		pr->space -= 2;
		{
			make_width(pr , 'p');
		}
		ft_putstr("0x");
		make_pres(pr, 'p');
		write(1, pr->s, pr->len);
	}
	else
	{
		ft_putstr("0x");
		if(pr->space < pr->len + 2)
			pr->res += 2;
		pr->space -= 2;
		make_pres(pr, 'p');
        write(1, pr->s, pr->len);
		make_width(pr , 'p');
	}
	if(pr->s != "")
		free(pr->s);
}