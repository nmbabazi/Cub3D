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

void	ft_initrays(t_ray *ray)
{
	ray->wallhitx = 0;
	ray->wallhity = 0;
	ray->colldistance = 0;
	ray->raydown = 0;
	ray->rayright = 0;
	ray->washitvert = 0;
	ray->wallheight = 0;
	ray->horzhity = 0;
	ray->horzhitx = 0;
	ray->verthity = 0;
	ray->verthitx = 0;
}

float	ft_findhorzhit(t_param *param)
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
	if (param->ray.raydown == 1)
		yintercept += TILE_S;
	xintercept = param->player.x + ((yintercept - param->player.y)
		/ tan(param->ray.rayangle));
	ystep = TILE_S;
	if (param->ray.raydown == -1)
		ystep *= -1;
	xstep = TILE_S / tan(param->ray.rayangle);
	if (param->ray.rayright == -1 && xstep > 0)
		xstep *= -1;
	if (param->ray.rayright == 1 && xstep < 0)
		xstep *= -1;
	nexthorzy = yintercept;
	nexthorzx = xintercept;
	if (param->ray.raydown == -1)
		nexthorzy--;
	while (nexthorzx >= 0 && nexthorzx <= WIN_WIDTH
		&& nexthorzy >= 0 && nexthorzy <= WIN_HEIGHT)
	{
		if (ft_iswall(nexthorzx, nexthorzy) == 1)
		{
			horzhit = 1;
			param->ray.horzhitx = nexthorzx;
			param->ray.horzhity = nexthorzy;
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
			param->player.y, param->ray.horzhitx, param->ray.horzhity);
	else
		horzhitdistance = INT_MAX;
	return (horzhitdistance);
}

float	ft_findverthit(t_param *param)
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
	if (param->ray.rayright == 1)
		xintercept += TILE_S;
	yintercept = param->player.y + ((xintercept - param->player.x)
		* tan(param->ray.rayangle));
	xstep = TILE_S;
	if (param->ray.rayright == -1)
		xstep *= -1;
	ystep = TILE_S * tan(param->ray.rayangle);
	if (param->ray.raydown == -1 && ystep > 0)
		ystep *= -1;
	if (param->ray.raydown == 1 && ystep < 0)
		ystep *= -1;
	nextverty = yintercept;
	nextvertx = xintercept;
	if (param->ray.rayright == -1)
		nextvertx--;
	while (nextvertx >= 0 && nextvertx <= WIN_WIDTH &&
		nextverty >= 0 && nextverty <= WIN_HEIGHT)
	{
		if (ft_iswall(nextvertx, nextverty) == 1)
		{
			verthit = 1;
			param->ray.verthitx = nextvertx;
			param->ray.verthity = nextverty;
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
			param->player.y, param->ray.verthitx, param->ray.verthity);
	else
		verthitdistance = INT_MAX;
	return (verthitdistance);
}

void	ft_compdistance(float horzhitdistance,
	float verthitdistance, t_param *param)
{
	if (horzhitdistance <= verthitdistance)
	{
		param->ray.wallhitx = param->ray.horzhitx;
		param->ray.wallhity = param->ray.horzhity;
		param->ray.colldistance = horzhitdistance;
		param->ray.washitvert = 0;
	}
	if (horzhitdistance > verthitdistance)
	{
		param->ray.wallhitx = param->ray.verthitx;
		param->ray.wallhity = param->ray.verthity;
		param->ray.colldistance = verthitdistance;
		param->ray.washitvert = 1;
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
		param->ray.id = id;
		param->ray.rayangle = ft_normalizeangle(angle);
		ft_initrays(&param->ray);
		ft_raydirection(param, param->ray.rayangle);
		ft_compdistance(ft_findhorzhit(param), ft_findverthit(param), param);
		ft_drawline(param->player.x * MINIMAP, param->player.y *
			MINIMAP, param->ray.colldistance * MINIMAP,
			param->ray.rayangle, param);
		ft_render3d(param);
		angle += FOV / NUM_RAYS;
		id++;
	}
}