/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 09:53:09 by nmbabazi          #+#    #+#             */
/*   Updated: 2019/11/14 15:57:51 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t i;
	size_t l;

	i = 0;
	l = 0;
	while (dest[i] && size > 0)
	{
		i++;
		size--;
	}
	while (src[l] && size > 1)
	{
		dest[i] = src[l];
		i++;
		l++;
		size--;
	}
	if (size > 0)
		dest[i] = '\0';
	while (src[l])
	{
		l++;
		i++;
	}
	return (i);
}
