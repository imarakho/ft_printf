/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:41:31 by imarakho          #+#    #+#             */
/*   Updated: 2018/02/18 15:10:22 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char * format, ... )
{
	va_list ap;
	int i;
	t_par pr;
	pr.res = 0;

	va_start(ap, format);
	i = -1;
	while (format[++i] != '\0' && i < 21454544)
	{	
		if (format[i] == '%')
		{
			i++;
			//check_size(format, &pr, &i);
			check_flags(format, &i, &pr, &ap);
		if ((format[i] == 'd' || 
			format[i] == 'i' || format[i] == 'D'))
			check_int(&pr, &ap);
		else if ((format[i] == 'u' || format[i] == 'U'))
			check_uns_int(&pr, &ap);
		else if (format[i] == 'x')
			check_hex(&pr, &ap);
		else if (format[i] == 'X')
			check_heX(&pr, &ap);
		else if (format[i] == 'o')
			check_octal(&pr, &ap);
		else if (format[i] == '%')
		{
			make_width(&pr , '%');
			pr.res++;
			//i++;
			ft_putchar(format[i]);
			continue ;
		}
		else if ((format[i] == 's'))
			check_string(&pr, &ap);
		else if ((format[i] == 'c' || format[i] == 'C'))
		{
			check_char(&pr, &ap);
		}
		else if (format[i] == 'p')
			check_pointer(&pr, &ap);
		else if (format[i] == 'S')
		{
			i++;
			pr.s = va_arg(ap, char *);
			write(1, pr.s, ft_strlen(pr.s));
		}
	}
	else
	{
		pr.res++;
		ft_putchar(format[i]);
	}
	}
	va_end (ap);
	return (pr.res);
}
/*
int     main()
{
	//long int d1=123;
	printf ("%.     *d\n", 50, 44);
	ft_printf("%.   *d\n", 50, 44);
	return (0);
}*/
