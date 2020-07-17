/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:34:32 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/06/29 18:58:38 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	ft_countsprite(t_param *param)
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

void	ft_spritetxt(t_param *param)
{
	param->sprite.ptr = mlx_xpm_file_to_image(param->mlx_ptr,
		param->sprite.path,
			&param->sprite.width, &param->sprite.height);
	param->sprite.data = (int *)mlx_get_data_addr(param->sprite.ptr,
			&param->sprite.bpp, &param->sprite.size_l, &param->sprite.endian);
}

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

int	ft_spritevisible(t_param *param, int id, float sprite_size)
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

void	ft_sortsprite(t_param *param)
{
	float	temp_dist;
	float	temp_y;
	float	temp_x;
	int		j;
	int		i;

	i = -1;
	while (i++ < param->sprite.nb_sprite)
	{
		j = i + 1;
		while (j++ < param->sprite.nb_sprite)
		{
			if (param->sprite.distance[j] > param->sprite.distance[i])
			{
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
		}
	}
}

void	ft_putsprite(t_param *param)
{
	int		textureoffsetx;
	int		distancefromtop;
	int		textureoffsety;
	float	distanceprojection;
	int		x;
	float	sprite_size;
	int		y;
	int		id;
	float	spritex;
	float	spritey;
	float	invdet;
	float	transformx;
	float	transformy;
	int		spritescreenx;
	int		spriteheight;
	int		drawstarty;
	int		drawendy;
	int		spritewidth;
	int		drawstartx;
	int		drawendx;
	int		color;

	id = 0;
	ft_spritedistance(param);
	ft_sortsprite(param);
	while (id < param->sprite.nb_sprite)
	{
		distanceprojection = (param->win_width / 2) / tan(FOV / 2);
		sprite_size = (param->tile_s * 0.5 /
			param->sprite.distance[id]) * distanceprojection;
		if (ft_spritevisible(param, id, sprite_size) == 1)
		{
			spritex = param->sprite.x[id] - param->player.x;
			spritey = param->sprite.y[id] - param->player.y;
			invdet = 1.0 / (param->player.planx * param->player.diry
				- param->player.dirx * param->player.plany);
			transformx = invdet * (param->player.diry * spritex
				- param->player.dirx * spritey);
			transformy = invdet * (-param->player.plany * spritex
				+ param->player.planx * spritey);
			spritescreenx = (int)((param->win_width / 2) *
				(1 + -transformx / transformy));

			spriteheight = sprite_size;
			drawstarty = -spriteheight / 2 + param->win_height / 2;
			if (drawstarty < 0)
				drawstarty = 0;
			drawendy = spriteheight / 2 + param->win_height / 2;
			if (drawendy >= param->win_height)
				drawendy = param->win_height - 1;

			spritewidth = sprite_size;
			drawstartx = -spritewidth / 2 + spritescreenx;
			if (drawstartx < 0)
				drawstartx = 0;
			drawendx = spritewidth / 2 + spritescreenx;
			if (drawendx >= param->win_width)
				drawendx = param->win_width - 1;

			x = drawstartx;
			while (x < drawendx)
			{
				if (transformy > 0 && x > 0 && x < param->win_width
					&& transformy < param->sprite.buffer[x])
				{
					y = drawstarty;
					while (y < drawendy)
					{
						textureoffsetx = (int)(256 * (x - (-sprite_size /
							2 + spritescreenx)) * param->sprite.width
							/ sprite_size) / 256;
						distancefromtop = (y) * 256 - param->win_height *
							128 + sprite_size * 128;
						textureoffsety = ((distancefromtop *
							param->sprite.height) / sprite_size) / 256;
						color = param->sprite.data[(textureoffsety *
							param->sprite.width) + textureoffsetx];
						param->img.data[y * param->win_width + x] = color;
						y++;
					}
				}
				x++;
			}
		}
		id++;
	}
}