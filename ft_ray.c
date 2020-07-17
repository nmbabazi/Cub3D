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
	param->ray.vertwallhitx = 0;
	param->ray.vertwallhity = 0;
	param->ray.horzwallhitx = 0;
	param->ray.horzwallhity = 0;
	param->ray.nextcheck = 0;
}

int		ft_findhithorz(t_param *param, float nexthorzx, float nexthorzy)
{
	int	hit;

	param->ray.nextcheck = param->ray.yintercept;
	while (nexthorzx >= 0 && nexthorzx <= param->map_cols * param->tile_s
		&& nexthorzy >= 0 && nexthorzy <= param->map_rows * param->tile_s
		&& param->ray.nextcheck >= 0
		&& param->ray.nextcheck <= param->map_rows * param->tile_s)
	{
		param->ray.nextcheck = nexthorzy;
		if (param->ray.raydown == -1)
			param->ray.nextcheck--;
		if (ft_iswall(nexthorzx, param->ray.nextcheck, param) == 1)
		{
			hit = 1;
			param->ray.horzwallhitx = nexthorzx;
			param->ray.horzwallhity = nexthorzy;
			break ;
		}
		else
		{
			nexthorzx += param->ray.xstep;
			nexthorzy += param->ray.ystep;
		}
	}
	return (hit);
}

int		ft_findhitvert(t_param *param, float nextvertx, float nextverty)
{
	int	hit;

	param->ray.nextcheck = param->ray.xintercept;
	while (nextvertx >= 0 && nextvertx <= param->map_cols * param->tile_s
		&& nextverty >= 0 && nextverty <= param->map_rows * param->tile_s
		&& param->ray.nextcheck >= 0
		&& param->ray.nextcheck <= param->map_cols * param->tile_s)
	{
		param->ray.nextcheck = nextvertx;
		if (param->ray.rayright == -1)
			param->ray.nextcheck--;
		if (ft_iswall(param->ray.nextcheck, nextverty, param) == 1)
		{
			hit = 1;
			param->ray.vertwallhitx = nextvertx;
			param->ray.vertwallhity = nextverty;
			break ;
		}
		else
		{
			nextvertx += param->ray.xstep;
			nextverty += param->ray.ystep;
		}
	}
	return (hit);
}

float	ft_casthorzray(t_param *param)
{
	float	nexthorzy;
	float	nexthorzx;

	param->ray.yintercept = floor(param->player.y / param->tile_s)
		* param->tile_s;
	if (param->ray.raydown == 1)
		param->ray.yintercept += param->tile_s;
	param->ray.xintercept = param->player.x +
		((param->ray.yintercept - param->player.y) / tan(param->ray.rayangle));
	param->ray.ystep = param->tile_s;
	if (param->ray.raydown == -1)
		param->ray.ystep *= -1;
	param->ray.xstep = param->tile_s / tan(param->ray.rayangle);
	if (param->ray.rayright == -1 && param->ray.xstep > 0)
		param->ray.xstep *= -1;
	if (param->ray.rayright == 1 && param->ray.xstep < 0)
		param->ray.xstep *= -1;
	nexthorzy = param->ray.yintercept;
	nexthorzx = param->ray.xintercept;
	if (ft_findhithorz(param, nexthorzx, nexthorzy) == 1)
		return (ft_distance(param->player.x, param->player.y,
			param->ray.horzwallhitx, param->ray.horzwallhity));
	else
		return (INT_MAX);
}

float	ft_castvertray(t_param *param)
{
	float	nextverty;
	float	nextvertx;

	param->ray.xintercept = floor(param->player.x / param->tile_s)
		* param->tile_s;
	if (param->ray.rayright == 1)
		param->ray.xintercept += param->tile_s;
	param->ray.yintercept = param->player.y +
		((param->ray.xintercept - param->player.x) * tan(param->ray.rayangle));
	param->ray.xstep = param->tile_s;
	if (param->ray.rayright == -1)
		param->ray.xstep *= -1;
	param->ray.ystep = param->tile_s * tan(param->ray.rayangle);
	if (param->ray.raydown == -1 && param->ray.ystep > 0)
		param->ray.ystep *= -1;
	if (param->ray.raydown == 1 && param->ray.ystep < 0)
		param->ray.ystep *= -1;
	nextverty = param->ray.yintercept;
	nextvertx = param->ray.xintercept;
	if (ft_findhitvert(param, nextvertx, nextverty) == 1)
		return (ft_distance(param->player.x, param->player.y,
			param->ray.vertwallhitx, param->ray.vertwallhity));
	else
		return (INT_MAX);
}

void	ft_findhitdirection(t_param *param, float horzhitdistance,
			float verthitdistance)
{
	if (horzhitdistance <= verthitdistance)
	{
		param->ray.wallhitx = param->ray.horzwallhitx;
		param->ray.wallhity = param->ray.horzwallhity;
		param->ray.colldistance = horzhitdistance;
		param->ray.washitvert = 0;
	}
	if (horzhitdistance > verthitdistance)
	{
		param->ray.wallhitx = param->ray.vertwallhitx;
		param->ray.wallhity = param->ray.vertwallhity;
		param->ray.colldistance = verthitdistance;
		param->ray.washitvert = 1;
	}
}

void	ft_castallrays(t_param *param)
{
	int		id;
	float	angle;
	float	horzhitdistance;
	float	verthitdistance;

	id = 0;
	angle = param->player.rotationangle - (FOV / 2);
	while (id < param->win_width)
	{
		param->ray.rayangle = ft_normalizeangle(angle);
		ft_initrays(param, id);
		ft_raydirection(param, param->ray.rayangle, id);
		horzhitdistance = ft_casthorzray(param);
		verthitdistance = ft_castvertray(param);
		ft_findhitdirection(param, horzhitdistance, verthitdistance);
		ft_drawline(param->player.x * MINIMAP, param->player.y * MINIMAP,
			param->ray.rayangle, param);
		ft_render3d(param, id);
		angle += FOV / param->win_width;
		id++;
	}
}
