/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 11:27:50 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/06/17 14:16:20 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include.h"

float	ft_distance(float x, float y, float xend, float yend)
{
	return (sqrt((xend - x) * (xend -x) + (yend - y) * (yend - y)));

}

void	ft_drawline(int X, int Y, float distance, int color, float angle, 
		t_param *param)
{
	float i;
	int x;
	int y;
	int longeur;

	longeur = 0;
	i = 0;
	x = 0;
	y = 0;
	while (i < distance)
	{
		param->img.data[(Y + y) * WIN_WIDTH + (X + x)] = color;
		x = cos(angle) * longeur;
		y = sin(angle) * longeur;
		longeur++;
		i++;
	}
}

void	ft_rectangle(int x, int y, int height, int width, int col, t_param *param)
{
	int count_y = 0;
	int count_x = 0;
	int x_start = x;
	int col_start = col;


	while (count_y < height)
	{
		count_x = 0;
		x = x_start;
		while(count_x < width)
		{
		//	if (y % TILE_S == 0 || x % TILE_S == 0)
		//		col = 0xFFFFFF;
		//	else
		//		col = col_start;
			param->img.data[y * WIN_WIDTH + x] = col;
			count_x++;
			x++;
		}
		count_y++;
		y++;
	}
	return;
}

float	ft_normalizeAngle(float angle)
{
	angle = remainder(angle, M_PI * 2);
	if (angle < 0)
		angle = (M_PI * 2) + angle;
	return (angle);
}
