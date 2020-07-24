/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:50:54 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/24 16:22:50 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		ft_isxpm(char *line)
{
	int i;

	i = 0;
	if (line[i] == '.')
	{
		i++;
		if (line[i] != 'x')
			return (0);
		i++;
		if (line[i] != 'p')
			return (0);
		i++;
		if (line[i] != 'm')
			return (0);
		i++;
	}
	if (line[i] != '\0')
		return (0);
	return (i);
}

void	ft_freestr(char *str)
{
	free(str);
}

int		ft_getlen(t_list *maps)
{
	int len;
	int check;

	len = 0;
	check = 0;
	while (maps)
	{
		check = ft_strlen(maps->str);
		if (check >= len)
			len = check;
		maps = maps->next;
	}
	return (len);
}

t_list	*add_link(t_list *maps, char *line)
{
	t_list	*tmp;
	char	*swp;

	if (!(tmp = (t_list *)malloc(sizeof(t_list) * 1)))
	{
		free(line);
		return (NULL);
	}
	if (tmp)
	{
		tmp->str = ft_strdup(line);
		tmp->next = maps;
	}
	free(line);
	return (tmp);
}

int		ft_open(char *path)
{
	return (open(path, O_RDONLY));
}
