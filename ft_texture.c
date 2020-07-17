/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 16:25:52 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/06/29 18:31:13 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	ft_inittexture(t_param *param)
{
	int i;

	i = 0;
	while (i < 4)
	{
		param->texture[i].ptr = mlx_xpm_file_to_image(param->mlx_ptr,
			param->texture[i].path, &param->texture[i].width,
			&param->texture[i].height);
		param->texture[i].data = (int *)mlx_get_data_addr(param->texture[i].ptr,
			&param->texture[i].bpp, &param->texture[i].size_l,
			&param->texture[i].endian);
		i++;
	}
}

void	ft_puttxt(t_param *param, int y, int x, int txt)
{
	int textureoffsetx;
	int distancefromtop;
	int textureoffsety;
	int end;

	end = (param->win_height / 2) + (param->ray.wallheight / 2);
	end = end > param->win_height ? param->win_height : end;
	if (param->ray.washitvert == 1)
		textureoffsetx = (int)(param->ray.wallhity * param->texture[txt].width
			/ param->tile_s) % param->texture[txt].width;
	else
		textureoffsetx = (int)(param->ray.wallhitx * param->texture[txt].width /
			param->tile_s) % param->texture[txt].width;
	while (y < end)
	{
		distancefromtop = y + (param->ray.wallheight / 2)
			- (param->win_height / 2);
		textureoffsety = distancefromtop * ((float)param->texture[txt].height /
			param->ray.wallheight);
		param->img.data[y * param->win_width + x] = param->texture[txt].data[
				(textureoffsety * param->texture[txt].width) + textureoffsetx];
		y++;
	}
}
