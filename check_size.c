/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 15:29:04 by imarakho          #+#    #+#             */
/*   Updated: 2018/02/18 15:34:34 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	make_size(t_par *pr, char md)
{
	if (pr->sz == 'c')
	{
		if (md == 'd')
			pr->val = (char)pr->val;
		if (md == 'o' || md == 'x' || md == 'X' || md == 'u')
			pr->val = (unsigned char)pr->val;
	}
	else if (pr->sz == 'h')
	{
		if (md == 'd')
			pr->val = (short)pr->val;
		if (md == 'o' || md == 'x' || md == 'X' || md == 'u')
			pr->val = (unsigned short)pr->val;
	}
	else if (pr->sz == 'l')
	{
		if (md == 'd')
			pr->val = (long)pr->val;
		if (md == 'o' || md == 'x' || md == 'X' || md == 'u')
			pr->val = (unsigned long)pr->val;
	}
	else if (pr->sz == 'm')
	{
		if (md == 'd')
			pr->val = (long long)pr->val;
		if (md == 'o' || md == 'x' || md == 'X' || md == 'u')
			pr->val = (unsigned long long)pr->val;
	}
	else if (pr->sz == 'j')
	{
		if (md == 'd')
			pr->val = (intmax_t)pr->val;
		if (md == 'o' || md == 'x' || md == 'X' || md == 'u')
			pr->val = (uintmax_t)pr->val;
	}
	else if (pr->sz == 'z')
	{
		pr->val = (size_t)pr->val;
	}
		
}

void    check_size(const char *format, t_par *pr, int *i)
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
	else if (format[*i] == 'l')
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
		pr->sz = 'j';
		*i += 1;
	}
}