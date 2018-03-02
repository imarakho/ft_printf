/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:10:46 by imarakho          #+#    #+#             */
/*   Updated: 2018/03/02 19:04:21 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count_nums(unsigned long long int n, int base)
{
	int i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= base;
		i++;
	}
	return (i);
}

char		*ft_itoa_base(long long int value, int base)
{
	unsigned long long int	n;
	int						sign;
	int						len;
	char					*str;

	sign = 0;
	if (base < 2 || base > 16)
		return (0);
	if (base == 10 && value < 0)
		sign = 1;
	n = (value < 0 ?
	(unsigned long long int)-value : (unsigned long long int)value);
	len = ft_count_nums(n, base) + sign;
	str = (char*)malloc(sizeof(char) * len);
	str[len] = '\0';
	while (len > 0)
	{
		str[len - 1] = "0123456789ABCDEF"[n % base];
		n /= base;
		len--;
	}
	if (sign == 1)
		str[len] = '-';
	return (str);
}

char		*ft_unsitoa_base(unsigned long long int value, int base)
{
	unsigned long long int	n;
	int						sign;
	int						len;
	char					*str;

	sign = 0;
	if (base < 2 || base > 16)
		return (0);
	n = (unsigned long long int)value;
	len = ft_count_nums(n, base) + sign;
	str = (char*)malloc(sizeof(char) * len);
	str[len] = '\0';
	while (len > 0)
	{
		str[len - 1] = "0123456789ABCDEF"[n % base];
		n /= base;
		len--;
	}
	return (str);
}
