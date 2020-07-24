/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initsprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:45:23 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/24 14:55:13 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

void	ft_spritetxt(t_param *param)
{
	param->sprite.ptr = mlx_xpm_file_to_image(param->mlx_ptr,
		param->sprite.path,
			&param->sprite.width, &param->sprite.height);
	param->sprite.data = (int *)mlx_get_data_addr(param->sprite.ptr,
			&param->sprite.bpp, &param->sprite.size_l, &param->sprite.endian);
}

int		ft_countsprite(t_param *param)
{
	int i;
	int l;
	int nb_sprite;

	i = 0;
	l = 0;
	nb_sprite = 0;
	while (l < param->map_rows)
	{
		i = 0;
		while (i < param->map_cols)
		{
			if (param->map[l][i] == '2')
				nb_sprite++;
			i++;
		}
		l++;
	}
	return (nb_sprite);
}

int		ft_mallocsprite(t_param *param)
{
	param->sprite.nb_sprite = ft_countsprite(param);
	if (!(param->sprite.x = malloc(sizeof(float) * param->sprite.nb_sprite)))
		return (0);
	if (!(param->sprite.y = malloc(sizeof(float) * param->sprite.nb_sprite)))
		return (0);
	if (!(param->sprite.distance = (float *)malloc(sizeof(float)
		* param->sprite.nb_sprite)))
		return (0);
	if (!(param->sprite.buffer = malloc(sizeof(float) * param->win_width)))
		return (0);
	return (1);
}

void	ft_puttozero(t_param *param)
{
	param->sprite.angle = 0;
	param->sprite.ptr = 0;
	param->sprite.data = 0;
	param->sprite.bpp = 0;
	param->sprite.endian = 0;
	param->sprite.size_l = 0;
	param->sprite.width = 0;
	param->sprite.height = 0;
}

void	ft_initsprite(t_param *param)
{
	int	i;
	int l;
	int id;

	i = -1;
	l = -1;
	id = 0;
	if (ft_mallocsprite(param) == 0)
		return ;
	while (l++ < param->map_rows && id < param->sprite.nb_sprite)
	{
		i = 0;
		while (i++ < param->map_cols)
		{
			if (param->map[l][i] == '2')
			{
				param->sprite.x[id] = i * param->tile_s + param->tile_s / 2;
				param->sprite.y[id] = l * param->tile_s + param->tile_s / 2;
				param->sprite.distance[id] = 0;
				id++;
			}
		}
	}
	ft_puttozero(param);
	ft_spritetxt(param);
}
