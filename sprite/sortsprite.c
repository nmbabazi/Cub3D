/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortsprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:49:32 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/24 14:55:03 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

void	ft_spritedistance(t_param *param)
{
	int id;

	id = 0;
	while (id < param->sprite.nb_sprite)
	{
		param->sprite.distance[id] = ft_distance(param->player.x,
			param->player.y, param->sprite.x[id], param->sprite.y[id]);
		id++;
	}
}

void	ft_switch(t_param *param, int i, int j)
{
	float	temp_dist;
	float	temp_y;
	float	temp_x;

	temp_dist = param->sprite.distance[j];
	temp_x = param->sprite.x[j];
	temp_y = param->sprite.y[j];
	param->sprite.distance[j] = param->sprite.distance[i];
	param->sprite.x[j] = param->sprite.x[i];
	param->sprite.y[j] = param->sprite.y[i];
	param->sprite.distance[i] = temp_dist;
	param->sprite.x[i] = temp_x;
	param->sprite.y[i] = temp_y;
}

void	ft_sortsprite(t_param *param)
{
	int		j;
	int		i;

	i = -1;
	while (i++ < param->sprite.nb_sprite)
	{
		j = i + 1;
		while (j < param->sprite.nb_sprite)
		{
			if (param->sprite.distance[j] > param->sprite.distance[i])
				ft_switch(param, i, j);
			j++;
		}
	}
}
