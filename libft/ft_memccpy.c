/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:05:02 by nmbabazi          #+#    #+#             */
/*   Updated: 2019/11/13 16:12:32 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	*t;
	size_t			i;

	p = (unsigned char *)dest;
	t = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		p[i] = t[i];
		if (t[i] == (unsigned char)c)
			return (&p[i + 1]);
		i++;
	}
	return (0);
}
