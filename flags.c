/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 13:44:58 by imarakho          #+#    #+#             */
/*   Updated: 2018/03/01 19:57:31 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char* concat(char *s1, char *s2) {

        size_t len1 = ft_strlen(s1);
        size_t len2 = ft_strlen(s2);                      
        char *result;
        
        result = (char *)malloc(len1 + len2 + 1);
        ft_memcpy(result, s1, len1);
        ft_memcpy(result + len1, s2, len2 + 1);    

        return result;
    }

void    make_pres(t_par *pr, char spec)
{
    if (pr->pres <= ft_strlen(pr->s))
    {
        if(pr->res < ft_strlen(pr->s))
            pr->res = ft_strlen(pr->s);
        return ;
    }
    if (pr->pres > 1)
    {
        if (pr->pres >= ft_strlen(pr->s))
        {
            pr->pres -= ft_strlen(pr->s);
            pr->res += pr->pres;
        }
         while (pr->pres > 0 && pr->pres--)
                ft_putchar('0');
    }
}

void	make_width(t_par *pr, char spec)
{ 
    if (!pr->wdth)
        return ;
    if (pr->space < ft_strlen(pr->s) && spec != 's')
    {
        pr->res -= pr->space;
        return ;
    }
            if(pr->pres > ft_strlen(pr->s))
            {
                if(spec != 's')
                pr->space -= pr->pres;
                else
                    pr->space -= ft_strlen(pr->s);
                if(pr->res > ft_strlen(pr->s))
                    pr->res -= ft_strlen(pr->s);
            }
         else if (spec != 's')
                pr->space -= ft_strlen(pr->s);
            else if (pr->pres > 1 && pr->pres < ft_strlen(pr->s))
            {
                pr->space -= pr->pres;
            }
        if (spec == '%' && pr->nll)
            pr->space--;
        if (pr->nll && !pr->minus && pr->pres <= 1)
            while (pr->space > 0 && pr->space--)
                ft_putchar('0');
        else
            while (pr->space > 0 && pr->space--)
            {
                if(pr->pres == 0 && pr->val == 0 && spec == 'd')
                    pr->res++;
                ft_putchar(' ');
            }
     return ;
}

void    parse_width(int *i, t_par *pr, const char *format)
{
    pr->wdth = 1;
    if(!ft_isdigit(format[*i]) || format[*i + 1] == '\0')
        return ;					
		pr->space = ft_atoi(&format[*i]);
        if (pr->res < pr->space)
            pr->res += pr->space;
		*i += ft_strlen(ft_itoa_base(pr->space, 10));
}

void    start_flags(t_par *pr)
{
    pr->alter = 0;
    pr->minus = 0;
    pr->plus = 0;
    pr->space = 0;
    pr->nll = 0;
    pr->wdth = 0;
    pr->flag = 1;
    pr->pres = 1;
    pr->md_sp = 0;
    pr->s = "";
    pr->sz = 0;
}

void    check_flags(const char *format, int *i, t_par *pr, va_list *ap)
{
    start_flags(pr);
    while (pr->flag)
    {
        if(format[*i] == '+')
        {
            pr->plus = 1;
            *i += 1;
        }
        else if(format[*i] == ' ')
        {
            pr->md_sp = 1;
            while (format[*i] == ' ')
                *i += 1;
        }
        else if(format[*i] == '-')
        {
            pr->minus = 1;
            *i += 1;
        }
        else if(format[*i] == '#')
        {
            pr->alter= 1;
            *i += 1;
        }
        else if (format[*i] == '0')
        {
            pr->nll = 1;
            *i += 1;
        }
        else if (format[*i] == '*')
                    {
                        pr->space = va_arg(*ap, int);
                        pr->wdth = 1;
                        if (pr->res < pr->space)
            pr->res += pr->space;
		*i += ft_strlen(ft_itoa_base(pr->space, 10));
                    }
        else if (format[*i] == '.')
        {
            *i += 1;

                    if(ft_isdigit(format[*i]))
                    {					
		                pr->pres = ft_atoi(&format[*i]);				
		                *i += ft_strlen(ft_itoa_base(pr->pres, 10));
	                }
                    else if (format[*i] == '*')
                    {
                        pr->pres = va_arg(*ap, int);
                        *i += 1;
                    }
                    else
                        pr->pres = 0;

        }
        else if(ft_isdigit(format[*i]) && format[*i] != '0')
        { 
            parse_width(i, pr, format);
        }
        else
            pr->flag = 0 ;
    }
    return ;
}