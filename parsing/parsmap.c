/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 15:14:24 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/24 15:22:29 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_fillrows(char *src, t_param *param, int len, int i)
{
	int l;

	l = 0;
	while (src[l])
	{
		param->map[i][l] = src[l];
		l++;
	}
	if (l < len)
	{
		while (l < len)
		{
			param->map[i][l] = ' ';
			l++;
		}
	}
	param->map[i][l] = '\0';
}

void	ft_fillgap(t_param *param)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < param->map_rows)
	{
		j = 0;
		while (j < param->map_cols)
		{
			if (param->map[i][j] == ' ')
				param->map[i][j] = '1';
			j++;
		}
		i++;
	}
}

int		ft_creatmap(t_list *maps, t_param *param)
{
	int i;

	i = 0;
	param->map_rows = ft_lstsize(maps);
	param->map_cols = ft_getlen(maps);
	if (!(param->map = (char **)malloc(sizeof(char *) * param->map_rows + 1)))
		return (0);
	while (i < param->map_rows)
	{
		if (!(param->map[i] = malloc(sizeof(char) * param->map_cols + 1)))
			return (0);
		i++;
	}
	while (--i >= 0 && maps)
	{
		ft_fillrows(maps->str, param, param->map_cols, i);
		maps = maps->next;
	}
	if (ft_checkmap(param->map, param) == 0)
		return (0);
	if (ft_oneplayer(param->map, param) == 0)
		return (0);
	ft_fillgap(param);
	return (1);
}

int		ft_checklastline(char *line, t_list *maps)
{
	if (!(*line == '1' || *line == ' ') || *line == '\0')
	{
		free(line);
		ft_lstclear(&maps, &ft_freestr);
		return (0);
	}
	return (1);
}

int		ft_buildmap(t_param *param, char *line, int *r, int fd)
{
	int		ret;
	t_list	*maps;

	ret = 0;
	maps = NULL;
	maps = add_link(maps, line);
	while ((*r = get_next_line(&line, fd)) > 0)
	{
		if (ft_checklastline(line, maps) != 1)
			return (5);
		maps = add_link(maps, line);
	}
	if (ft_checklastline(line, maps) != 1)
		return (5);
	maps = add_link(maps, line);
	if (ft_creatmap(maps, param) != 1)
	{
		ft_lstclear(&maps, &ft_freestr);
		return (5);
	}
	ft_lstclear(&maps, &ft_freestr);
	return (1);
}
