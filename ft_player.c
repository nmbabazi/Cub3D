/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:02:57 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/06/20 17:49:08 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	ft_initplayer(const char map[MAP_ROWS][MAP_COLS], t_param *param)
{
	int i;
	int l;

	i = 0;
	l = 0;
	while (l < MAP_ROWS)
	{
		i = 0;
		while (i < MAP_COLS)
		{
			if (map[l][i] == '3')
			{
				param->player.x = i * TILE_S + TILE_S / 2;
				param->player.y = l * TILE_S + TILE_S / 2;
				break ;
			}
			i++;
		}
		l++;
	}
	param->player.rotationangle = M_PI / 2;
	param->player.walkspeed = 2;
	param->player.turnspeed = 2 * (M_PI / 180);
	return ;
}

void	ft_renderplayer(t_param *param)
{
	int l;
	int size_player;

	l = 0;
	size_player = 15;
	ft_rectangle((param->player.x - size_player / 2) * MINIMAP,
		(param->player.y - size_player / 2) * MINIMAP,
			size_player * MINIMAP, 0xFF0000, param);
}

void	ft_updateplayer(t_param *param)
{
	float movestep;
	float newplayerx;
	float newplayery;

	param->player.rotationangle += param->player.turndirection *
		param->player.turnspeed;
	movestep = param->player.walkdirection * param->player.walkspeed;
	newplayerx = param->player.x + cos(param->player.rotationangle) * movestep;
	newplayery = param->player.y + sin(param->player.rotationangle) * movestep;
	if (ft_iswall(newplayerx, newplayery) == 0)
	{
		param->player.x = newplayerx;
		param->player.y = newplayery;
	}
}
