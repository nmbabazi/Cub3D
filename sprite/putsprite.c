/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:34:32 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/24 14:54:36 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

float	ft_calculangle(t_param *param, float x, float y)
{
	float	vectx;
	float	vecty;
	float	playertospriteangle;
	float	spriteangle;
	float	playerangle;

	vectx = x - param->player.x;
	vecty = y - param->player.y;
	playertospriteangle = atan2(vecty, vectx);
	playerangle = ft_normalizeangle(param->player.rotationangle);
	spriteangle = playerangle - playertospriteangle;
	if (spriteangle < -3.14159)
		spriteangle += 2.0 * 3.14159;
	if (spriteangle > 3.14159)
		spriteangle -= 2.0 * 3.14159;
	spriteangle = fabs(spriteangle);
	return (spriteangle);
}

int		ft_spritevisible(t_param *param, int id, float sprite_size)
{
	float	spriteangle;
	float	spriteangle_end;
	float	wallspriteangle;
	float	fovsprite;

	spriteangle = fabs(ft_calculangle(param, param->sprite.x[id],
		param->sprite.y[id]));
	spriteangle_end = fabs(ft_calculangle(param, (param->sprite.x[id]
		+ sprite_size), (param->sprite.y[id] + sprite_size)));
	wallspriteangle = fabs(spriteangle_end - spriteangle);
	fovsprite = FOV / 2 + wallspriteangle;
	if (spriteangle < fovsprite)
		return (1);
	else
		return (0);
}

float	ft_gettransformy(t_param *param, int id, float sprite_size)
{
	float	spritex;
	float	spritey;
	float	invdet;
	float	transformx;
	float	transformy;

	spritex = param->sprite.x[id] - param->player.x;
	spritey = param->sprite.y[id] - param->player.y;
	invdet = 1.0 / (param->player.planx * param->player.diry
		- param->player.dirx * param->player.plany);
	transformx = invdet * (param->player.diry * spritex
		- param->player.dirx * spritey);
	transformy = invdet * (-param->player.plany * spritex
		+ param->player.planx * spritey);
	param->sprite.spritescreenx = (int)((param->win_width / 2) *
		(1 + -transformx / transformy));
	return (transformy);
}

void	ft_getstart(t_param *param, float sprite_size)
{
	int		spriteheight;
	int		spritewidth;

	spritewidth = sprite_size;
	param->sprite.drawstartx = -spritewidth / 2 + param->sprite.spritescreenx;
	if (param->sprite.drawstartx < 0)
		param->sprite.drawstartx = 0;
	param->sprite.drawendx = spritewidth / 2 + param->sprite.spritescreenx;
	if (param->sprite.drawendx >= param->win_width)
		param->sprite.drawendx = param->win_width - 1;
	spriteheight = sprite_size;
	param->sprite.drawstarty = -spriteheight / 2 + param->win_height / 2;
	if (param->sprite.drawstarty < 0)
		param->sprite.drawstarty = 0;
	param->sprite.drawendy = spriteheight / 2 + param->win_height / 2;
	if (param->sprite.drawendy >= param->win_height)
		param->sprite.drawendy = param->win_height - 1;
}

void	ft_putsprite(t_param *param)
{
	float	distanceprojection;
	float	sprite_size;
	int		id;
	float	transformy;

	id = 0;
	ft_spritedistance(param);
	ft_sortsprite(param);
	while (id < param->sprite.nb_sprite)
	{
		distanceprojection = (param->win_width / 2) / tan(FOV / 2);
		sprite_size = (param->tile_s * 0.5 /
			param->sprite.distance[id]) * distanceprojection;
		ft_zero(param);
		if (ft_spritevisible(param, id, sprite_size) == 1)
		{
			transformy = ft_gettransformy(param, id, sprite_size);
			ft_getstart(param, sprite_size);
			ft_drawsprite(param, transformy, sprite_size);
		}
		id++;
	}
}
