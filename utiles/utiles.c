/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 11:27:50 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/25 16:29:10 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

float	ft_distance(float x, float y, float xend, float yend)
{
	return (sqrt((xend - x) * (xend - x) + (yend - y) * (yend - y)));
}

void	ft_drawline(int x_start, int y_start, float angle, t_param *param)
{
	float	i;
	int		x;
	int		y;
	int		longeur;

	longeur = 0;
	i = 0;
	x = 0;
	y = 0;
	while (i < param->ray.colldistance * MINIMAP)
	{
		param->img.data[(y_start + y) * param->win_width
			+ (x_start + x)] = 0xffff00;
		x = cos(angle) * longeur;
		y = sin(angle) * longeur;
		longeur++;
		i++;
	}
}

float	ft_normalizeangle(float angle)
{
	angle = remainder(angle, M_PI * 2);
	if (angle < 0)
		angle = (M_PI * 2) + angle;
	return (angle);
}

void	ft_initwin_size(t_param *param)
{
	if (param->win_height > 1440)
		param->win_height = 1440;
	if (param->win_width > 2560)
		param->win_width = 2560;
	if (param->win_height < 60)
		param->win_height = 60;
	if (param->win_width < 60)
		param->win_width = 60;
	if (param->win_height / param->win_width > 28.8)
		param->win_width = param->win_height / 28.8;
	if (param->win_width / param->win_height > 6.4)
		param->win_height = param->win_width / 6.4;
	param->tile_s = param->win_width / param->map_cols;
	param->num_rays = param->win_width;
	return ;
}

void	ft_initall(t_param *param)
{
	ft_initplayer(param);
	ft_inittexture(param);
	ft_initsprite(param);
	ft_initdir(param);
	ft_initplan(param);
	ft_initwin_size(param);
}
