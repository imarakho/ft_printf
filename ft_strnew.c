/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 19:35:48 by smykyten          #+#    #+#             */
/*   Updated: 2018/03/01 18:24:58 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strnew(size_t size)
{
	char	*ret;

	ret = ft_memalloc(size + 1);
	if (ret)
	{
		while (size)
		{
			ret[size - 1] = '\0';
			size--;
		}
		return (ret);
	}
	return (NULL);
}
