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
			param->texture[i].path, &param->texture[i].width, &param->texture[i].height);
		param->texture[i].data = (int *)mlx_get_data_addr(param->texture[i].ptr,
			&param->texture[i].bpp, &param->texture[i].size_l,
			&param->texture[i].endian);
		i++;
	}
/*	param->texture[0].ptr = mlx_xpm_file_to_image(param->mlx_ptr,
		param->texture[0].path, &param->texture[0].width, &param->texture[0].height);
	param->texture[1].ptr = mlx_xpm_file_to_image(param->mlx_ptr,
		param->texture[1].path, &param->texture[1].width, &param->texture[1].height);
	param->texture[2].ptr = mlx_xpm_file_to_image(param->mlx_ptr,
		param->texture[2].path, &param->texture[2].width, &param->texture[2].height);
	param->texture[3].ptr = mlx_xpm_file_to_image(param->mlx_ptr,
		param->texture[3].path, &param->texture[3].width, &param->texture[3].height);
	param->texture[0].data = (int *)mlx_get_data_addr(param->texture[0].ptr,
		&param->texture[0].bpp, &param->texture[0].size_l,
		&param->texture[0].endian);
	param->texture[1].data = (int *)mlx_get_data_addr(param->texture[1].ptr,
		&param->texture[1].bpp, &param->texture[1].size_l,
		&param->texture[1].endian);
	param->texture[2].data = (int *)mlx_get_data_addr(param->texture[2].ptr,
		&param->texture[2].bpp, &param->texture[2].size_l,
		&param->texture[2].endian);
	param->texture[3].data = (int *)mlx_get_data_addr(param->texture[3].ptr,
		&param->texture[3].bpp, &param->texture[3].size_l,
		&param->texture[3].endian);*/
}

void	ft_puttxt(t_param *param, int y, int x, int end, int txt)
{
	int textureoffsetx;
	int distancefromtop;
	int textureoffsety;

	if (param->ray.washitvert == 1)
		textureoffsetx = (int)(param->ray.wallhity * param->texture[txt].width / param->tile_s) % param->texture[txt].width;
	else
		textureoffsetx = (int)(param->ray.wallhitx * param->texture[txt].width /
			param->tile_s) % param->texture[txt].width;
	while (y < end)
	{
		distancefromtop = y + (param->ray.wallheight / 2) - (param->win_height / 2);
		textureoffsety = distancefromtop * ((float)param->texture[txt].height /
			param->ray.wallheight);
		param->img.data[y * param->win_width + x] = param->texture[txt].data[
				(textureoffsety * param->texture[txt].width) + textureoffsetx];
		y++;
	}
}
