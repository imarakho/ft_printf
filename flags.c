/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 13:44:58 by imarakho          #+#    #+#             */
/*   Updated: 2018/02/18 18:08:05 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	make_width(t_par *pr, char spec)
{
    
 //   if(pr->space <= 0)
 //       return ;
	if ((spec == 'd' && pr->plus && pr->space != 0) || spec == '%')
		pr->space--;
   //  exit(1);
	if (pr->space > 0)
			{
				if (spec == 'c')
					pr->space -= 1;
				if(pr->space > ft_strlen(pr->s))
					pr->space -= ft_strlen(pr->s);
                if(pr->space > pr->pres)
                {
                    pr->space -= pr->pres;
                    if(pr->pres > 0 && ft_strlen(pr->s) < pr->pres)
                        pr->pres -= ft_strlen(pr->s);
                  //  if(pr->space > 0)
				    while (pr->space-- && pr->space > -1)
                    {
                    if (pr->nll && ! pr->minus)
                        ft_putchar('0');
                    else
					    ft_putchar(' ');
                    }
                    while(pr->pres-- && pr->pres > -1)
                        ft_putchar('0');
                }
                else if(pr->pres != 0)
                {
                    while (pr->space-- && pr->space > -1)
                         ft_putchar(' ');
                    pr->pres -= ft_strlen(pr->s);
                    if(pr->pres != 0)
                        while(pr->pres-- && pr->pres > -1)
                            ft_putchar('0');
                }
			}
        else
        {
            if(pr->pres > ft_strlen(pr->s))
                 pr->pres -= ft_strlen(pr->s);
            while(pr->pres-- && pr->pres > -1)
                            ft_putchar('0');
        }
        
}

void    parse_width(int *i, t_par *pr, const char *format)
{
    if (pr->plus)
        pr->space = 0;
    if(!ft_isdigit(format[*i]))
        return ;
	//while (ft_isdigit(format[*i]))
	{						
		pr->space = ft_atoi(&format[*i]);
        pr->res += ft_atoi(&format[*i]);					
		*i += ft_strlen(ft_itoa_base(pr->space, 10));
	}
	//*i -= 1;
}

void    start_flags(t_par *pr)
{
    pr->alter = 0;
    pr->minus = 0;
    pr->plus = 0;
    pr->space = 0;
    pr->nll = 0;
    pr->flag = 1;
    pr->pres = 0;
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
        if(format[*i] == ' ')
        {
            pr->res++;
            pr->space++;
            while (format[*i] == ' ')
            {
             //   printf("%d\n", pr->space);
                *i += 1;
            }
        }
        if(format[*i] == '-')
        {
            pr->minus = 1;
            *i += 1;
        }
        if(format[*i] == '#')
        {
            pr->alter= 1;
            *i += 1;
        }
        if (format[*i] == '0')
        {
            pr->nll = 1;
            *i += 1;
        }
        if (format[*i] == '.')
        {
            *i += 1;

                    if(ft_isdigit(format[*i]))
                    {						
		                pr->pres = ft_atoi(&format[*i]);
                       // exit (1);
                        pr->res += ft_atoi(&format[*i]);					
		                *i += ft_strlen(ft_itoa_base(pr->pres, 10));
	                }
                    else if (format[*i] == '*')
                    {
                    //    while (format[*i] != '*')
                     //       *i += 1;
                        pr->pres = va_arg(*ap, int);
                        *i += 1;
                    }

        }
        if(ft_isdigit(format[*i]) && format[*i] != '0')
        { 
            parse_width(i, pr, format);
         //   *i += 1;
        }
        else
            return ;
    }
    return ;
   /* if (format[*i + 1] == '+')
				{
					*i += 2;
					if(format[*i] != '-')
					{
					pr->d = 0;
					while(ft_isdigit(format[*i]))
						{						
							pr->d += ft_atoi(&format[*i]);						
							*i += 1;
						}
						//printf("%d\n", pr.d);
					//while(pr.d--)
					//	ft_putchar(' ');
					}
					*i -= 1;
				}*/
}