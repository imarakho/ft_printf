/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_unicode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 19:20:41 by imarakho          #+#    #+#             */
/*   Updated: 2018/02/23 16:32:54 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void    check_symbol(t_par *pr, va_list *ap, char md)
{
        if(md == 'C')
        {
                pr->uval = va_arg(*ap, wchar_t);
                make_size(pr, 'C', ap);
        }
        else
             make_size(pr, 'S', ap);   
        unsigned int mask0 = 0;
        unsigned int mask1 = 49280;
        unsigned int mask2= 14712960;
        unsigned int mask3= 4034953344;
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
        printf("size:%d\n", size);
          pr->d = -1;
        while (pr->s[++pr->d] != '\0')
                if (pr->s[pr->d] == ' ')
                        size--;
        pr->d = 0;
        unsigned char octet;
 
        if (size <= 7)
        {
                octet = pr->uval;
                write(1, &octet, 1);
                pr->res++;
        }
        else  if (size <= 11)
        {
                unsigned char o2 = (v << 26) >> 26; 
                unsigned char o1 = ((v >> 6) << 27) >> 27; 
       
                octet = (mask1 >> 8) | o1; 
                write(1, &octet, 1);
                octet = ((mask1 << 24) >> 24) | o2; 
                write(1, &octet, 1);
                pr->res += 2;

        }
        else  if (size <= 16)
        {
                unsigned char o3 = (v << 26) >> 26; 
                unsigned char o2 = ((v >> 6) << 26) >> 26;
                unsigned char o1 = ((v >> 12) << 28) >> 28;
       
                octet = (mask2 >> 16) | o1; 
                write(1, &octet, 1);
                octet = ((mask2 << 16) >> 24) | o2; 
                write(1, &octet, 1);
                octet = ((mask2 << 24) >> 24) | o3; 
                write(1, &octet, 1);
                pr->res += 3;
        }
        else
        {
                unsigned char o4 = (v << 26) >> 26; 
                unsigned char o3 = ((v >> 6) << 26) >> 26;
                unsigned char o2 = ((v >> 12) << 26) >> 26; 
                unsigned char o1 = ((v >> 18) << 29) >> 29; 
       
                octet = (mask3 >> 24) | o1; 
                write(1, &octet, 1);
                octet = ((mask3 << 8) >> 24) | o2;
                write(1, &octet, 1);
                octet = ((mask3 << 16) >> 24) | o3; 
                write(1, &octet, 1);
                octet = ((mask3 << 24) >> 24) | o4; 
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