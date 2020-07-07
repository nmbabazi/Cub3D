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
	param->ray[id].horzhity = 0;
	param->ray[id].horzhitx = 0;
//	float spritehitdistance;

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
	float	nexthorzycheck = yintercept;
	while (nexthorzx >= 0 && nexthorzx <= WIN_WIDTH
		&& nexthorzy >= 0 && nexthorzy <= WIN_HEIGHT &&
		nexthorzycheck >= 0 && nexthorzycheck <= WIN_HEIGHT)
	{
		nexthorzycheck = nexthorzy;
		if (param->ray[id].raydown == -1)
			nexthorzycheck--;
		if (ft_iswall(nexthorzx, nexthorzycheck) == 1)
		{
			horzhit = 1;
			param->ray[id].horzhitx = nexthorzx;
			param->ray[id].horzhity = nexthorzy;
			break ;
		}
	/*	if (ft_issprite(nexthorzx, nexthorzy) == 1)
		{
			horzhit = 2;
			param->ray[id].horzhitx = nexthorzx;
			param->ray[id].horzhity = nexthorzy;
			spritehitdistance = 6 / cos(param->ray[id].rayangle);
			break ;
		}*/
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
	float	nextvertxcheck = xintercept;
	while (nextvertx >= 0 && nextvertx <= WIN_WIDTH &&
		nextverty >= 0 && nextverty <= WIN_HEIGHT &&
		nextvertxcheck >= 0 && nextvertxcheck <= WIN_WIDTH)
	{
		nextvertxcheck = nextvertx;
		if (param->ray[id].rayright == -1)
			nextvertxcheck--;
		if (ft_iswall(nextvertxcheck, nextverty) == 1)
		{
			verthit = 1;
			param->ray[id].verthitx = nextvertx;
			param->ray[id].verthity = nextverty;
			break ;
		}
	/*	if (ft_issprite(nextvertx, nextverty) == 1)
		{	
			verthit = 2;
			param->ray[id].verthitx = nextvertx;
			param->ray[id].verthity = nextverty;
			break ;
		}*/
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


/*int	ft_spritecollision(int x_sprite, int y_sprite, float distance, float angle,
		t_param *param)
{
	float	i;
	int		x;
	int		y;
	int		longeur;

	longeur = 0;
	i = 0;
	x = 0;
	y = 0;
	while (i < distance)
	{
	//	param->img.data[(y_start + y) * WIN_WIDTH + (x_start + x)] = 0xffff00;
		if((x <= param->sprite.xsprite - (param->sprite.sprite_width / 2) &&
		x >= param->sprite.xsprite + (param->sprite.sprite_width / 2)) &&
		(y <= param->sprite.ysprite - (param->sprite.sprite_height / 2) &&
		y >= param->sprite.ysprite + (param->sprite.sprite_height / 2)))
			return (1);
		x = cos(angle) * longeur;
		y = sin(angle) * longeur;
		longeur++;
		i++;
	}
	return (0);
}*/

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
	//	ft_render3d(param, id);
	/*	if (ft_spritecollision(param->sprite.xsprite * MINIMAP, param->sprite.ysprite *
			MINIMAP, param->ray[id].colldistance * MINIMAP,
			param->ray[id].rayangle, param) == 1)
			printf("HERE\n");*/
		angle += FOV / NUM_RAYS;
		id++;
	}
}