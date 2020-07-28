/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:50:54 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/28 16:10:16 by user42           ###   ########.fr       */
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

void	ft_freepath(t_param *param)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (param->texture[i].path != NULL)
			free(param->texture[i].path);
		i++;
	}
	if (param->sprite.path != NULL)
		free(param->sprite.path);
}
