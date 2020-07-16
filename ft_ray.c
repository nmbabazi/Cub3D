/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 11:47:27 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/06/29 15:04:14 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include "include.h"

void	ft_initrays(t_param *param, int id)
{
	param->ray.wallhitx = 0;
	param->ray.wallhity = 0;
	param->ray.colldistance = 0;
	param->ray.raydown = 0;
	param->ray.rayright = 0;
	param->ray.washitvert = 0;
	param->ray.wallheight = 0;
}

void	ft_castsingleray(t_param *param, int id)
{
	ft_raydirection(param, param->ray.rayangle, id);
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

	yintercept = floor(param->player.y / param->tile_s) * param->tile_s;
	if (param->ray.raydown == 1)
		yintercept += param->tile_s;
	xintercept = param->player.x + ((yintercept - param->player.y) / tan(param->ray.rayangle));
	ystep = param->tile_s;
	if (param->ray.raydown == -1)
		ystep *= -1;
	xstep = param->tile_s / tan(param->ray.rayangle);
	if (param->ray.rayright == -1 && xstep > 0)
		xstep *= -1;
	if (param->ray.rayright == 1 && xstep < 0)
		xstep *= -1;
	float	nexthorzy = yintercept;
	float	nexthorzx = xintercept;
	float	nexthorzycheck = yintercept;
	while (nexthorzx >= 0 && nexthorzx <= param->map_cols * param->tile_s  && nexthorzy >= 0 && nexthorzy <= param->map_rows * param->tile_s && nexthorzycheck >= 0 && nexthorzycheck <= param->map_rows * param->tile_s)
	{
		nexthorzycheck = nexthorzy;
		if (param->ray.raydown == -1)
			nexthorzycheck--;
		if (ft_iswall(nexthorzx , nexthorzycheck, param) == 1)
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
	xintercept = floor(param->player.x / param->tile_s) * param->tile_s;
	if (param->ray.rayright == 1)
		xintercept += param->tile_s;
	yintercept = param->player.y + ((xintercept - param->player.x) * tan(param->ray.rayangle));
	xstep = param->tile_s;
	if (param->ray.rayright == -1)
		xstep *= -1;
	ystep = param->tile_s * tan(param->ray.rayangle);
	if (param->ray.raydown == -1 && ystep > 0)
		ystep *= -1;
	if (param->ray.raydown == 1 && ystep < 0)
		ystep *= -1;
	float	nextverty = yintercept;
	float	nextvertx = xintercept;
	float	nextvertxcheck = xintercept;
	while (nextvertx >= 0 && nextvertx <= param->map_cols * param->tile_s  && nextverty >= 0 && nextverty <= param->map_rows * param->tile_s && nextvertxcheck >= 0 && nextvertxcheck <= param->map_cols * param->tile_s)
	{
		nextvertxcheck = nextvertx;
		if (param->ray.rayright == -1)
			nextvertxcheck--;
		if (ft_iswall(nextvertxcheck, nextverty, param) == 1)
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
//	printf("%f\n", param->ray.wallhitx);
/////////////////RENDER////////////////////////
	ft_drawline(param->player.x * MINIMAP, param->player.y * MINIMAP, param->ray.colldistance * MINIMAP, param->ray.rayangle, param);
//////////////////////////////////////////////
}

void	ft_castallrays(t_param *param)
{
	int		id;
	float	angle;

	id = 0;
	angle = param->player.rotationangle - (FOV / 2);
	while (id < param->win_width)
	{
		param->ray.rayangle = ft_normalizeangle(angle);
		ft_initrays(param, id);
		ft_castsingleray(param, id);
		ft_render3d(param, id);
		angle += FOV / param->win_width;
		id++;
	}
		
	
}
