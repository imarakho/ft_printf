/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 15:28:28 by imarakho          #+#    #+#             */
/*   Updated: 2018/03/02 15:38:59 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	int_checks(t_par *pr)
{
	if (pr->pres == 0 && pr->val == 0)
	{
		free(pr->s);
		pr->s = "";
	}
	pr->len = ft_strlen(pr->s);
	if (pr->minus && pr->pres - pr->len == 1 && !pr->plus)
	{
		pr->res--;
		pr->space--;
	}
	if (pr->len > pr->space)
	{
		pr->res += pr->len; 
	}
	if (pr->space > 0 && pr->pres > pr->space)
	{
		pr->wdth = 0;
		if (pr->len < pr->space)
			pr->res -= pr->len;
		else
		{
			pr->res -= pr->len;
			pr->res += (pr->len - pr->space);
		}
	}

}

void	check_int(t_par *pr, va_list *ap, char sz)
{
	int st_sp;
	
	st_sp = pr->space;
	pr->val = va_arg(*ap, intmax_t);
	make_size(pr, sz);
	ft_strcmp(pr->s, "")? pr->s = "" : 0;
	pr->s = ft_itoa_base(pr->val, 10);
	int_checks(pr);
	if (pr->md_sp && !pr->plus && !pr->minus && pr->val >= 0)
	{
		ft_putchar(' ');
		pr->space--;
		if (pr->space <= 0)
			pr->res++;	
	}
	if (!pr->minus)
	{
		if (pr->plus && pr->val >= 0 && (pr->nll || pr->pres > pr->len))
		{
			if (pr->nll)
			{
				pr->plus = 0;
				ft_putchar('+');
			}
			if (pr->space <= pr->len
			&& pr->pres <= pr->len && pr->val == 0)
				pr->res++;
			pr->space--;
		}
		if (pr->val < 0 && (pr->nll || pr->pres > 1))
		{
			pr->d = pr->val;
			pr->val *= -1;
			pr->s = ft_itoa_base(pr->val, 10);
			pr->len = ft_strlen(pr->s);
			pr->plus = 0;
			if (pr->space > pr->len)
				pr->space--;
			if (pr->nll)
				ft_putchar('-');
		}
		make_width(pr, 'd');
		if (pr->d < 0 && (!pr->nll || pr->pres > 1))
		{
			pr->d = 0;
			if (pr->res < pr->pres && pr->len < pr->space)
				pr->res += pr->len;
			if (!pr->nll)
			ft_putchar('-');
		}
		if (pr->plus && pr->val >= 0 && pr->pres > pr->len)
		{
			pr->plus = 0; 
			ft_putchar('+');
			if (pr->space <= pr->len 
			&& pr->pres <= pr->len)
			pr->res++;
		}
		make_pres(pr, 'd');
	
		if (pr->plus && pr->val >= 0 )
		{
			ft_putchar('+');
			if (pr->space <= pr->len 
			&& pr->pres <= pr->len)
			pr->res++;
		}
		write(1, pr->s, ft_strlen(pr->s));
	}
	else
	{
		if (pr->plus && pr->val >= 0)
		{
			pr->plus = 0;
			ft_putchar('+');
			pr->res--;
			pr->space -= 2;
		}
		make_pres(pr, 'd');
		write(1, pr->s, ft_strlen(pr->s));
		make_width(pr, 'd');
	}
	pr->res < st_sp ?pr->res = st_sp : 0;
	ft_strcmp(pr->s, "") ? free(pr->s) : 0;
}

void	check_uns_int(t_par *pr, va_list *ap)
{
	pr->uval = va_arg(*ap, uintmax_t);
	make_size(pr, 'u');
	if (ft_strcmp(pr->s, ""))
		free(pr->s);
	pr->s = ft_unsitoa_base(pr->uval, 10);
	if (pr->pres == 0 && pr->uval == 0)
		pr->s = "";
	pr->len = ft_strlen(pr->s);
	if (pr->space < pr->len)
		pr->res += pr->len;
	if (!pr->minus)
	{
		make_width(pr, 'u');
		make_pres(pr, 'd');
		write(1, pr->s, pr->len);
	}
	else
	{
		make_pres(pr, 'd');
		write(1, pr->s, pr->len);
		make_width(pr, 'u');
	}
	if (ft_strcmp(pr->s, ""))
		free(pr->s);
}

void	check_uns_long(t_par *pr, va_list *ap)
{
	pr->uval = va_arg(*ap, uintmax_t);
	make_size(pr, 'U');
	if (ft_strcmp(pr->s, ""))
		free(pr->s);
	pr->s = ft_unsitoa_base(pr->uval, 10);
	if (pr->pres == 0 && pr->val == 0)
	{
		free(pr->s);
		pr->s = "";
	}
	pr->len = ft_strlen(pr->s);
	if (pr->space < pr->len)
		pr->res += pr->len;
	if (!pr->minus)
	{
		make_width(pr, 'U');
		write(1, pr->s, pr->len);
	}
	else
	{
		write(1, pr->s, pr->len);
		make_width(pr, 'U');
	}
	if (ft_strcmp(pr->s, ""))
		free(pr->s);
}

void	check_octal(t_par *pr,char sz, va_list *ap)
{
	pr->uval = va_arg(*ap, uintmax_t);
	make_size(pr, sz);
	if (ft_strcmp(pr->s, ""))
		free(pr->s);
	pr->s = ft_unsitoa_base(pr->uval, 8);
	if (pr->pres == 0 && pr->uval == 0)
	{
		pr->res +=  pr->space;
		free(pr->s);
		pr->s = "";
	}
	if (((pr->alter && pr->uval != 0) || (pr->alter && pr->uval == 0 && pr->pres == 0)))
		pr->s = concat("0", pr->s);
	pr->len = ft_strlen(pr->s);
	if (pr->space < pr->len && pr->len > 0)
		pr->res += pr->len;
	if (pr->space < pr->pres && pr->minus)
	{
		pr->wdth = 0;
		pr->res--;
	}
	if (!pr->minus)
	{
		make_width(pr, 'o');
		make_pres(pr, 'o');
		write(1, pr->s, pr->len);
	}
	else
	{
		if (pr->space > (pr->pres + pr->len))
		{
			pr->space -= pr->pres; 
			pr->space += pr->len;
			pr->res--;
		}
		make_pres(pr, 'o');
		write(1, pr->s, pr->len);
		make_width(pr, 'o');
	}
	if (ft_strcmp(pr->s, ""))
		free(pr->s);
}
void	check_hex(t_par *pr, va_list *ap)
{
	pr->uval = va_arg(*ap, unsigned long);
	make_size(pr, 'x');
//	if (ft_strcmp(pr->s, ""))
//		free(pr->s);
	pr->s = ft_unsitoa_base(pr->uval, 16);
	if (pr->pres == 0 && pr->uval == 0)
	{
		if (pr->space)
			pr->res += pr->space;
		free(pr->s);
		pr->s = "";
	}
	 else if (pr->alter && ft_strcmp(pr->s, "0"))
	{
		pr->s = concat("0x", pr->s);
		if ((unsigned long)pr->res < ft_strlen(pr->s))
			pr->space -= 2;
	}
	pr->len = ft_strlen(pr->s);
	if (pr->space < pr->len)
		pr->res += pr->len;
	if (!pr->minus)
	{
		if (pr->alter && pr->nll && ft_strcmp(pr->s, "0"))
		{
			free(pr->s);
			pr->s = ft_unsitoa_base(pr->uval, 16);
			pr->space -= 2;
			write(1, "0x", 2);
		}
		make_width(pr, 'x');
		pr->d = -1;
		while (pr->s[++pr->d] != '\0')
			pr->s[pr->d] = ft_tolower(pr->s[pr->d]);
		pr->d = 0;
		make_pres(pr, 'x');
		write(1, pr->s, ft_strlen(pr->s));
	}
	else
	{
		pr->d = -1;
		while (pr->s[++pr->d] != '\0')
			pr->s[pr->d] = ft_tolower(pr->s[pr->d]);
		pr->d = 0;
		make_pres(pr, 'x');
		write(1, pr->s, ft_strlen(pr->s));
		make_width(pr, 'x');
	}
	//if (ft_strcmp(pr->s, "")) //with a question
	//	free(pr->s);
}

void	check_hexb(t_par *pr, va_list *ap)
{
	pr->uval = va_arg(*ap, uintmax_t);
	make_size(pr, 'X');
	if (ft_strcmp(pr->s, ""))
		free(pr->s);
	pr->s = ft_unsitoa_base(pr->uval, 16);
	if (pr->pres == 0 && pr->uval == 0)
	{
		if (pr->space)
			pr->res += pr->space;
		free(pr->s);
		pr->s = "";
	}
	pr->len = ft_strlen(pr->s);
	if (pr->space < pr->len)
		pr->res += pr->len;
	if (!pr->minus)
	{
		if (pr->alter && pr->nll && ft_strcmp(pr->s, "0"))
		{
			pr->space -= 2;
			write(1, "0X", 2);
		}
		make_width(pr, 'X');
		if (pr->alter && ft_strcmp(pr->s, "0"))
		{
			write(1, "0X", 2);
			pr->res += 2;
			pr->space -= 2;
		}
		make_pres(pr, 'X');
		write(1, pr->s, ft_strlen(pr->s));
	}
	else
	{
		make_pres(pr, 'X');
		write(1, pr->s, ft_strlen(pr->s));
		make_width(pr, 'X');
	}
	if (ft_strcmp(pr->s, ""))
		free(pr->s);
}