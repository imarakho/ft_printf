/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_unicode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 19:20:41 by imarakho          #+#    #+#             */
/*   Updated: 2018/03/01 19:40:13 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void    check_symbol(t_par *pr, va_list *ap, char md)
{
        if(md == 'C')
        {
                pr->uval = va_arg(*ap, unsigned int);
                make_size(pr, 'C', ap);
        }
        else
             make_size(pr, 'S', ap);   
        pr->mask[0] = 0;
        pr->mask[1] = 49280;
        pr->mask[2] = 14712960;
        pr->mask[3] = 4034953344;
         unsigned int v = 0;
         int size = 0;
        if (md == 'C')
        {
        v = pr->uval;
        size = ft_strlen(ft_unsitoa_base(pr->uval, 2));
       // if(pr->s != "")
       // free(pr->s);
         pr->s = ft_unsitoa_base(pr->uval, 2);
        }
        else
        {
        v = *pr->unval;
        size = ft_strlen(ft_unsitoa_base(*pr->unval, 2));
        //if(pr->s != "")
      //  free(pr->s);
        pr->s = ft_unsitoa_base(*pr->unval, 2);
        }
        unsigned int octet;
        if (size <= 7)
        {
                if (md == 'C')
                        octet = pr->uval;
                else
                        octet = *pr->unval;
                write(1, &octet, 1);
                pr->res++;
        }
        else  if (size <= 11)
        {
                unsigned int o2 = (v << 26) >> 26; 
                unsigned int o1 = ((v >> 6) << 27) >> 27; 
       
                octet = (pr->mask[1] >> 8) | o1; 
                write(1, &octet, 1);
                octet = ((pr->mask[1] << 24) >> 24) | o2; 
                write(1, &octet, 1);
                pr->res += 2;

        }
        else  if (size <= 16)
        {
                unsigned int o3 = (v << 26) >> 26; 
                unsigned int o2 = ((v >> 6) << 26) >> 26;
                unsigned int o1 = ((v >> 12) << 28) >> 28;
       
                octet = (pr->mask[2] >> 16) | o1; 
                write(1, &octet, 1);
                octet = ((pr->mask[2] << 16) >> 24) | o2; 
                write(1, &octet, 1);
                octet = ((pr->mask[2] << 24) >> 24) | o3; 
                write(1, &octet, 1);
                pr->res += 3;
        }
        else
        {
                unsigned int o4 = (v << 26) >> 26; 
                unsigned int o3 = ((v >> 6) << 26) >> 26;
                unsigned int o2 = ((v >> 12) << 26) >> 26; 
                unsigned int o1 = ((v >> 18) << 29) >> 29; 
       
                octet = (pr->mask[3] >> 24) | o1; 
                write(1, &octet, 1);
                octet = ((pr->mask[3] << 8) >> 24) | o2;
                write(1, &octet, 1);
                octet = ((pr->mask[3] << 16) >> 24) | o3; 
                write(1, &octet, 1);
                octet = ((pr->mask[3] << 24) >> 24) | o4; 
                write(1, &octet, 1);
                pr->res += 4;
        }
}

void    check_uncode(t_par *pr, va_list *ap, char md)
{
        int len = 0;
        int i = -1;

        pr->unval = (wchar_t *)va_arg(*ap, void*);
        if (pr->unval ==  NULL)
        {
                write(1, "(null)", 6);
		pr->res += 6;
                return ;
        }
           while (pr->unval[len])
                len++;
        if(pr->pres < len && pr->pres > 1)
        {
                pr->pres--;
                len = pr->pres;
        }
       // if (!pr->minus)
        {
           while (++i < len)
           {
                   check_symbol(pr, ap, md);
                    pr->unval++;
           }
        }
       /* else
        {
                while (++i < len)
           {
                   check_symbol(pr, ap, md);
                    pr->unval++;
           }
        }*/
}