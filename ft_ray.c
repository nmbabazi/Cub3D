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
	param->ray[id].wallhitx = 0;
	param->ray[id].wallhity = 0;
	param->ray[id].colldistance = 0;
	param->ray[id].raydown = 0;
	param->ray[id].rayright = 0;
	param->ray[id].washitvert = 0;
	param->ray[id].wallheight = 0;
}

void	ft_castsingleray(t_param *param, int id)
{
	ft_raydirection(param, param->ray[id].rayangle, id);
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
	if (param->ray[id].raydown == 1)
		yintercept += TILE_S;
	xintercept = param->player.x + ((yintercept - param->player.y) / tan(param->ray[id].rayangle));
	ystep = TILE_S;
	if (param->ray[id].raydown == -1)
		ystep *= -1;
	xstep = TILE_S / tan(param->ray[id].rayangle);
	if (param->ray[id].rayright == -1 && xstep > 0)
		xstep *= -1;
	if (param->ray[id].rayright == 1 && xstep < 0)
		xstep *= -1;
	float	nexthorzy = yintercept;
	float	nexthorzx = xintercept;
	float	nexthorzycheck = yintercept;
	while (nexthorzx >= 0 && nexthorzx <= WIN_WIDTH  && nexthorzy >= 0 && nexthorzy <= WIN_HEIGHT && nexthorzycheck >= 0 && nexthorzycheck <= WIN_HEIGHT)
	{
		nexthorzycheck = nexthorzy;
		if (param->ray[id].raydown == -1)
			nexthorzycheck--;
		if (ft_iswall(nexthorzx , nexthorzycheck) == 1)
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
	if (param->ray[id].rayright == 1)
		xintercept += TILE_S;
	yintercept = param->player.y + ((xintercept - param->player.x) * tan(param->ray[id].rayangle));
	xstep = TILE_S;
	if (param->ray[id].rayright == -1)
		xstep *= -1;
	ystep = TILE_S * tan(param->ray[id].rayangle);
	if (param->ray[id].raydown == -1 && ystep > 0)
		ystep *= -1;
	if (param->ray[id].raydown == 1 && ystep < 0)
		ystep *= -1;
	float	nextverty = yintercept;
	float	nextvertx = xintercept;
	float	nextvertxcheck = xintercept;
	while (nextvertx >= 0 && nextvertx <= WIN_WIDTH  && nextverty >= 0 && nextverty <= WIN_HEIGHT && nextvertxcheck >= 0 && nextvertxcheck <= WIN_WIDTH)
	{
		nextvertxcheck = nextvertx;
		if (param->ray[id].rayright == -1)
			nextvertxcheck--;
		if (ft_iswall(nextvertxcheck, nextverty) == 1)
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
		param->ray[id].wallhitx = horzwallhitx;
		param->ray[id].wallhity = horzwallhity;
		param->ray[id].colldistance = horzhitdistance;
		param->ray[id].washitvert = 0;
	}
	if (horzhitdistance > verthitdistance)
	{
		param->ray[id].wallhitx = vertwallhitx;
		param->ray[id].wallhity = vertwallhity;
		param->ray[id].colldistance = verthitdistance;
		param->ray[id].washitvert = 1;
	}
//	printf("%f\n", param->ray[id].wallhitx);
/////////////////RENDER////////////////////////
	ft_drawline(param->player.x * MINIMAP, param->player.y * MINIMAP, param->ray[id].colldistance * MINIMAP, param->ray[id].rayangle, param);
//////////////////////////////////////////////
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
		ft_castsingleray(param, id);
		ft_render3d(param, id);
		angle += FOV / NUM_RAYS;
		id++;
	}
}
