/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:02:57 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/28 11:38:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

void	ft_drawplayer(int x, int y, int col, t_param *param)
{
	int count_y;
	int count_x;
	int x_start;
	int col_start;

	count_y = 0;
	count_x = 0;
	x_start = x;
	col_start = col;
	while (count_y < 15 * MINIMAP)
	{
		count_x = 0;
		x = x_start;
		while (count_x < 15 * MINIMAP)
		{
			param->img.data[y * param->win_width + x] = col;
			count_x++;
			x++;
		}
		count_y++;
		y++;
	}
	return ;
}

void	ft_renderplayer(t_param *param)
{
	int l;
	int size_player;

	l = 0;
	size_player = 15;
	ft_drawplayer((param->player.x - size_player / 2) * MINIMAP,
		(param->player.y - size_player / 2) * MINIMAP, 0xFF0000, param);
}

void	ft_playerdirection(t_param *param, float angle_start)
{
	float angle;

	angle = ft_normalizeangle(angle_start);
	if ((angle > M_PI * 0.25 && angle < 0.75 * M_PI) ||
			(angle > M_PI * 1.25 && angle < 1.75 * M_PI))
		param->player.facingvert = 1;
	else
		param->player.facingvert = 0;
}

void	ft_translation(t_param *param, float movestep,
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

void	ft_updateplayer(t_param *param)
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
