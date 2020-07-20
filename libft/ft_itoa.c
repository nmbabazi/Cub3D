/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:36:38 by nmbabazi          #+#    #+#             */
/*   Updated: 2019/11/14 14:08:17 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static	unsigned int	ft_len(int n)
{
	unsigned int i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char					*ft_itoa(int n)
{
	char			*str;
	int				len;
	int				sign;
	unsigned int	nbr;

	len = ft_len(n);
	sign = '\0';
	nbr = n;
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (0);
	if (n < 0)
	{
		sign = '-';
		nbr = n * (-1);
	}
	str[len] = '\0';
	while (--len >= 0)
	{
		str[len] = (nbr % 10) + 48;
		nbr = nbr / 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}
