/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 15:28:28 by imarakho          #+#    #+#             */
/*   Updated: 2018/02/28 16:53:07 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void    check_int(t_par *pr, va_list *ap, char sz)
{
	pr->val = va_arg(*ap, intmax_t);
	make_size(pr, sz, ap);
	pr->s = ft_itoa_base(pr->val, 10);
	if(pr->pres == 0 && pr->val == 0)
		pr->s = "";
	if(ft_strlen(pr->s) > pr->space)
	{
		pr->res += ft_strlen(pr->s); 
	}
	 if (pr->space > 0 && pr->pres > pr->space)
	{
		pr->wdth = 0;
		 if(ft_strlen(pr->s) < pr->space)
			pr->res -= ft_strlen(pr->s);
		else
		{
			pr->res -= ft_strlen(pr->s);
			pr->res += (ft_strlen(pr->s) - pr->space);
		}
		//if(pr->res < pr->pres)
		//	pr->res = pr->pres;
	}
	if(pr->md_sp && !pr->plus && !pr->minus && pr->val >= 0 && pr->space < ft_strlen(pr->s))
	{
		ft_putchar(' ');
		pr->space--;
		pr->res++;	
	}
	if(!pr->minus)
	{
		if(pr->plus && pr->val >= 0 && (pr->nll || pr->pres > ft_strlen(pr->s) && pr->space < ft_strlen(pr->s)))
		{
			pr->plus = 0;
			ft_putchar('+');
			if(pr->space <= ft_strlen(pr->s) 
			&& pr->pres <= ft_strlen(pr->s))
			pr->res++;
			pr->space--;
		}
		if(pr->val < 0 && (pr->nll || pr->pres > 1))
		{
			pr->d = pr->val;
			pr->val *= -1;
			pr->s = ft_itoa_base(pr->val, 10);
			pr->plus = 0;
			//if (ft_strlen(pr->s) < pr->pres)
			//pr->res += ft_strlen(pr->s);
			if(pr->space > ft_strlen(pr->s))
				pr->space--;
			if(pr->nll)
				ft_putchar('-');
		}
		make_width(pr, 'd');
		if(pr->plus && pr->val >= 0 && (pr->nll || pr->pres > ft_strlen(pr->s)))
		{
			pr->plus = 0;
			ft_putchar('+');
			if(pr->space <= ft_strlen(pr->s) 
			&& pr->pres <= ft_strlen(pr->s))
			pr->res++;
		}
		if(pr->d < 0 && (!pr->nll || pr->pres > 1))
		{
			pr->d = 0;
			if (pr->res < pr->pres && ft_strlen(pr->s) < pr->space)
				pr->res += ft_strlen(pr->s);
			ft_putchar('-');
		}
		make_pres(pr, 'd');
	
		if(pr->plus && pr->val >= 0 && !pr->nll )
		{
			ft_putchar('+');
			if(pr->space <= ft_strlen(pr->s) 
			&& pr->pres <= ft_strlen(pr->s))
			pr->res++;
		}
		ft_putstr(pr->s);
	}
	else
	{
		if(pr->plus && pr->val >= 0 && (pr->nll || pr->pres > ft_strlen(pr->s)))
		{
			pr->plus = 0;
			ft_putchar('+');
			//if( pr->pres <= ft_strlen(pr->s))
			pr->res++;
			pr->space--;
		}
		make_pres(pr, 'd');
		ft_putstr(pr->s);
		make_width(pr, 'd');
	}
}

void    check_uns_int(t_par *pr, va_list *ap)
{
	pr->uval = va_arg(*ap, uintmax_t);
	make_size(pr, 'u', ap);
	if(pr->pres == 0 && pr->val == 0)
		pr->s = "";
	pr->s = ft_unsitoa_base(pr->uval, 10);
	if (pr->space < ft_strlen(pr->s))
		pr->res += ft_strlen(pr->s);
	/*else if(pr->pres > 1)
	{
		pr->res += pr->pres;
	}*/
	if (!pr->minus)
	{
		make_width(pr , 'u');
		make_pres(pr, 'd');
		ft_putstr(pr->s);
	}
	else
	{
		make_pres(pr, 'd');
		ft_putstr(pr->s);
		make_width(pr , 'u');
	}
}

void    check_uns_long(t_par *pr, va_list *ap)
{
	pr->uval = va_arg(*ap, uintmax_t);
	make_size(pr, 'U', ap);
	pr->s = ft_unsitoa_base(pr->uval, 10);
	if (pr->space < ft_strlen(pr->s))
		pr->res += ft_strlen(pr->s);
	if (!pr->minus)
	{
		make_width(pr , 'U');
		ft_putstr(pr->s);
	}
	else
	{
		ft_putstr(pr->s);
		make_width(pr , 'U');
	}
}

