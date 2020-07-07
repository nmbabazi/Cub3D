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

void    ft_initsprite(const char map[MAP_ROWS][MAP_COLS], t_param *param)
{
    int i;
	int l;

	i = 0;
	l = 0;
	int		size_sprite = 15;
	while (l < MAP_ROWS)
	{
		i = 0;
		while (i < MAP_COLS)
		{
			if (map[l][i] == '2')
			{
				param->sprite.x = i * TILE_S + TILE_S / 2;
				param->sprite.y = l * TILE_S + TILE_S / 2;
				break ;
			}
			i++;
		}
		l++;
	}
	param->sprite.distance = 0;
	param->sprite.angle = 0;
	param->sprite.isvisible = 0;
	param->sprite.ptr = 0;
	param->sprite.data = 0;
	param->sprite.bpp = 0;
	param->sprite.endian = 0;
	param->sprite.size_l = 0;
	param->sprite.width = 0;
	param->sprite.height = 0;
/*	ft_rectangle((param->sprite.x - size_sprite / 2) * MINIMAP, (param->sprite.y - size_sprite / 2) * MINIMAP, size_sprite * MINIMAP, 0x008000, param);
	param->sprite.distance = ft_distance(param->player.x, param->player.y,
			param->sprite.x, param->sprite.y);*/
	ft_spritetxt(param);
}

void	ft_spritetxt(t_param *param)
{
	param->sprite.ptr = mlx_xpm_file_to_image(param->mlx_ptr, "plante.xpm",
			&param->sprite.width, &param->sprite.height);
	param->sprite.data = (int *)mlx_get_data_addr(param->sprite.ptr,
			&param->sprite.bpp, &param->sprite.size_l, &param->sprite.endian);

}


float	ft_angle(t_param *param)
{
	float	vectX;
	float	vectY;
	float	playertospriteangle;
	float 	spriteangle;
	float playerangle;

	vectX = param->sprite.x - param->player.x;
	vectY = param->sprite.y - param->player.y;
	playertospriteangle  = atan2(vectY, vectX);
	playerangle = ft_normalizeangle(param->player.rotationangle);
	spriteangle = playerangle - playertospriteangle;
			
	if (spriteangle < -3.14159)
			spriteangle += 2.0 * 3.14159;
	if (spriteangle > 3.14159)
			spriteangle -= 2.0 * 3.14159;
	spriteangle = fabs(spriteangle);
	if(spriteangle < FOV / 2)
		param->sprite.isvisible = 1;
	else
		param->sprite.isvisible = 0;
	return (spriteangle);
}

/*void	ft_drawsprite(float y_start, float y_end, float sprite_size, t_param *param, int id)
{
		static int i = 0;
		int l;
		int		textureoffsetx;
		int		distancefromtop;
		int		textureoffsety;
		int		color;
	//	int x1;
	//	float hauteur = fabs(y_start - y_end) / param->sprite.height;
	if (i < sprite_size)
	{
		if (param->sprite.distance < param->ray[id].colldistance)
			{
				l = y_start;
				while (l < y_end)
				{
		//	x1 = (int)(x_start + ((i-1) * hauteur)+l);
					distancefromtop = l + (sprite_size / 2) - (WIN_HEIGHT / 2);
					textureoffsetx = (int)(i * param->sprite.width / sprite_size);
					textureoffsety = distancefromtop * ((float)param->sprite.height / sprite_size);
					color = param->sprite.data[(textureoffsety * param->sprite.width) + textureoffsetx];
					param->img.data[l * WIN_WIDTH + i] = color;
					l++;
				}
			}
	}
	i++;
	return ;
}

void	ft_putsprite(t_param *param)
{
	float	distanceprojection;
	float	sprite_size;
	float	spritetop;
	float	spritebottom;
	int 	i = 0;
	float	x0;
	float	x;
	int x1;
	param->sprite.angle = ft_angle(param);
	param->sprite.distance = ft_distance(param->player.x, param->player.y, param->sprite.x, param->sprite.y);

	if (param->sprite.isvisible == 1)
	{
		distanceprojection = (WIN_WIDTH / 2) / tan(FOV / 2);
		sprite_size = (TILE_S * 0.5 / param->sprite.distance) * distanceprojection;
		spritetop = (WIN_HEIGHT / 2) - (sprite_size / 2);
		spritetop = spritetop < 0 ? 0 : spritetop;
		spritebottom = spritetop + sprite_size;
		spritebottom = spritebottom > WIN_HEIGHT ? WIN_HEIGHT : spritebottom;
		x0 = tan(param->sprite.angle) * 500;
		x = (WIN_WIDTH / 2 + x0 - sprite_size / 2);
		float hauteur = fabs(spritetop - spritebottom) / param->sprite.height;
		x1 = (int)(x + ((i-1) * hauteur)+ 1);
	//	ft_drawsprite(spritetop, spritebottom, sprite_size, param, id);
	//	printf("ok\n");
		while (i < NUM_RAYS)
		{
		//	printf("Yes\n");
			if (param->ray[i].wallhitx == x1)
			{
				printf("Yah\n");
				ft_rectangle(i, spritetop, 20, 0xf7ff3c, param);
			}
			i++;
		}
	}
}*/

