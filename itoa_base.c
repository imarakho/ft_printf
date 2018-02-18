/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:10:46 by imarakho          #+#    #+#             */
/*   Updated: 2018/02/18 18:22:04 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long		ft_pow(uintmax_t nb, long pow)
{
	if (pow == 0)
		return (1);
	else
		return (nb * ft_pow(nb, pow - 1));
}

char	*ft_itoa_base(intmax_t value, int base)
{
	int		i;
	char	*num;
	int		min;

	i = 1;
	min = 0;
	if (value < 0)
	{
		if (base == 10)
			min = 1;
		value *= -1;
	}
	while (ft_pow(base, i) - 1 < value)
		i++;
	num = (char*)malloc(sizeof(num) * i);
	num[i + min] = '\0';
	while (i-- > 0)
	{
		num[i + min] = (value % base) + (value % base > 9 ? 'A' - 10 : '0');
		value = value / base;
	}
	if (min)
		num[0] = '-';
	return (num);
}

char	*ft_unsitoa_base(uintmax_t value, int base)
{
	int		i;
	char	*num;

	i = 1;
	while (ft_pow(base, i) - 1 < value)
		i++;
	num = (char*)malloc(sizeof(num) * i);
	num[i] = '\0';
	while (i-- > 0)
	{
		num[i] = (value % base) + (value % base > 9 ? 'A' - 10 : '0');
		value = value / base;
	}
	return (num);
}

char	*ft_itoa_baseptr(long value, int base)
{
	int		i;
	char	*num;
	int		min;

	i = 1;
	min = 0;
	while (ft_pow(base, i) - 1 < value)
		i++;
	num = (char*)malloc(sizeof(num) * (i));
	num[i + min] = '\0';
	while (i-- > 0)
	{
		num[i + min] = (value % base) + (value % base > 9 ? 'a' - 10 : '0');
		value = value / base;
	}
	if (min)
		num[0] = '-';
	return (num);
	return (0);
}