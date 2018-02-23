/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:41:31 by imarakho          #+#    #+#             */
/*   Updated: 2018/02/23 19:20:56 by imarakho         ###   ########.fr       */
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
	if (!ft_strcmp(format, "%"))
		return (0);
	while (format[++i] != '\0')
	{	
		if (format[i] == '%')
		{
			i++;
			check_flags(format, &i, &pr, &ap);
			check_size(format, &pr, &i);
		if (format[i] == 'd' || format[i] == 'i')
			check_int(&pr, &ap, 'd');
		else if (format[i] == 'D')
			check_int(&pr, &ap, 'D');
		else if (format[i] == 'u')
			check_uns_int(&pr, &ap);
		else if (format[i] == 'U')
			check_uns_long(&pr, &ap);	
		else if (format[i] == 'x')
			check_hex(&pr, &ap);
		else if (format[i] == 'X')
			check_heX(&pr, &ap);
		else if (format[i] == 'o')
			check_octal(&pr, 'o', &ap);
		else if (format[i] == 'O')
			check_octal(&pr, 'O', &ap);
		else if (format[i] == '%')
		{
			if (!pr.space || pr.res == 0)
			{
				pr.res++;
			}
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
		else if (format[i] == 'c')
			check_char(&pr, &ap, 'c');
		else if (format[i] == 'C')
			check_symbol(&pr, &ap, 'C');
		else if (format[i] == 'p')
			check_pointer(&pr, &ap);
		else if (format[i] == 'S')
			check_uncode(&pr, &ap, 'S');
	}
	else
	{
		pr.res++;
		ft_putchar(format[i]);
	}
	}
	va_end (ap);
//	if(pr.res == 0)
//		pr.res++;
	return (pr.res);
}
/*
int     main()
{
	//setlocale(LC_ALL, "");
	// char *s = setlocale(LC_ALL, "ы");
	//printf("%d\n" ,ft_printf("%\n"));
	//printf("%#.o\n", 42);
	//ft_printf("%#.o\n", 42);
	printf("%d\n" ,printf("%llx, %llx\n", 0, ULLONG_MAX));
	printf("%d\n" ,ft_printf("%llx, %llx\n", 0, ULLONG_MAX));
	return (0);
}
*/