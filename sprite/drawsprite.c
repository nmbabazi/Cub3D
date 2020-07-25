/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawsprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:51:29 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/25 16:32:50 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

void	ft_zero(t_param *param)
{
	param->sprite.drawstartx = 0;
	param->sprite.drawendx = 0;
	param->sprite.drawstarty = 0;
	param->sprite.drawendy = 0;
	param->sprite.spritescreenx = 0;
}

void	ft_puttexture(t_param *param, int x, int y, float sprite_size)
{
	int		textureoffsetx;
	int		distancefromtop;
	int		textureoffsety;
	int		color;

	textureoffsetx = (int)(256 * (x - (-sprite_size /
		2 + param->sprite.spritescreenx)) * param->sprite.width
		/ sprite_size) / 256;
	distancefromtop = (y) * 256 - param->win_height *
		128 + sprite_size * 128;
	textureoffsety = ((distancefromtop *
		param->sprite.height) / sprite_size) / 256;
	color = param->sprite.data[(textureoffsety *
		param->sprite.width) + textureoffsetx];
	if (color != 0x000000)
		param->img.data[y * param->win_width + x] = color;
}

void	ft_drawsprite(t_param *param, float transformy, float sprite_size)
{
	int		y;
	int		x;

	x = param->sprite.drawstartx;
	while (x < param->sprite.drawendx)
	{
		if (transformy > 0 && x > 0 && x < param->win_width
			&& transformy < param->sprite.buffer[x])
		{
			y = param->sprite.drawstarty;
			while (y < param->sprite.drawendy)
			{
				ft_puttexture(param, x, y, sprite_size);
				y++;
			}
		}
		x++;
	}
}
