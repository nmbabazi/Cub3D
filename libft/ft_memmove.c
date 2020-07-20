/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 12:05:19 by nmbabazi          #+#    #+#             */
/*   Updated: 2019/11/14 09:42:58 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*pdest;
	unsigned char	*psrc;

	i = 0;
	psrc = (unsigned char *)src;
	pdest = (unsigned char *)dest;
	if (src == dest)
		return (dest);
	if (pdest > psrc)
	{
		while (++i <= n)
			pdest[n - i] = psrc[n - i];
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
