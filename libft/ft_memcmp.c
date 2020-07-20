/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 14:23:38 by nmbabazi          #+#    #+#             */
/*   Updated: 2019/11/18 14:51:08 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>
#include <stdio.h>
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ps1;
	unsigned char	*ps2;

	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	while (*ps1 == *ps2 && --n)
	{
		ps1++;
		ps2++;
	}
	if (n > 0)
		return (*ps1 - *ps2);
	return (0);
}

int	main(void)
{
	printf("%d\n", ft_memcmp(NULL, "", 1));
	printf("%d\n", memcmp(NULL, "", 1));
}
