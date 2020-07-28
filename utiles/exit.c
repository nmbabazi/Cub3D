/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:58:27 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/28 16:18:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

void	ft_freemap(t_param *param)
{
	int l;

	l = 0;
	while (l < param->map_rows)
	{
		if (param->map[l] != NULL)
			free(param->map[l]);
		l++;
	}
	if (param->map != NULL)
		free(param->map);
}

void	ft_freesprite(t_param *param)
{
	free(param->sprite.x);
	free(param->sprite.y);
	free(param->sprite.distance);
	free(param->sprite.buffer);
}

int		exit_properly(void *data)
{
	t_param *param;

	param = (t_param *)data;
	ft_freemap(param);
	ft_freepath(param);
	ft_freesprite(param);
	exit(0);
	return (1);
}

void	ft_screen_size(t_param *param)
{
	int sizex;
	int sizey;

	sizex = 0;
	sizey = 0;
	mlx_get_screen_size(param->mlx_ptr, &sizex, &sizey);
	if (param->win_width > sizex)
		param->win_width = (unsigned int)sizex;
	if (param->win_height > sizey)
		param->win_height = (unsigned int)sizey;
	if (param->win_height < 60)
		param->win_height = 60;
	if (param->win_width < 60)
		param->win_width = 60;
	param->tile_s = param->win_width / param->map_cols;
	param->num_rays = param->win_width;
}

void	ft_initimg(t_param *param)
{
	param->img.img_ptr = NULL;
	param->img.data = NULL;
	param->img.bpp = 0;
	param->img.endian = 0;
	param->img.size_l = 0;
}
