/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 15:28:28 by imarakho          #+#    #+#             */
/*   Updated: 2018/02/20 20:24:51 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void    check_int(t_par *pr, va_list *ap)
{
	//pr->val = va_arg(*ap, int);
	pr->val = va_arg(*ap, intmax_t);
	make_size(pr, 'd', ap);
	pr->s = ft_itoa_base(pr->val, 10);
	if (pr->space < ft_strlen(pr->s))
		pr->res += ft_strlen(pr->s)  - pr->space;
	if (!pr->minus)
	{
		//printf("%d\n", pr->space);
		//exit(1);
		//printf("pzd\n");
		make_width(pr , 'd');
		if (pr->plus && pr->val > 0)
		{
			pr->res++;
			ft_putchar('+');
		}
	//	if(pr->val)
			ft_putstr(pr->s);
	//	else
	//		pr->res--;
	}
	else
	{
		if(pr->plus && pr->val > 0)
		{
			pr->res++;
			ft_putchar('+');
		}
	//	if(pr->val)
			ft_putstr(pr->s);
		//else
	//		pr->res--;
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
	if (pr->space < ft_strlen(pr->s))
		pr->res += ft_strlen(pr->s) - pr->space;
	//pr->s = ft_itoa_base(va_arg(*ap, unsigned int), 10);
	if (!pr->minus)
	{
		make_width(pr , 'u');
		//if (pr->plus)
		//	ft_putchar('+');
		ft_putstr(pr->s);
	}
	else
	{
		//if(pr->plus)
		//	ft_putchar('+');
		ft_putstr(pr->s);
		make_width(pr , 'u');
	}
}

void    check_uns_long(t_par *pr, va_list *ap)
{
  //  *i += 1;
	//pr->uval = va_arg(*ap, unsigned int);
	pr->uval = va_arg(*ap, uintmax_t);
	make_size(pr, 'U', ap);
	pr->s = ft_unsitoa_base(pr->uval, 10);
	if (pr->space < ft_strlen(pr->s))
		pr->res += ft_strlen(pr->s)  - pr->space;
	//pr->s = ft_itoa_base(va_arg(*ap, unsigned int), 10);
	if (!pr->minus)
	{
		make_width(pr , 'U');
		//if (pr->plus)
		//	ft_putchar('+');
		ft_putstr(pr->s);
	}
	else
	{
		//if(pr->plus)
		//	ft_putchar('+');
		ft_putstr(pr->s);
		make_width(pr , 'U');
	}
}

void    check_octal(t_par *pr, va_list *ap)
{
	pr->uval = va_arg(*ap, uintmax_t);
	make_size(pr, 'o', ap);
	pr->s = ft_unsitoa_base(pr->uval, 8);
	if (pr->space < ft_strlen(pr->s))
		pr->res += ft_strlen(pr->s)  - pr->space;
	if (pr->alter && !ft_strcmp(pr->s, "0"))
		{
			pr->space--;
			pr->res++;
			pr->s = concat("0", pr->s);
		}
	if (!pr->minus)
	{
		make_width(pr , 'o');
		ft_putstr(pr->s);
	}
	else
	{
		ft_putstr(pr->s);
		make_width(pr , 'o');
	}
}

void    check_hex(t_par *pr, va_list *ap)
{
	pr->uval = va_arg(*ap, uintmax_t);
	make_size(pr, 'x', ap);
	pr->s = ft_unsitoa_base(pr->uval, 16);
	if (pr->space < ft_strlen(pr->s))
		pr->res += ft_strlen(pr->s)  - pr->space;
	if (pr->pres == 0)
	{
		pr->res -= ft_strlen(pr->s);
		free(pr->s);
		pr->s = "";
	}
	else if (pr->alter && ft_strcmp(pr->s, "0"))
		{
			//concat is not good variant
				pr->s = concat("0x", pr->s);
				if(pr->res < ft_strlen(pr->s))
				{
					pr->res += 2;
					pr->space -= 2;
				}
			//ft_putstr("0x");
		}
	if (!pr->minus)
	{
		if(ft_strlen(pr->s) <= pr->space)
			make_width(pr , 'x');
		pr->d = -1;
		/*if (pr->alter && ft_strcmp(pr->s, "0"))
		{
				if(pr->res < ft_strlen(pr->s))
				{
					pr->res += 2;
					pr->space -= 2;
				}
			ft_putstr("0x");
		}*/
		while(pr->s[++pr->d] != '\0')
			pr->s[pr->d] = ft_tolower(pr->s[pr->d]);
		pr->d = 0;
		ft_putstr(pr->s);
	}
	else
	{
		pr->d = -1;
		/*if (pr->alter && ft_strcmp(pr->s, "0"))
		{
				if(pr->res < ft_strlen(pr->s))
				{
					pr->res += 2;
					pr->space -= 2;
				}
			ft_putstr("0x");
		}*/
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
	if (pr->res < ft_strlen(pr->s))
	pr->res += ft_strlen(pr->s)  - pr->space;
	if (pr->alter     && ft_strcmp(pr->s, "0"))
		{
				pr->res += 2;
				//think about it
		//		pr->space -= 2;
				pr->s = concat("0X", pr->s);
			//ft_putstr("0x");
		}
	if (!pr->minus)
	{
		make_width(pr , 'X');
	/*	if (pr->alter)
		{
			pr->space--;
			pr->res += 2;
			ft_putstr("0X");
		}*/
		ft_putstr(pr->s);
	}
	else
	{
	/*if (pr->alter)
		{
			pr->space--;
			pr->res += 2;
			ft_putstr("0X");
		}*/
		ft_putstr(pr->s);
		make_width(pr , 'X');
	}
}