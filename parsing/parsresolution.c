/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsresolution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 15:10:51 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/27 12:52:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		ft_fillrez(t_param *param, int i, char *line, int n)
{
	while ((line[i] >= '0' && line[i] <= '9') && line[i] != 32 && line[i])
	{
		if (n > 1)
		{
			free(line);
			return (0);
		}
		if (n == 0)
			param->win_width = (param->win_width * 10) + (line[i] - 48);
		if (n == 1)
			param->win_height = (param->win_height * 10) + (line[i] - 48);
		i++;
	}
	if (n == 1 && line[i] == ' ')
		return (0);
	return (i);
}

int		ft_findnum(t_param *param, char *line, int n)
{
	int i;

	i = 1;
	while (line[i])
	{
		while (line[i] == ' ')
		{
			i++;
		}
		if (!(line[i] >= '0' && line[i] <= '9') || (n != 0 && n != 1))
			return (0);
		if ((i = ft_fillrez(param, i, line, n)) == 0)
			return (0);
		if (line[i] == 32 && line[i + 1] != '\0')
		{
			i++;
			n++;
		}
	}
	return (n);
}

int		ft_resolution(char *line, t_param *param, int *tab)
{
	int i;
	int n;

	i = 1;
	n = 0;
	ft_filltab(line, tab);
	n = ft_findnum(param, line, n);
	if (n != 1)
	{
		free(line);
		return (2);
	}
	free(line);
	return (1);
}
