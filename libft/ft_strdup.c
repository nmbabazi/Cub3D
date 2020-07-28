/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 15:15:32 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/27 18:02:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	int		i;
	int		l;
	char	*p;

	i = 0;
	l = 0;
	while (src[i])
		i++;
	p = malloc(sizeof(*p) * (i + 1));
	if (p == NULL)
		return (0);
	while (src[l])
	{
		p[l] = src[l];
		l++;
	}
	p[l] = '\0';
	return (p);
}
