/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 11:27:50 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/24 16:39:53 by nmbabazi         ###   ########.fr       */
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

void	ft_initwin_size(t_param *param, int width, int height)
{
	if (param->win_height > height)
		param->win_height = height;
	if (param->win_width > width)
		param->win_width = width;
	return ;
}

void	ft_initall(t_param *param)
{
	ft_initplayer(param);
	ft_inittexture(param);
	ft_initsprite(param);
	ft_initdir(param);
	ft_initplan(param);
}
