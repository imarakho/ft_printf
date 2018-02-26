/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 15:28:28 by imarakho          #+#    #+#             */
/*   Updated: 2018/02/26 14:57:10 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void    check_int(t_par *pr, va_list *ap, char sz)
{
	pr->val = va_arg(*ap, intmax_t);
	make_size(pr, sz, ap);
	pr->s = ft_itoa_base(pr->val, 10);
	if (pr->space < ft_strlen(pr->s))
		pr->res += ft_strlen(pr->s);
	if(pr->md_sp && pr->space < pr->pres &&
	 pr->val > 0 && !pr->plus)
	{
		pr->res++;
		ft_putchar(' ');
		//ft_putstr(pr->s);
		//return ;
	}
	if (pr->space < pr->pres)
		pr->wdth = 0;
	if (pr->pres == 0 && pr->val == 0)
	{
		if(!pr->space && !pr->alter)
			pr->res--;
	   pr->res += pr->space;
		free(pr->s);
		pr->s = "";
	}
	if (pr->pres > 1 && pr->pres > pr->space)
	{
		if(pr->pres > ft_strlen(pr->s))
			if(pr->space)
				pr->res -= pr->space;
		if(pr->space)
			pr->res +=  pr->pres;
	}
	if (!pr->minus)
	{
		if(pr->space > pr->pres && pr->pres > 1 /*&& pr->pres >= ft_strlen(pr->s)*/)
		{
		//	pr->space--;
			pr->res--;
		}
		if (pr->plus && pr->val >= 0 && (pr->nll || 
		(pr->pres > ft_strlen(pr->s) && pr->pres > pr->space)))
		{
				pr->space--;
				ft_putchar('+');
		}
		if (pr->val < 0 && (pr->nll || pr->pres > 1))
		{
			pr->val *= -1;
			pr->s = ft_itoa_base(pr->val, 10);
			if(ft_strlen(pr->s) > pr->space || ft_strlen(pr->s) > pr->pres)
				pr->space--;
			else
			{
				pr->res++;
				pr->pres--;
			}
			ft_putchar('-');
		}
		if (pr->plus && pr->val >= 0 && !pr->nll)
			{
				if(pr->space < ft_strlen(pr->s))
				pr->res++;
				pr->space--;
			}
		make_width(pr , 'd');
		if (pr->plus && pr->val >= 0 && !pr->nll)
			ft_putchar('+');
			make_pres(pr, 'd');
			ft_putstr(pr->s);
			return ;
	}
	else
	{
		if(pr->space > pr->pres && pr->pres > 1)
			pr->space--;
		if(pr->plus && pr->val >= 0)
		{
			if(ft_strlen(pr->s) > pr->space || ft_strlen(pr->s) > pr->pres)
				pr->res++;
			else
				pr->space--;
			ft_putchar('+');
		}
			make_pres(pr, 'd');
			ft_putstr(pr->s);
		make_width(pr , 'd');
	}
}

void    check_uns_int(t_par *pr, va_list *ap)
{
	pr->uval = va_arg(*ap, uintmax_t);
	make_size(pr, 'u', ap);
	pr->s = ft_unsitoa_base(pr->uval, 10);
	if (pr->space < ft_strlen(pr->s))
		pr->res += ft_strlen(pr->s);
	else if(pr->pres > 1)
	{
		pr->res += pr->pres;
	}
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
  //  *i += 1;
	//pr->uval = va_arg(*ap, unsigned int);
	pr->uval = va_arg(*ap, uintmax_t);
	make_size(pr, 'U', ap);
	pr->s = ft_unsitoa_base(pr->uval, 10);
	if (pr->space < ft_strlen(pr->s))
		pr->res += ft_strlen(pr->s);
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

void    check_octal(t_par *pr,char sz, va_list *ap)
{
	pr->uval = va_arg(*ap, uintmax_t);
	make_size(pr, sz, ap);
	pr->s = ft_unsitoa_base(pr->uval, 8);
	if (pr->space < ft_strlen(pr->s))
	{
		pr->res += ft_strlen(pr->s);
	}
	if (pr->pres == 0 && pr->uval == 0)
	{
		if(!pr->space && !pr->alter)
		{
			pr->res--;
		}
		pr->res +=  pr->space;
		free(pr->s);
		pr->s = "";
	}
	else if (pr->pres >= 1 && pr->pres > pr->space)
	{

		pr->res -= pr->space;
		pr->wdth = 0;
		if(pr->space)
			pr->res +=  pr->pres;
	}
	if (pr->pres == 0 && pr->uval != 0)
		pr->res++;
	if ((pr->alter && pr->uval != 0) || (pr->alter && pr->uval == 0 && pr->pres == 0))
		{
			pr->s = concat("0", pr->s);
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
	if (pr->space < ft_strlen(pr->s) && ft_strlen(pr->s))
		pr->res += ft_strlen(pr->s)  - pr->space;
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
		if(ft_strlen(pr->s) <= pr->space)
			make_width(pr , 'x');
		pr->d = -1;
		//make_prefix(pr);
		while(pr->s[++pr->d] != '\0')
			pr->s[pr->d] = ft_tolower(pr->s[pr->d]);
		pr->d = 0;
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
		pr->res += ft_strlen(pr->s)  - pr->space;
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
		if(ft_strlen(pr->s) <= pr->space)
			make_width(pr , 'X');
		ft_putstr(pr->s);
	}
	else
	{
		ft_putstr(pr->s);
		make_width(pr , 'X');
	}
	/*pr->uval = va_arg(*ap, uintmax_t);
	make_size(pr, 'X', ap);
	pr->s = ft_unsitoa_base(pr->uval, 16);
	if (pr->res < ft_strlen(pr->s))
	pr->res += ft_strlen(pr->s)  - pr->space;
	if (pr->alter     && ft_strcmp(pr->s, "0"))
		{
				pr->res += 2;
				pr->s = concat("0X", pr->s);
		}
	if (!pr->minus)
	{
		make_width(pr , 'X');
		ft_putstr(pr->s);
	}
	else
	{
		ft_putstr(pr->s);
		make_width(pr , 'X');
	}*/
}