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

void			ft_initplan(t_param *param)
{
	if (param->player.c == 'E')
	{
		param->player.planx = 0;
		param->player.plany = -0.6;
	}
	if (param->player.c == 'S')
	{
		param->player.planx = 0.6;
		param->player.plany = 0;
	}
	if (param->player.c == 'W')
	{
		param->player.planx = 0;
		param->player.plany = 0.6;
	}
	if (param->player.c == 'N')
	{
		param->player.planx = -0.6;
		param->player.plany = 0;
	}
}

void			ft_initdir(t_param *param)
{
	if (param->player.c == 'E')
	{
		param->player.dirx = 1;
		param->player.diry = 0;
	}
	if (param->player.c == 'S')
	{
		param->player.dirx = 0;
		param->player.diry = 1;
	}
	if (param->player.c == 'W')
	{
		param->player.dirx = -1;
		param->player.diry = 0;
	}
	if (param->player.c == 'N')
	{
		param->player.dirx = 0;
		param->player.diry = -1;
	}
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

void			ft_renderplayer(t_param *param)
{
	int l;
	int size_player;

	l = 0;
	size_player = 15;
	ft_drawplayer((param->player.x - size_player / 2) * MINIMAP,
		(param->player.y - size_player / 2) * MINIMAP, 0xFF0000, param);
//	ft_drawline(param->player.x * MINIMAP, param->player.y * MINIMAP,
//		100 * MINIMAP, param->player.rotationangle, param);
}

void			ft_playerdirection(t_param *param, float angle_start)
{
	float angle;

	angle = ft_normalizeangle(angle_start);
	if ((angle > M_PI * 0.25 && angle < 0.75 * M_PI) ||
			(angle > M_PI * 1.25 && angle < 1.75 * M_PI))
		param->player.facingvert = 1;
	else
		param->player.facingvert = 0;
}

void			ft_updatevect(t_param *param)
{
	float olddirx;
	float oldplanx;
	float vectangle;

	olddirx = param->player.dirx;
	oldplanx = param->player.planx;
	vectangle = param->player.turndirection * param->player.turnspeed;
	param->player.dirx = param->player.dirx * cos(vectangle)
		- param->player.diry * sin(vectangle);
	param->player.diry = olddirx * sin(vectangle) +
		param->player.diry * cos(vectangle);
	param->player.planx = param->player.planx * cos(vectangle)
		- param->player.plany * sin(vectangle);
	param->player.plany = oldplanx * sin(vectangle) +
		param->player.plany * cos(vectangle);
}

void			ft_translation(t_param *param, float movestep,
			float *newplayerx, float *newplayery)
{
	float translationangle;

	translationangle = (M_PI * 0.5) - param->player.rotationangle;
	if (param->player.translation != 0 && param->player.facingvert == 0)
	{
		*newplayerx = param->player.x - cos(translationangle) * movestep;
		*newplayery = param->player.y + sin(translationangle) * movestep;
	}
	else if (param->player.translation != 0 && param->player.facingvert == 1)
	{
		*newplayerx = param->player.x + cos(translationangle) * -movestep;
		*newplayery = param->player.y - sin(translationangle) * -movestep;
	}
	else
		return ;
}

void			ft_updateplayer(t_param *param)
{
	float movestep;
	float newplayerx;
	float newplayery;

	param->player.rotationangle += param->player.turndirection
		* param->player.turnspeed;
	movestep = param->player.walkdirection * param->player.walkspeed;
	ft_playerdirection(param, param->player.rotationangle);
	if (param->player.translation == 1)
		ft_translation(param, movestep, &newplayerx, &newplayery);
	if (param->player.translation == 0)
	{
		newplayerx = param->player.x +
			cos(param->player.rotationangle) * movestep;
		newplayery = param->player.y +
			sin(param->player.rotationangle) * movestep;
	}
	ft_updatevect(param);
	if (ft_iswall(newplayerx, newplayery, param) == 0)
	{
		param->player.x = newplayerx;
		param->player.y = newplayery;
	}
}
