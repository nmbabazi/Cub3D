/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:42:47 by nmbabazi          #+#    #+#             */
/*   Updated: 2019/11/14 17:15:41 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_verif(const char *set, char c)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		l;
	char	*s2;
	int		z;

	i = 0;
	z = 0;
	if (!s1 || !set)
		return (0);
	while (*s1 && ft_verif(set, *s1) == 1)
		s1++;
	l = ft_strlen(s1);
	while (l > 0 && ft_verif(set, s1[l - 1]) == 1)
		l--;
	if (!(s2 = malloc(sizeof(char) * (l + 1))))
		return (0);
	while (s1[i] && i < l)
	{
		s2[z++] = s1[i++];
	}
	s2[z] = '\0';
	return (s2);
}
