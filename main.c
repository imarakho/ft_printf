/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:41:31 by imarakho          #+#    #+#             */
/*   Updated: 2018/02/20 18:11:59 by imarakho         ###   ########.fr       */
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
	while (format[++i] != '\0')
	{	
		if (format[i] == '%')
		{
			i++;
			check_flags(format, &i, &pr, &ap);
			check_size(format, &pr, &i);
		if ((format[i] == 'd' || 
			format[i] == 'i' || format[i] == 'D'))
			check_int(&pr, &ap);
		else if (format[i] == 'u')
			check_uns_int(&pr, &ap);
		else if (format[i] == 'U')
			check_uns_long(&pr, &ap);	
		else if (format[i] == 'x')
			check_hex(&pr, &ap);
		else if (format[i] == 'X')
			check_heX(&pr, &ap);
		else if (format[i] == 'o')
			check_octal(&pr, &ap);
		else if (format[i] == '%')
		{
			if(pr.res == 0)
				pr.res++;
				if (!pr.minus)
				{
					make_width(&pr , '%');
					ft_putchar(format[i]);
				}
				else
				{
					ft_putchar(format[i]);
					make_width(&pr , '%');
				}
			//make_width(&pr , '%');
			//ft_putchar(format[i]);
		}
		else if ((format[i] == 's'))
			check_string(&pr, &ap);
		else if ((format[i] == 'c' || format[i] == 'C'))
		{
			check_char(&pr, &ap);
		}
		else if (format[i] == 'p')
			check_pointer(&pr, &ap);
		/*else if (format[i] == 'S')
		{
			i++;
			pr.s = va_arg(ap, char *);
			write(1, pr.s, ft_strlen(pr.s));
		}*/
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
	printf("%5.2x\n", 5427);
	ft_printf("%5.2x\n", 5427);
	return (0);
}
*/