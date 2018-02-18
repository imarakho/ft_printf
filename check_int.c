/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 15:28:28 by imarakho          #+#    #+#             */
/*   Updated: 2018/02/18 16:02:15 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void    check_int(t_par *pr, va_list *ap)
{
//	pr->val = va_arg(*ap, int);
	if(!make_size(pr, 'd'))
		pr->val = va_arg(*ap, int);
	pr->s = ft_itoa_base(pr->val, 10);
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
	//pr->val = va_arg(*ap, unsigned int);
	if(!make_size(pr, 'u'))
		pr->val = va_arg(*ap, unsigned int);
	pr->s = ft_itoa_base(pr->val, 10);
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
	//pr->val = va_arg(*ap, unsigned int);
	//make_size(pr, 'o');
	if(!make_size(pr, 'o'))
		pr->val = va_arg(*ap, unsigned int);
	pr->s = ft_itoa_base(pr->val, 8);
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
	//pr->val = va_arg(*ap, unsigned int);
	//make_size(pr, 'x');
	if(!make_size(pr, 'x'))
		pr->val = va_arg(*ap, unsigned int);
	pr->s = ft_itoa_base(pr->val, 16);
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
	//pr->val = va_arg(*ap, unsigned int);
	//make_size(pr, 'X');
	if(!make_size(pr, 'X'))
		pr->val = va_arg(*ap, unsigned int);
	pr->s = ft_itoa_base(pr->val, 16);
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