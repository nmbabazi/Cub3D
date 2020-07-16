/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_walls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 11:54:23 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/06/23 11:54:25 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/*int		ft_iswall(float x, float y)
{
	int indexx;
	int indexy;

	if (x < 0 || x > param->win_width || y < 0 || y > param->win_height)
		return (1);
	indexx = floor(x / param->tile_s);
	indexy = floor(y / param->tile_s);
	if (map[indexy][indexx] == '1')
		return (1);
	return (0);
}*/

void	ft_drawwall(int walltop, int wallbottom, t_param *param, int id)
{
	int	y;

	y = 0;
//	y = walltop;
	while (y < walltop)
	{
		param->img.data[y * param->win_width + id] = param->c_color;
		y++;
	}
	if (param->ray.washitvert == 0 && param->ray.raydown == -1)
		ft_puttxt(param, walltop, id, wallbottom, NO);
	if (param->ray.washitvert == 0 && param->ray.raydown == 1)
		ft_puttxt(param, walltop, id, wallbottom, SO);
	if (param->ray.washitvert == 1 && param->ray.rayright == -1)
		ft_puttxt(param, walltop, id, wallbottom, WE);
	if (param->ray.washitvert == 1 && param->ray.rayright == 1)
		ft_puttxt(param, walltop, id, wallbottom, EA);
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
	int		walltop;
	int		wallbottom;

	walldistance = param->ray.colldistance *
	cos(param->ray.rayangle - param->player.rotationangle);
	param->sprite.buffer[id] = walldistance;
//	printf("len = %f\n", param->sprite.buffer[id]);
	distanceprojection = (param->win_width / 2) / tan(FOV / 2);
	param->ray.wallheight = (int)((param->tile_s / walldistance)
		* distanceprojection);
	walltop = (param->win_height / 2) - (param->ray.wallheight / 2);
	walltop = walltop < 0 ? 0 : walltop;
	wallbottom = (param->win_height / 2) + (param->ray.wallheight / 2);
	wallbottom = wallbottom > param->win_height ? param->win_height : wallbottom;
	ft_drawwall(walltop, wallbottom, param, id);
}