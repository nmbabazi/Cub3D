/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 16:20:56 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/24 16:22:14 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*ft_strnew(size_t n)
{
	char	*new;
	int		i;

	i = 0;
	if (!(new = malloc(sizeof(char) * (n + 1))))
		return (NULL);
	while (n + 1 > 0)
	{
		new[i] = '\0';
		i++;
		n--;
	}
	return (new);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(s3 = (char *)malloc(sizeof(char) *
		(ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	return (s3);
}

int		get_next_line(char **line, int fd)
{
	int		ret;
	char	*tmp;
	char	buf[2];

	ret = 0;
	tmp = NULL;
	if (!line || read(fd, buf, 0) < 0)
		return (-1);
	*line = ft_strnew(1);
	while ((ret = read(fd, buf, 1)) > 0)
	{
		buf[ret] = '\0';
		if (buf[0] != '\n')
		{
			tmp = *line;
			*line = ft_strjoin(*line, buf);
			free(tmp);
		}
		if (buf[0] == '\n')
			break ;
	}
	if (ret)
		return (1);
	return (0);
}
