/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horzandvert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:34:11 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/28 14:51:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

int		ft_findhithorz(t_param *param, float nexthorzx, float nexthorzy)
{
	int	hit;

	hit = 0;
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

	hit = 0;
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
