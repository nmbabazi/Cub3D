/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initplayer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:08:15 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/24 14:32:56 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

void			ft_startingdirection(t_param *param, char c)
{
	param->player.c = c;
	if (c == 'N')
		param->player.rotationangle = 1.5 * M_PI;
	if (c == 'S')
		param->player.rotationangle = 0.5 * M_PI;
	if (c == 'E')
		param->player.rotationangle = 0;
	if (c == 'W')
		param->player.rotationangle = M_PI;
}

static	char	ft_findplayer(t_param *param)
{
	int		i;
	int		l;
	char	c;

	i = 0;
	l = 0;
	while (l < param->map_rows)
	{
		i = 0;
		while (i < param->map_cols)
		{
			if (param->map[l][i] == 'N' || param->map[l][i] == 'S'
				|| param->map[l][i] == 'E' || param->map[l][i] == 'W')
			{
				param->player.x = i * param->tile_s + param->tile_s / 2;
				param->player.y = l * param->tile_s + param->tile_s / 2;
				c = param->map[l][i];
				break ;
			}
			i++;
		}
		l++;
	}
	return (c);
}

void			ft_initplayer(t_param *param)
{
	char c;

	c = ft_findplayer(param);
	ft_startingdirection(param, c);
	param->player.walkspeed = 2;
	param->player.turnspeed = 2 * (M_PI / 180);
	param->player.facingvert = 0;
	return ;
}