void    check_octal(t_par *pr,char sz, va_list *ap)
{
	pr->uval = va_arg(*ap, uintmax_t);
	make_size(pr, sz, ap);
	pr->s = ft_unsitoa_base(pr->uval, 8);
	/*if(ft_strlen(pr->s) > pr->space && ft_strlen(pr->s) > pr->pres)
	{
		ft_putstr(pr->s);
		pr->res += ft_strlen(pr->s);
		return ;
	}*/
	if (pr->space < ft_strlen(pr->s))
		pr->res += ft_strlen(pr->s);
	if (pr->pres == 0 && pr->uval == 0)
	{
		if(!pr->space && !pr->alter)
			pr->res--;
		pr->res +=  pr->space;
		free(pr->s);
		pr->s = "";
	}
	if (pr->pres == 0 && pr->uval != 0)
		pr->res++;
	if (((pr->alter && pr->uval != 0) || (pr->alter && pr->uval == 0 && pr->pres == 0)))
		{
			pr->s = concat("0", pr->s);
			if(!pr->space && pr->pres != 0)
				pr->res++;
		}
	if (!pr->minus)
	{
		make_width(pr , 'o');
		make_pres(pr, 'o');
		ft_putstr(pr->s);
	}
	else
	{
		if(pr->space > (pr->pres + ft_strlen(pr->s)))
		{
			pr->space -= pr->pres; 
			pr->space += ft_strlen(pr->s);
		}
		make_pres(pr, 'o');
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
		pr->res += ft_strlen(pr->s);
	if (pr->pres == 0 && pr->uval == 0)
	{
		if(pr->space)
			pr->res++;
		pr->res -= ft_strlen(pr->s);
		pr->res += pr->space;
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
		if(pr->alter && pr->nll && ft_strcmp(pr->s, "0"))
		{
			free(pr->s);
			pr->s = ft_unsitoa_base(pr->uval, 16);
				/*if(pr->res < ft_strlen(pr->s))
				{
					pr->res += 2;
					pr->space -= ft_strlen(pr->s) - 2;
				}*/
			pr->space -= 2;
			ft_putstr("0x");
		}
		make_width(pr , 'x');
		pr->d = -1;
		//make_prefix(pr);
		while(pr->s[++pr->d] != '\0')
			pr->s[pr->d] = ft_tolower(pr->s[pr->d]);
		pr->d = 0;
		make_pres(pr, 'x');
		ft_putstr(pr->s);
	}
	else
	{
		pr->d = -1;
		//make_prefix(pr);
		while(pr->s[++pr->d] != '\0')
			pr->s[pr->d] = ft_tolower(pr->s[pr->d]);
		pr->d = 0;
		/*if(pr->alter)
		{
				if(pr->res < ft_strlen(pr->s))
				{
					pr->res += 2;
					pr->space -= 2;
				}
			ft_putstr("0x");
		}*/
		make_pres(pr, 'x');
		ft_putstr(pr->s);
		make_width(pr , 'x');
	}
}

void    check_heX(t_par *pr, va_list *ap)
{
	pr->uval = va_arg(*ap, uintmax_t);
	make_size(pr, 'X', ap);
	pr->s = ft_unsitoa_base(pr->uval, 16);
	if (pr->space < ft_strlen(pr->s) && ft_strlen(pr->s))
		pr->res += ft_strlen(pr->s);
	if (pr->pres == 0)
	{
		if(pr->space)
			pr->res++;
		pr->res -= ft_strlen(pr->s);
		pr->res += pr->space;
		free(pr->s);
		pr->s = "";
	}
	else if (pr->alter && ft_strcmp(pr->s, "0"))
		{
				pr->s = concat("0X", pr->s);
				if(pr->res < ft_strlen(pr->s))
				{
					pr->res += 2;
					pr->space -= 2;
				}
		}
	if (!pr->minus)
	{
		if(pr->alter && pr->nll && ft_strcmp(pr->s, "0"))
		{
			free(pr->s);
			pr->s = ft_unsitoa_base(pr->uval, 16);
			pr->space -= 2;
			ft_putstr("0X");
		}
		make_width(pr , 'X');
		make_pres(pr, 'X');
		ft_putstr(pr->s);
	}
	else
	{
		make_pres(pr, 'X');
		ft_putstr(pr->s);
		make_width(pr , 'X');
	}
}