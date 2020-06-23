/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 11:47:27 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/06/20 17:51:23 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	ft_initrays(t_param *param, int id)
{
	param->ray[id].wallhitx = 0;
	param->ray[id].wallhity = 0;
	param->ray[id].colldistance = 0;
	param->ray[id].raydown = 0;
	param->ray[id].rayright = 0;
	param->ray[id].washitvert = 0;
	param->ray[id].wallheight = 0;
	param->ray[id].horzhity = 0;
	param->ray[id].horzhitx = 0;
	param->ray[id].verthity = 0;
	param->ray[id].verthitx = 0;
}

float	ft_findhorzhit(t_param *param, int id)
{
	float	horzhitdistance;
	float	yintercept;
	float	xintercept;
	float	xstep;
	float	ystep;
	int		horzhit;
	float	nexthorzy;
	float	nexthorzx;

	yintercept = floor(param->player.y / TILE_S) * TILE_S;
	if (param->ray[id].raydown == 1)
		yintercept += TILE_S;
	xintercept = param->player.x + ((yintercept - param->player.y)
		/ tan(param->ray[id].rayangle));
	ystep = TILE_S;
	if (param->ray[id].raydown == -1)
		ystep *= -1;
	xstep = TILE_S / tan(param->ray[id].rayangle);
	if (param->ray[id].rayright == -1 && xstep > 0)
		xstep *= -1;
	if (param->ray[id].rayright == 1 && xstep < 0)
		xstep *= -1;
	nexthorzy = yintercept;
	nexthorzx = xintercept;
	if (param->ray[id].raydown == -1)
		nexthorzy--;
	while (nexthorzx >= 0 && nexthorzx <= WIN_WIDTH
		&& nexthorzy >= 0 && nexthorzy <= WIN_HEIGHT)
	{
		if (ft_iswall(nexthorzx, nexthorzy) == 1)
		{
			horzhit = 1;
			param->ray[id].horzhitx = nexthorzx;
			param->ray[id].horzhity = nexthorzy;
			break ;
		}
		else
		{
			nexthorzx += xstep;
			nexthorzy += ystep;
		}
	}
	if (horzhit == 1)
		horzhitdistance = ft_distance(param->player.x,
			param->player.y, param->ray[id].horzhitx, param->ray[id].horzhity);
	else
		horzhitdistance = INT_MAX;
	return (horzhitdistance);
}

float	ft_findverthit(t_param *param, int id)
{
	float	verthitdistance;
	float	yintercept;
	float	xintercept;
	float	xstep;
	float	ystep;
	int		verthit;
	float	nextverty;
	float	nextvertx;

	xintercept = floor(param->player.x / TILE_S) * TILE_S;
	if (param->ray[id].rayright == 1)
		xintercept += TILE_S;
	yintercept = param->player.y + ((xintercept - param->player.x)
		* tan(param->ray[id].rayangle));
	xstep = TILE_S;
	if (param->ray[id].rayright == -1)
		xstep *= -1;
	ystep = TILE_S * tan(param->ray[id].rayangle);
	if (param->ray[id].raydown == -1 && ystep > 0)
		ystep *= -1;
	if (param->ray[id].raydown == 1 && ystep < 0)
		ystep *= -1;
	nextverty = yintercept;
	nextvertx = xintercept;
	if (param->ray[id].rayright == -1)
		nextvertx--;
	while (nextvertx >= 0 && nextvertx <= WIN_WIDTH &&
		nextverty >= 0 && nextverty <= WIN_HEIGHT)
	{
		if (ft_iswall(nextvertx, nextverty) == 1)
		{
			verthit = 1;
			param->ray[id].verthitx = nextvertx;
			param->ray[id].verthity = nextverty;
			break ;
		}
		else
		{
			nextvertx += xstep;
			nextverty += ystep;
		}
	}
	if (verthit == 1)
		verthitdistance = ft_distance(param->player.x,
			param->player.y, param->ray[id].verthitx, param->ray[id].verthity);
	else
		verthitdistance = INT_MAX;
	return (verthitdistance);
}

void	ft_compdistance(float horzhitdistance,
	float verthitdistance, t_param *param, int id)
{
	if (horzhitdistance <= verthitdistance)
	{
		param->ray[id].wallhitx = param->ray[id].horzhitx;
		param->ray[id].wallhity = param->ray[id].horzhity;
		param->ray[id].colldistance = horzhitdistance;
		param->ray[id].washitvert = 0;
	}
	if (horzhitdistance > verthitdistance)
	{
		param->ray[id].wallhitx = param->ray[id].verthitx;
		param->ray[id].wallhity = param->ray[id].verthity;
		param->ray[id].colldistance = verthitdistance;
		param->ray[id].washitvert = 1;
	}
}

void	ft_castallrays(t_param *param)
{
	int		id;
	float	angle;

	id = 0;
	angle = param->player.rotationangle - (FOV / 2);
	while (id < NUM_RAYS)
	{
		param->ray[id].rayangle = ft_normalizeangle(angle);
		ft_initrays(param, id);
		ft_raydirection(param, param->ray[id].rayangle, id);
		ft_compdistance(ft_findhorzhit(param, id), ft_findverthit(param, id), param, id);
		ft_drawline(param->player.x * MINIMAP, param->player.y *
			MINIMAP, param->ray[id].colldistance * MINIMAP,
			param->ray[id].rayangle, param);
		ft_render3d(param, id);
		angle += FOV / NUM_RAYS;
		id++;
	}
}