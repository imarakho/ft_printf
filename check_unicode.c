/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_unicode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 19:20:41 by imarakho          #+#    #+#             */
/*   Updated: 2018/02/23 17:13:31 by imarakho         ###   ########.fr       */
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
        unsigned int mask0 = 0xF0;
        unsigned int mask1 =  0x80;
        unsigned int mask2=  0x80;
        unsigned int mask3=  0x80;
         unsigned int v = 0;
         int size = 0;
        if (md == 'C')
        {
        v = pr->uval;
        size = ft_strlen(ft_unsitoa_base(pr->uval, 2));
         pr->s = ft_unsitoa_base(pr->uval, 2);
        }
        else
        {
        v = *pr->unval;
        size = ft_strlen(ft_unsitoa_base(*pr->unval, 2));
        pr->s = ft_unsitoa_base(*pr->unval, 2);
        }
         /* pr->d = -1;
        while (pr->s[++pr->d] != '\0')
                if (pr->s[pr->d] == ' ')
                        size--;
        pr->d = 0;*/
        unsigned int octet;
        if (pr->uval <= 0x007F)
        {
                if (md == 'C')
                        octet = pr->uval;
                else
                        octet = *pr->unval;
                write(1, &octet, 1);
                pr->res++;
        }
        else  if (pr->uval <= 0x07FF)
        {
                unsigned int cl =  pr->uval & 0x7000; 
       
                octet = mask0 | (cl >> 18); 
                write(1, &octet, 1);
                cl =  v & 0x03F000; 
                octet = mask1 | (cl >> 12);
                write(1, &octet, 1);
                pr->res += 2;

        }
        else  if (pr->uval <= 0x07FFF)
        {
               unsigned int cl =  pr->uval & 0x7000; 
       
                octet = mask0 | (cl >> 18); 
                write(1, &octet, 1);
                cl =  v & 0x03F000; 
                octet = mask1 | (cl >> 12);
                write(1, &octet, 1);
                cl = v & 0xFC0;
                octet = mask2 | (cl >> 6); 
                write(1, &octet, 1);
        }
        else
        {
                unsigned int cl =  pr->uval & 0x7000; 
       
                octet = mask0 | (cl >> 18); 
                write(1, &octet, 1);
                cl =  v & 0x03F000; 
                octet = mask1 | (cl >> 12);
                write(1, &octet, 1);
                cl = v & 0xFC0;
                octet = mask2 | (cl >> 6); 
                write(1, &octet, 1);
                octet = mask3 | (v & 0x003F); 
                write(1, &octet, 1);
                pr->res += 4;
        }
}

void    check_uncode(t_par *pr, va_list *ap, char md)
{
           pr->unval = (wchar_t *)va_arg(*ap, void *); 
           //while (pr->unval++)
           {
                   check_symbol(pr, ap, md);
           }
}