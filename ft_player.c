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

void	ft_startingdirection(t_param *param, char c)
{
	if (c == 'N')
		param->player.rotationangle = 1.5 * M_PI;;
	if (c == 'S')
		param->player.rotationangle = 0.5 * M_PI;
	if (c == 'E')
		param->player.rotationangle = 0;
	if (c == 'W')
		param->player.rotationangle = M_PI;
}

void	ft_initplayer(t_param *param)
{
	int i;
	int l;
	char c;

	i = 0;
	l = 0;
	while (l < param->map_rows)
	{
		i = 0;
		while (i < param->map_cols)
		{
			if (param->map[l][i] == 'N' || param->map[l][i] == 'S' || param->map[l][i] == 'E' || param->map[l][i] == 'W')
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
	ft_startingdirection(param, c);
	param->player.walkspeed = 2;
	param->player.turnspeed = 2 * (M_PI / 180);
	param->player.facingvert = 0;
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
	ft_drawline(param->player.x * MINIMAP, param->player.y * MINIMAP, 100 * MINIMAP,param->player.rotationangle, param);
}

void	ft_playerdirection(t_param *param, float angle_start)
{
	float angle = ft_normalizeangle(angle_start);
	if ((angle > M_PI * 0.25 && angle < 0.75 * M_PI) || (angle > M_PI * 1.25 && angle < 1.75 * M_PI))
		param->player.facingvert = 1;
	else	
		param->player.facingvert = 0;
}

void	ft_updateplayer(t_param *param)
{
	float movestep;
	float newplayerx;
	float newplayery;
	float olddirx = param->dirx;
	float oldplanx = param->planx;
	float dirangle = param->player.turndirection * param->player.turnspeed;
	float angleangle;

	param->player.rotationangle += param->player.turndirection *
			param->player.turnspeed;
	angleangle = (M_PI * 0.5) - param->player.rotationangle;
	movestep = param->player.walkdirection * param->player.walkspeed;
	ft_playerdirection(param, param->player.rotationangle);
	if (param->player.velocity != 0 && param->player.facingvert == 0)
	{
		newplayerx = param->player.x - cos(angleangle) * movestep;
		newplayery = param->player.y + sin(angleangle) * movestep;
	}
	if (param->player.velocity != 0 && param->player.facingvert == 1)
	{
		newplayerx = param->player.x + cos(angleangle) * -movestep;
		newplayery = param->player.y - sin(angleangle) * -movestep;
	}
	if (param->player.velocity == 0)
	{
		newplayerx = param->player.x + cos(param->player.rotationangle) * movestep;
		newplayery = param->player.y + sin(param->player.rotationangle) * movestep;
	}
	////////////////////////calculs dir et plan pour les sprites/////////////////////////////////
	param->dirx = param->dirx * cos(dirangle) - param->diry * sin(dirangle);
    param->diry = olddirx * sin(dirangle) + param->diry * cos(dirangle);
	param->planx = param->planx * cos(dirangle) - param->plany * sin(dirangle);
    param->plany = oldplanx * sin(dirangle) + param->plany * cos(dirangle);
	if (ft_iswall(newplayerx, newplayery, param) == 0)
	{
		param->player.x = newplayerx;
		param->player.y = newplayery;
	}
}