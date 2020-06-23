/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:34:32 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/06/23 18:34:34 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void    ft_initsprite(const char map[MAP_ROWS][MAP_COLS], t_param *param)
{
    int i;
	int l;

	i = 0;
	l = 0;
	while (l < MAP_ROWS)
	{
		i = 0;
		while (i < MAP_COLS)
		{
			if (map[l][i] == 'x')
			{
				param->sprite.xsprite = i * TILE_S + TILE_S / 2;
				param->sprite.ysprite = l * TILE_S + TILE_S / 2;
				break ;
			}
			i++;
		}
		l++;
	}
    param->sprite.sprite_height = 20;
    param->sprite.sprite_width = 20;
}
