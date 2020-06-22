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

void	ft_raydirection(t_param *param, float angle)
{
	if (angle > 0 && angle < M_PI)
		param->ray.raydown = 1;
	else
		param->ray.raydown = -1;
	if (angle < (M_PI * 0.5) || angle > (M_PI * 1.5))
		param->ray.rayright = 1;
	else
		param->ray.rayright = -1;
}

void	ft_initrays(t_ray *ray)
{
	ray->wallhitx = 0;
	ray->wallhity = 0;
	ray->colldistance = 0;
	ray->raydown = 0;
	ray->rayright = 0;
	ray->washitvert = 0;
	ray->wallheight = 0;
}

/*void	ft_castsingleray(t_param *param, int id)
{
	ft_initrays(&param->ray);
	ft_raydirection(param, param->ray.rayangle);
//////////////////////HORIZONTAL//////////////////////////
	float horzhitdistance = 0;
	float verthitdistance = 0;
	int	horzhit = 0;
	float	horzwallhitx = 0;
	float	horzwallhity = 0;
	float yintercept;
	float xintercept;
	float xstep;
	float ystep;

	yintercept = floor(param->player.y / TILE_S) * TILE_S;
	if (param->ray.raydown == 1)
		yintercept += TILE_S;
	xintercept = param->player.x + ((yintercept - param->player.y) / tan(param->ray.rayangle));
	ystep = TILE_S;
	if (param->ray.raydown == -1)
		ystep *= -1;
	xstep = TILE_S / tan(param->ray.rayangle);
	if (param->ray.rayright == -1 && xstep > 0)
		xstep *= -1;
	if (param->ray.rayright == 1 && xstep < 0)
		xstep *= -1;
	float	nexthorzy = yintercept;
	float	nexthorzx = xintercept;
	if (param->ray.raydown == -1)
		nexthorzy--;
	while (nexthorzx >= 0 && nexthorzx <= WIN_WIDTH  && nexthorzy >= 0 && nexthorzy <= WIN_HEIGHT)
	{
		if (ft_iswall(nexthorzx , nexthorzy) == 1)
		{
			horzhit = 1;
			horzwallhitx = nexthorzx;
			horzwallhity = nexthorzy;
			break;
		}
		else
		{
			nexthorzx += xstep;
			nexthorzy += ystep;
		}
	}
/////////////////////VERTICAL//////////////////////////
	int	verthit = 0;
	float	vertwallhitx = 0;
	float	vertwallhity = 0;
	xintercept = floor(param->player.x / TILE_S) * TILE_S;
	if (param->ray.rayright == 1)
		xintercept += TILE_S;
	yintercept = param->player.y + ((xintercept - param->player.x) * tan(param->ray.rayangle));
	xstep = TILE_S;
	if (param->ray.rayright == -1)
		xstep *= -1;
	ystep = TILE_S * tan(param->ray.rayangle);
	if (param->ray.raydown == -1 && ystep > 0)
		ystep *= -1;
	if (param->ray.raydown == 1 && ystep < 0)
		ystep *= -1;
	float	nextverty = yintercept;
	float	nextvertx = xintercept;
	if (param->ray.rayright == -1)
		nextvertx--;
	while (nextvertx >= 0 && nextvertx <= WIN_WIDTH  && nextverty >= 0 && nextverty <= WIN_HEIGHT)
	{
		if (ft_iswall(nextvertx, nextverty) == 1)
		{
			verthit = 1;
			vertwallhitx = nextvertx;
			vertwallhity = nextverty;
			break;
		}
		else
		{
			nextvertx += xstep;
			nextverty += ystep;
		}
	}
//////////////////////DISTANCES////////////////////
	if (horzhit == 1)
		horzhitdistance = ft_distance(param->player.x, param->player.y, horzwallhitx, horzwallhity);
	else
		horzhitdistance = INT_MAX;
	if (verthit == 1)
		verthitdistance = ft_distance(param->player.x, param->player.y, vertwallhitx, vertwallhity);
	else
		verthitdistance = INT_MAX;
///////////////////RESULTAT////////////////////
	if (horzhitdistance <= verthitdistance)
	{
		param->ray.wallhitx = horzwallhitx;
		param->ray.wallhity = horzwallhity;
		param->ray.colldistance = horzhitdistance;
		param->ray.washitvert = 0;
	}
	if (horzhitdistance > verthitdistance)
	{
		param->ray.wallhitx = vertwallhitx;
		param->ray.wallhity = vertwallhity;
		param->ray.colldistance = verthitdistance;
		param->ray.washitvert = 1;
	}
/////////////////RENDER////////////////////////
	ft_drawline(param->player.x * MINIMAP, param->player.y * MINIMAP, param->ray.colldistance * MINIMAP, param->ray.rayangle, param);
//////////////////////////////////////////////
	ft_render3d(param, param->ray.rayangle, id);
}*/

void	ft_castallrays(t_param *param)
{
	int		id;
	float	angle;

	id = 0;
	angle = param->player.rotationangle - (FOV / 2);
	while (id < NUM_RAYS)
	{
		param->ray.rayangle = ft_normalizeangle(angle);
		ft_castsingleray(param, id);
		angle += FOV / NUM_RAYS;
		id++;
	}
}
