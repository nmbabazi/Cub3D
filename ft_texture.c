/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 16:25:52 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/06/20 17:26:17 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include.h"


void	ft_inittexture(t_param *param)
{
	
	param->texture[0].ptr = mlx_xpm_file_to_image(param->mlx_ptr, "txt-nord.xpm", &param->texture[0].width, &param->texture[0].height);
	param->texture[1].ptr = mlx_xpm_file_to_image(param->mlx_ptr, "txt-sud.xpm", &param->texture[1].width, &param->texture[1].height);
	param->texture[2].ptr = mlx_xpm_file_to_image(param->mlx_ptr, "txt-est.xpm", &param->texture[2].width, &param->texture[2].height);
	param->texture[3].ptr = mlx_xpm_file_to_image(param->mlx_ptr, "txt-west.xpm", &param->texture[3].width, &param->texture[3].height);

	param->texture[0].data = (int *)mlx_get_data_addr(param->texture[0].ptr, &param->texture[0].bpp, &param->texture[0].size_l, &param->texture[0].endian);
	param->texture[1].data = (int *)mlx_get_data_addr(param->texture[1].ptr, &param->texture[1].bpp, &param->texture[1].size_l, &param->texture[1].endian);
	param->texture[2].data = (int *)mlx_get_data_addr(param->texture[2].ptr, &param->texture[2].bpp, &param->texture[2].size_l, &param->texture[2].endian);
	param->texture[3].data = (int *)mlx_get_data_addr(param->texture[3].ptr, &param->texture[3].bpp, &param->texture[3].size_l, &param->texture[3].endian);
}

void ft_puttxt(t_param *param, int y, int x, int end, int i)
{
	int textureOffsetX;
	if (param->ray.wasHitVert == 1)
		textureOffsetX = (int)(param->ray.wallHitY * param->texture[i].width / TILE_S) % param->texture[i].width;
	else
		textureOffsetX = (int)(param->ray.wallHitX * param->texture[i].width / TILE_S) % param->texture[i].width;
	while (y < end)
	{
			int distanceFromtop = y + (param->ray.wallHeight / 2) - (WIN_HEIGHT / 2);
			int textureOffsetY = distanceFromtop * ((float)param->texture[i].height / param->ray.wallHeight);
			param->img.data[y * WIN_WIDTH + x] = param->texture[i].data[(textureOffsetY * param->texture[i].width) + textureOffsetX];
			y++;
	}
}
