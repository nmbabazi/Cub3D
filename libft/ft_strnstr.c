/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 12:02:21 by nmbabazi          #+#    #+#             */
/*   Updated: 2019/11/13 16:18:42 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t i;
	size_t l;

	i = 0;
	l = 0;
	if (to_find[l] == '\0')
		return ((char *)str);
	while (str[i] != '\0' && i < n)
	{
		if (str[i] == to_find[0])
		{
			l = 0;
			while (str[i + l] == to_find[l])
			{
				if ((i + l) >= n)
					return (0);
				if (to_find[l + 1] == '\0')
					return ((char *)&str[i]);
				l++;
			}
		}
		i++;
	}
	return (0);
}
