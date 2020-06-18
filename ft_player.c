/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:02:57 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/06/18 12:57:14 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	ft_initplayer(const char map[MAP_ROWS][MAP_COLS], t_param *param)
{
	int i = 0;
	int l = 0;

	while (l < MAP_ROWS)
	{
		i = 0;
		while(i < MAP_COLS)
		{
			if (map[l][i] == '3')
			{
				param->player.x = i * TILE_S + TILE_S / 2;
				param->player.y = l * TILE_S + TILE_S / 2;
				break;
			}
			i++;
		}
		l++;
	}
	param->player.rotationAngle = M_PI / 2;
	param->player.walkSpeed = 2;
	param->player.turnSpeed  = 2 * (M_PI / 180);
	return ;
}

void	ft_renderplayer(t_param *param)
{
	int l = 0;
	int size_player = 15;

	ft_rectangle((param->player.x - size_player / 2) * MINIMAP, (param->player.y - size_player / 2) * MINIMAP, size_player * MINIMAP, size_player * MINIMAP, 0xFF0000, param);

}

void	ft_updateplayer(t_param *param)
{
	param->player.rotationAngle += param->player.turnDirection * param->player.turnSpeed;
	float  moveStep = param->player.walkDirection * param->player.walkSpeed;

	float NewplayerX = param->player.x + cos(param->player.rotationAngle) * moveStep;
	float NewplayerY = param->player.y + sin(param->player.rotationAngle) * moveStep;

	if (ft_isWall(NewplayerX, NewplayerY) == 0)
	{
		param->player.x = NewplayerX;
		param->player.y = NewplayerY;
	}
}