void	ft_putsprite(t_param *param)
{
	int		textureoffsetx;
	int		distancefromtop;
	int		textureoffsety;
	float distanceprojection;
	int sprite;
	float sprite_size;
	int y;
	int id = 0;
	param->sprite.angle = ft_angle(param);
	param->sprite.distance = ft_distance(param->player.x, param->player.y, param->sprite.x, param->sprite.y);
		distanceprojection = (WIN_WIDTH / 2) / tan(FOV / 2);
		sprite_size = (TILE_S * 0.5 / param->sprite.distance) * distanceprojection;

	if (param->sprite.isvisible == 1)
	{
		float spriteX = param->sprite.x - param->player.x;
		float spriteY = param->sprite.y - param->player.y;
		float invDet = 1.0 / (param->planx * param->diry - param->dirx * param->plany);
		float transformX = invDet * (param->diry * spriteX - param->dirx * spriteY);
     	float transformY = invDet * (-param->plany * spriteX + param->planx * spriteY);
		int spriteScreenX = (int)((WIN_WIDTH / 2) * (1 + -transformX / transformY));

		int spriteHeight = sprite_size;
      	int drawStartY = -spriteHeight / 2 + WIN_HEIGHT / 2;
    	if(drawStartY < 0) drawStartY = 0;
    	int drawEndY = spriteHeight / 2 + WIN_HEIGHT / 2;
    	if(drawEndY >= WIN_HEIGHT) drawEndY = WIN_HEIGHT - 1;

		int spriteWidth = sprite_size;
      	int drawStartX = -spriteWidth / 2 + spriteScreenX;
     	if(drawStartX < 0) drawStartX = 0;
      	int drawEndX = spriteWidth / 2 + spriteScreenX;
     	if(drawEndX >= WIN_WIDTH) drawEndX = WIN_WIDTH - 1;
		
		sprite = drawStartX;
		while (sprite < drawEndX)
		{
			if(transformY > 0 && drawStartX > 0 && drawStartX < WIN_WIDTH)
			{
				y = drawStartY;
				while (y < drawEndY)
				{
					textureoffsetx = (int)(256 * (sprite - (-sprite_size / 2 + spriteScreenX)) * param->sprite.width / sprite_size) / 256;
					distancefromtop = (y) * 256 - WIN_HEIGHT * 128 + sprite_size * 128;
					textureoffsety = ((distancefromtop * param->sprite.height) / sprite_size) / 256;
					int color = param->sprite.data[(textureoffsety * param->sprite.width) + textureoffsetx];
					param->img.data[y * WIN_WIDTH + sprite] = color;
					y++;
				}
			}
			sprite++;
		}
	}
}