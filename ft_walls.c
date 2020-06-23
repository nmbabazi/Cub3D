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

	if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
		return (1);
	indexx = floor(x / TILE_S);
	indexy = floor(y / TILE_S);
	if (map[indexy][indexx] == '1')
		return (1);
	return (0);
}*/

void	ft_drawwall(int walltop, int wallbottom, t_param *param, int id)
{
	int	y;

	y = 0;
	while (y < walltop)
	{
		param->img.data[y * WIN_WIDTH + id] = 0xC0C0C0;
		y++;
	}
	if (param->ray[id].washitvert == 0 && param->ray[id].raydown == -1)
		ft_puttxt(param, walltop, id, wallbottom, NO);
	if (param->ray[id].washitvert == 0 && param->ray[id].raydown == 1)
		ft_puttxt(param, walltop, id, wallbottom, SO);
	if (param->ray[id].washitvert == 1 && param->ray[id].rayright == -1)
		ft_puttxt(param, walltop, id, wallbottom, WE);
	if (param->ray[id].washitvert == 1 && param->ray[id].rayright == 1)
		ft_puttxt(param, walltop, id, wallbottom, EA);
	y = wallbottom;
	while (y < WIN_HEIGHT)
	{
		param->img.data[y * WIN_WIDTH + id] = 0x778899;
		y++;
	}
}

void	ft_render3d(t_param *param, int id)
{
	float	distanceprojection;
	float	walldistance;
	int		walltop;
	int		wallbottom;

	walldistance = param->ray[id].colldistance *
		cos(param->ray[id].rayangle - param->player.rotationangle);
	distanceprojection = (WIN_WIDTH / 2) / tan(FOV / 2);
	param->ray[id].wallheight = (int)((TILE_S / walldistance)
		* distanceprojection);
	walltop = (WIN_HEIGHT / 2) - (param->ray[id].wallheight / 2);
	walltop = walltop < 0 ? 0 : walltop;
	wallbottom = (WIN_HEIGHT / 2) + (param->ray[id].wallheight / 2);
	wallbottom = wallbottom > WIN_HEIGHT ? WIN_HEIGHT : wallbottom;
	ft_drawwall(walltop, wallbottom, param, id);
}