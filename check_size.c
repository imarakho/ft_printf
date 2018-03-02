/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 15:29:04 by imarakho          #+#    #+#             */
/*   Updated: 2018/03/02 17:09:36 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	make_size3(t_par *pr, char md)
{
	if (pr->sz == 'z')
	{
		if (md == 'c' || md == 'd')
			pr->val = (size_t)pr->val;
		else
			pr->uval = (size_t)pr->uval;
	}
}

void	make_size2(t_par *pr, char md)
{
	if (pr->sz == 'l')
	{
		if (md == 'd')
			pr->val = (long)pr->val;
		else if ((md == 'o' || md == 'x' || md == 'X'
		|| md == 'u' || md == 'U'))
			pr->uval = (unsigned long)pr->uval;
	}
	else if (pr->sz == 'm')
	{
		if (md == 'c' || md == 'd')
			pr->val = (long long)pr->val;
		else if (md == 'o' || md == 'x' || md == 'X' || md == 'u')
			pr->uval = (unsigned long long)pr->uval;
	}
	else if (pr->sz == 'j')
	{
		if (md == 'c' || md == 'd')
			pr->val = (intmax_t)pr->val;
		else if (md == 'o' || md == 'x' || md == 'X' || md == 'u')
			pr->uval = (uintmax_t)pr->uval;
	}
	else
		make_size3(pr, md);
}

void	make_size(t_par *pr, char md)
{
	if (pr->sz == 0)
	{
		if (md == 'c' || md == 'd')
			pr->val = (int)pr->val;
		else if (md == 'o' || md == 'x' || md == 'X' || md == 'u')
			pr->uval = (unsigned int)pr->uval;
		else if (md == 'U' || md == 'O' || md == 'D')
			pr->uval = (unsigned long)pr->uval;
	}
	if (pr->sz == 'c')
	{
		if (md == 'c' || md == 'd')
			pr->val = (char)pr->val;
		else if (md == 'o' || md == 'x' || md == 'X' || md == 'u')
			pr->uval = (unsigned char)pr->uval;
	}
	else if (pr->sz == 'h')
	{
		if (md == 'c' || md == 'd')
			pr->val = (short)pr->val;
		if (md == 'o' || md == 'x' || md == 'X' || md == 'u')
			pr->uval = (unsigned short)pr->uval;
	}
	make_size2(pr, md);
}

void	check_size2(const char *format, t_par *pr, int *i)
{
	if (format[*i] == 'l')
	{
		if (format[*i + 1] == 'l')
		{
			pr->sz = 'm';
			*i += 2;
		}
		else
		{
			pr->sz = 'l';
			*i += 1;
		}
	}
	else if (format[*i] == 'j')
	{
		pr->sz = 'j';
		*i += 1;
	}
	else if (format[*i] == 'z')
	{
		pr->sz = 'z';
		*i += 1;
	}
}

void	check_size(const char *format, t_par *pr, int *i)
{
	if (format[*i] == 'h')
	{
		if (format[*i + 1] == 'h')
		{
			pr->sz = 'c';
			*i += 2;
		}
		else
		{
			pr->sz = 'h';
			*i += 1;
		}
	}
	else
		check_size2(format, pr, i);
}
