/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:58:27 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/24 16:39:41 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

void	ft_freemap(t_param *param)
{
	int l;

	l = 0;
	while (l < param->map_rows)
	{
		free(param->map[l]);
		l++;
	}
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
	ft_freesprite(param);
	exit(0);
	return (1);
}
