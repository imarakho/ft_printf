/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 15:28:28 by imarakho          #+#    #+#             */
/*   Updated: 2018/02/18 19:25:02 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void    check_int(t_par *pr, va_list *ap)
{
	//pr->val = va_arg(*ap, int);
	pr->val = va_arg(*ap, intmax_t);
	make_size(pr, 'd', ap);
	pr->s = ft_itoa_base(pr->val, 10);
	pr->res += ft_strlen(pr->s);
	if (!pr->minus)
	{
		//printf("%d\n", pr->space);
		//exit(1);
		//printf("pzd\n");
		make_width(pr , 'd');
		if (pr->plus)
			ft_putchar('+');
		ft_putstr(pr->s);
	}
	else
	{
		if(pr->plus)
			ft_putchar('+');
		ft_putstr(pr->s);
		make_width(pr , 'd');
	}
}

void    check_uns_int(t_par *pr, va_list *ap)
{
  //  *i += 1;
	//pr->uval = va_arg(*ap, unsigned int);
	pr->uval = va_arg(*ap, uintmax_t);
	make_size(pr, 'u', ap);
	pr->s = ft_unsitoa_base(pr->uval, 10);
	pr->res += ft_strlen(pr->s);
	//pr->s = ft_itoa_base(va_arg(*ap, unsigned int), 10);
	if (!pr->minus)
	{
		make_width(pr , 'u');
		if (pr->plus)
			ft_putchar('+');
		ft_putstr(pr->s);
	}
	else
	{
		if(pr->plus)
			ft_putchar('+');
		ft_putstr(pr->s);
		make_width(pr , 'u');
	}
}

void    check_octal(t_par *pr, va_list *ap)
{
	//pr->uval = va_arg(*ap, unsigned int);
	pr->uval = va_arg(*ap, uintmax_t);
	make_size(pr, 'o', ap);
	pr->s = ft_unsitoa_base(pr->uval, 8);
	pr->res += ft_strlen(pr->s);
	//pr->s = ft_itoa_base(va_arg(*ap, unsigned int), 8);
	if (!pr->minus)
	{
		make_width(pr , 'o');
		if (pr->alter)
		{
			pr->space--;
			ft_putchar('0');
		}
		ft_putstr(pr->s);
	}
	else
	{
		if (pr->alter)
		{
			pr->space--;
			ft_putchar('0');
		}
		ft_putstr(pr->s);
		make_width(pr , 'o');
	}
}

void    check_hex(t_par *pr, va_list *ap)
{
	//pr->uval = va_arg(*ap, unsigned int);
	pr->uval = va_arg(*ap, uintmax_t);
	make_size(pr, 'x', ap);
	pr->s = ft_unsitoa_base(pr->uval, 16);
	pr->res += ft_strlen(pr->s);
	//pr->s = ft_itoa_base(va_arg(*ap, unsigned int), 16);
	if (!pr->minus)
	{
		make_width(pr , 'x');
		if (pr->alter)
		{
			pr->space -= 2;
			ft_putstr("0x");
		}
		pr->d = -1;			
		while(pr->s[++pr->d] != '\0')
			pr->s[pr->d] = ft_tolower(pr->s[pr->d]);
		pr->d = 0;
		ft_putstr(pr->s);
	}
	else
	{
		if (pr->alter)
		{
			pr->space--;
			ft_putstr("0x");
		}
		pr->d = -1;
		while(pr->s[++pr->d] != '\0')
			pr->s[pr->d] = ft_tolower(pr->s[pr->d]);
		pr->d = 0;
		ft_putstr(pr->s);
		make_width(pr , 'x');
	}
}

void    check_heX(t_par *pr, va_list *ap)
{
	//pr->val = va_arg(*ap, intmax_t);
	pr->uval = va_arg(*ap, uintmax_t);
	make_size(pr, 'X', ap);
	pr->s = ft_unsitoa_base(pr->uval, 16);
	pr->res += ft_strlen(pr->s);
	//pr->s = ft_itoa_base(va_arg(*ap, unsigned int), 16);
	if (!pr->minus)
	{
		make_width(pr , 'X');
		if (pr->alter)
		{
			pr->space--;
			ft_putstr("0X");
		}
		ft_putstr(pr->s);
	}
	else
	{
		if (pr->alter)
		{
			pr->space--;
			ft_putstr("0X");
		}
		ft_putstr(pr->s);
		make_width(pr , 'X');
	}
}