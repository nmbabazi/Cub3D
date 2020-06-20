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
		param->ray.rayDown = 1;
	else
		param->ray.rayDown = -1;
	if (angle < (M_PI * 0.5) || angle > (M_PI * 1.5))
		param->ray.rayRight = 1;
	else
		param->ray.rayRight = -1;
}

void	ft_initrays(t_ray *ray)
{
	ray->rayAngle = 0;
	ray->wallHitX = 0;
	ray->wallHitY = 0;
	ray->collDistance = 0;
	ray->rayDown = 0;
	ray->rayRight = 0;
	ray->wasHitVert = 0;
	ray->wallHeight = 0;
}

void	ft_castsingleray(t_param *param, float angle, int i)
{
	ft_initrays(&param->ray);
	angle = ft_normalizeAngle(angle);
	ft_raydirection(param, angle);
//////////////////////HORIZONTAL//////////////////////////
	float horzHitDistance = 0;
	float vertHitDistance = 0;
	int	horzHit = 0;
	float	horzWallHitX = 0;
	float	horzWallHitY = 0;
	float yintercept;
	float xintercept;
	float xstep;
	float ystep;

	yintercept = floor(param->player.y / TILE_S) * TILE_S;
	if (param->ray.rayDown == 1)
		yintercept += TILE_S;
	xintercept = param->player.x + ((yintercept - param->player.y) / tan(angle));
	ystep = TILE_S;
	if (param->ray.rayDown == -1)
		ystep *= -1;
	xstep = TILE_S / tan(angle);
	if (param->ray.rayRight == -1 && xstep > 0)
		xstep *= -1;
	if (param->ray.rayRight == 1 && xstep < 0)
		xstep *= -1;
	float	nextHorzY = yintercept;
	float	nextHorzX = xintercept;
	if (param->ray.rayDown == -1)
		nextHorzY--;
	while (nextHorzX >= 0 && nextHorzX <= WIN_WIDTH  && nextHorzY >= 0 && nextHorzY <= WIN_HEIGHT)
	{
		if (ft_isWall(nextHorzX , nextHorzY) == 1)
		{
			horzHit = 1;
			horzWallHitX = nextHorzX;
			horzWallHitY = nextHorzY;
			break;
		}
		else
		{
			nextHorzX += xstep;
			nextHorzY += ystep;
		}
	}
/////////////////////VERTICAL//////////////////////////
	int	vertHit = 0;
	float	vertWallHitX = 0;
	float	vertWallHitY = 0;
	xintercept = floor(param->player.x / TILE_S) * TILE_S;
	if (param->ray.rayRight == 1)
		xintercept += TILE_S;
	yintercept = param->player.y + ((xintercept - param->player.x) * tan(angle));
	xstep = TILE_S;
	if (param->ray.rayRight == -1)
		xstep *= -1;
	ystep = TILE_S * tan(angle);
	if (param->ray.rayDown == -1 && ystep > 0)
		ystep *= -1;
	if (param->ray.rayDown == 1 && ystep < 0)
		ystep *= -1;
	float	nextVertY = yintercept;
	float	nextVertX = xintercept;
	if (param->ray.rayRight == -1)
		nextVertX--;
	while (nextVertX >= 0 && nextVertX <= WIN_WIDTH  && nextVertY >= 0 && nextVertY <= WIN_HEIGHT)
	{
		if (ft_isWall(nextVertX, nextVertY) == 1)
		{
			vertHit = 1;
			vertWallHitX = nextVertX;
			vertWallHitY = nextVertY;
			break;
		}
		else
		{
			nextVertX += xstep;
			nextVertY += ystep;
		}
	}
//////////////////////DISTANCES////////////////////
	if (horzHit == 1)
		horzHitDistance = ft_distance(param->player.x, param->player.y, horzWallHitX, horzWallHitY);
	else
		horzHitDistance = INT_MAX;
	if (vertHit == 1)
		vertHitDistance = ft_distance(param->player.x, param->player.y, vertWallHitX, vertWallHitY);
	else
		vertHitDistance = INT_MAX;
///////////////////RESULTAT////////////////////
	if (horzHitDistance <= vertHitDistance)
	{
		param->ray.wallHitX = horzWallHitX;
		param->ray.wallHitY = horzWallHitY;
		param->ray.collDistance = horzHitDistance;
		param->ray.wasHitVert = 0;
	}
	if (horzHitDistance > vertHitDistance)
	{
		param->ray.wallHitX = vertWallHitX;
		param->ray.wallHitY = vertWallHitY;
		param->ray.collDistance = vertHitDistance;
		param->ray.wasHitVert = 1;
	}
/////////////////RENDER////////////////////////
	ft_drawline(param->player.x * MINIMAP, param->player.y * MINIMAP, param->ray.collDistance * MINIMAP, 0xffff00, angle, param);
//////////////////////////////////////////////
	ft_render3D(param, angle, i);
}

void	ft_castallrays(t_param *param)
{
	float angle = param->player.rotationAngle - (FOV / 2);
	int i = 0;
	angle = ft_normalizeAngle(angle);

	while (i < NUM_RAYS)
	{
		ft_castsingleray(param, angle, i);
		angle += FOV / NUM_RAYS;
		i++;
	}
}
