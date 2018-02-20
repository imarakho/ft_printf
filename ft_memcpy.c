/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:06:09 by smykyten          #+#    #+#             */
/*   Updated: 2018/02/20 17:27:42 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	char		*pdst;
	char const	*psrc;
	size_t		i;

	i = 0;
	pdst = dst;
	psrc = src;
	if (n == 0 || pdst == psrc)
		return (dst);
	while (i < n)
	{
		pdst[i] = psrc[i];
		i++;
	}
	return (dst);
}
