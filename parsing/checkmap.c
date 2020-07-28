/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 15:18:46 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/28 16:00:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		ft_checksurrounding(char c, int i, int j, char **map)
{
	if (map[i][j + 1] == ' '
		|| map[i][j - 1] == ' ' || map[i + 1][j] == ' '
		|| map[i - 1][j] == ' ')
	{
		ft_putstr_fd("ERROR:\n Map not surrounded by wall.....\n", 1);
		return (0);
	}
	return (1);
}

int		ft_checkcorner(t_param *param, int i, int j, char **map)
{
	if (((i == 0 || j == 0) && (map[i][j] == '0'
		|| map[i][j] == '2' || map[i][j] == 'N' || map[i][j] == 'S'
		|| map[i][j] == 'W' || map[i][j] == 'E')))
		return (0);
	if (((i == param->map_rows - 1 || j == param->map_cols - 1) &&
		(map[i][j] == '0' || map[i][j] == '2' || map[i][j] == 'N'
		|| map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')))
		return (0);
	return (1);
}

int		ft_oneplayer(char **map, t_param *param)
{
	int i;
	int j;
	int n;

	i = 0;
	j = 0;
	n = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
				n++;
			if (n > 1)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int		ft_checkmap(char **map, t_param *param)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (param->map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '2' && map[i][j] != 'N'
				&& map[i][j] != 'S' && map[i][j] != 'W' && map[i][j] != 'E'
				&& map[i][j] != '1' && map[i][j] != ' ')
				return (0);
			if (ft_checkcorner(param, i, j, map) == 0)
				return (0);
			else if ((map[i][j] != '1' && map[i][j] != ' ')
				&& ft_checksurrounding(map[i][j], i, j, map) == 0)
				return (0);
			j++;
		}
		i++;
	}
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
