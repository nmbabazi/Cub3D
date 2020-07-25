/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 11:47:27 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/25 17:36:34 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

void	ft_raydirection(t_param *param, float angle, int id)
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
		ft_render3d(param, id);
		angle += FOV / param->win_width;
		id++;
	}
}
