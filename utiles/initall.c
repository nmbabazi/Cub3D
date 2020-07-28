/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 16:16:20 by user42            #+#    #+#             */
/*   Updated: 2020/07/28 16:20:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

void	ft_initstructsprite(t_param *param)
{
	param->sprite.x = NULL;
	param->sprite.y = NULL;
	param->sprite.distance = NULL;
	param->sprite.angle = 0;
	param->sprite.ptr = NULL;
	param->sprite.data = NULL;
	param->sprite.bpp = 0;
	param->sprite.endian = 0;
	param->sprite.size_l = 0;
	param->sprite.width = 0;
	param->sprite.height = 0;
	param->sprite.path = NULL;
	param->sprite.nb_sprite = 0;
	param->sprite.buffer = NULL;
	param->sprite.spritescreenx = 0;
	param->sprite.drawstarty = 0;
	param->sprite.drawendy = 0;
	param->sprite.drawstartx = 0;
	param->sprite.drawendx = 0;
}

void	ft_initstructplayer(t_param *param)
{
	param->player.x = 0;
	param->player.y = 0;
	param->player.turndirection = 0;
	param->player.walkdirection = 0;
	param->player.rotationangle = 0;
	param->player.walkspeed = 0;
	param->player.turnspeed = 0;
	param->player.translation = 0;
	param->player.facingvert = 0;
	param->player.c = 0;
	param->player.diry = 0;
	param->player.dirx = 0;
	param->player.plany = 0;
	param->player.planx = 0;
}

void	ft_initstructray(t_param *param)
{
	param->ray.rayangle = 0;
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
	param->ray.yintercept = 0;
	param->ray.xintercept = 0;
	param->ray.xstep = 0;
	param->ray.ystep = 0;
	param->ray.nextcheck = 0;
}

void	ft_initstructxt(t_param *param)
{
	int i;

	i = 0;
	while (i < 4)
	{
		param->texture[i].ptr = NULL;
		param->texture[i].data = NULL;
		param->texture[i].bpp = 0;
		param->texture[i].endian = 0;
		param->texture[i].size_l = 0;
		param->texture[i].width = 0;
		param->texture[i].height = 0;
		param->texture[i].path = 0;
		i++;
	}
}

void	ft_initeverything(t_param *param)
{
	param->win_height = 0;
	param->win_width = 0;
	param->f_color = 0;
	param->c_color = 0;
	param->map_cols = 0;
	param->map_rows = 0;
	param->tile_s = 0;
	param->map = NULL;
	param->map_cols = 0;
	param->map_rows = 0;
	param->num_rays = 0;
	param->argument = 0;
	ft_initimg(param);
	ft_initstructsprite(param);
	ft_initstructplayer(param);
	ft_initstructray(param);
	ft_initstructxt(param);
}
