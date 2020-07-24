/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_walls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 11:54:23 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/24 14:42:47 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

void	ft_rendermap(t_param *param)
{
	int i;
	int l;
	int col;

	i = 0;
	l = 0;
	col = 0x000000;
	while (l < param->map_rows)
	{
		i = 0;
		while (i < param->map_cols)
		{
			if (param->map[l][i] == '1')
				col = 0xFFFFFF;
			else if (param->map[l][i] != '1')
				col = 0x000000;
			ft_drawmap(i * param->tile_s * MINIMAP,
				l * param->tile_s * MINIMAP, col, param);
			i++;
		}
		l++;
	}
}

void	ft_drawmap(int x, int y, int col, t_param *param)
{
	int count_y;
	int count_x;
	int x_start;
	int col_start;

	count_y = 0;
	count_x = 0;
	x_start = x;
	col_start = col;
	while (count_y < param->tile_s * MINIMAP)
	{
		count_x = 0;
		x = x_start;
		while (count_x < param->tile_s * MINIMAP)
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

int		ft_iswall(float x, float y, t_param *param)
{
	int indexx;
	int indexy;

	if (x < 0 || x > param->map_cols * param->tile_s
		|| y < 0 || y > param->map_rows * param->tile_s)
		return (1);
	indexx = floor(x / param->tile_s);
	indexy = floor(y / param->tile_s);
	if (param->map[indexy][indexx] == '1')
		return (1);
	return (0);
}

void	ft_drawwall(int walltop, int wallbottom, t_param *param, int id)
{
	int	y;

	y = 0;
	while (y < walltop)
	{
		param->img.data[y * param->win_width + id] = param->c_color;
		y++;
	}
	if (param->ray.washitvert == 0 && param->ray.raydown == -1)
		ft_puttxt(param, walltop, id, NO);
	if (param->ray.washitvert == 0 && param->ray.raydown == 1)
		ft_puttxt(param, walltop, id, SO);
	if (param->ray.washitvert == 1 && param->ray.rayright == -1)
		ft_puttxt(param, walltop, id, WE);
	if (param->ray.washitvert == 1 && param->ray.rayright == 1)
		ft_puttxt(param, walltop, id, EA);
	y = wallbottom;
	while (y < param->win_height)
	{
		param->img.data[y * param->win_width + id] = param->f_color;
		y++;
	}
}

void	ft_render3d(t_param *param, int id)
{
	float	distanceprojection;
	float	walldistance;
	int		top;
	int		bottom;

	walldistance = param->ray.colldistance *
	cos(param->ray.rayangle - param->player.rotationangle);
	param->sprite.buffer[id] = walldistance;
	distanceprojection = (param->win_width / 2) / tan(FOV / 2);
	param->ray.wallheight = (int)((param->tile_s / walldistance)
		* distanceprojection);
	top = (param->win_height / 2) - (param->ray.wallheight / 2);
	top = top < 0 ? 0 : top;
	bottom = (param->win_height / 2) + (param->ray.wallheight / 2);
	bottom = bottom > param->win_height ? param->win_height : bottom;
	ft_drawwall(top, bottom, param, id);
}
