/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:10:46 by imarakho          #+#    #+#             */
/*   Updated: 2018/02/18 18:28:20 by imarakho         ###   ########.fr       */
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
	int				sign;
	int				len;
	char			*str;

	sign = 0;
	if (base < 2 || base > 16)
		return (0);
	if (base == 10 && value < 0)
		sign = 1;
	n = (value < 0 ? (unsigned long long int)-value : (unsigned long long int)value);
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

char		*ft_unsitoa_base(unsigned long int value,  int base)
{
	unsigned long long int	n;
	int				sign;
	int				len;
	char			*str;

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
/*
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
}*/