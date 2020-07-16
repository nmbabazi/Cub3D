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

void    ft_initsprite(t_param *param)
{
    int i;
	int l;
	int id;

	i = 0;
	l = 0;
	id = 0;
	param->sprite.nb_sprite = ft_countsprite(param);
	if (!(param->sprite.x = malloc(sizeof(float) * param->sprite.nb_sprite)))
		return ;
	if (!(param->sprite.y = malloc(sizeof(float) * param->sprite.nb_sprite)))
		return ;
	if (!(param->sprite.distance = (float *)malloc(sizeof(float) * param->sprite.nb_sprite)))
		return ;
	if (!(param->sprite.buffer = malloc(sizeof(float) * param->win_width)))
		return ;
	while (l < param->map_rows && id < param->sprite.nb_sprite)
	{
		i = 0;
		while (i < param->map_cols)
		{
			if (param->map[l][i] == '2')
			{
				param->sprite.x[id] = i * param->tile_s + param->tile_s / 2;
				param->sprite.y[id] = l * param->tile_s + param->tile_s / 2;
				param->sprite.distance[id] = 0;
	//			printf("X = %f             Y = %f\n", param->sprite.x[id], param->sprite.y[id]);
				id++;
			}
			i++;
		}
		l++;
	}
	param->sprite.angle = 0;
	param->sprite.ptr = 0;
	param->sprite.data = 0;
	param->sprite.bpp = 0;
	param->sprite.endian = 0;
	param->sprite.size_l = 0;
	param->sprite.width = 0;
	param->sprite.height = 0;
	ft_spritetxt(param);
}

void	ft_spritetxt(t_param *param)
{
	param->sprite.ptr = mlx_xpm_file_to_image(param->mlx_ptr, param->sprite.path,
			&param->sprite.width, &param->sprite.height);
	param->sprite.data = (int *)mlx_get_data_addr(param->sprite.ptr,
			&param->sprite.bpp, &param->sprite.size_l, &param->sprite.endian);

}


int	ft_spritevisible(t_param *param, int id, float sprite_size)
{
	float	vectX;
	float	vectY;
	float	vectX_end;
	float	vectY_end;
	float	playertospriteangle;
	float	playertospriteangle_end;
	float 	spriteangle;
	float 	spriteangle_end;
	float	playerangle;

	vectX = param->sprite.x[id] - param->player.x;
	vectY = param->sprite.y[id] - param->player.y;
	vectX_end = (param->sprite.x[id] + sprite_size) - param->player.x;
	vectY_end = (param->sprite.y[id] + sprite_size) - param->player.y;
	playertospriteangle  = atan2(vectY, vectX);
	playertospriteangle_end  = atan2(vectY_end, vectX_end);
	playerangle = ft_normalizeangle(param->player.rotationangle);
	spriteangle = playerangle - playertospriteangle;
	spriteangle_end = playerangle - playertospriteangle_end;
			
	if (spriteangle < -3.14159)
			spriteangle += 2.0 * 3.14159;
	if (spriteangle > 3.14159)
			spriteangle -= 2.0 * 3.14159;
	if (spriteangle_end < -3.14159)
			spriteangle_end += 2.0 * 3.14159;
	if (spriteangle_end > 3.14159)
			spriteangle_end -= 2.0 * 3.14159;
	spriteangle = fabs(spriteangle);
	spriteangle_end = fabs(spriteangle_end);
	float wallspriteangle = fabs(spriteangle_end - spriteangle);
	float fovSprite = FOV / 2 + wallspriteangle;
	if(spriteangle < fovSprite)
		return (1);
	else
		return (0);
}

void	ft_spritedistance(t_param *param)
{
	int id;
	
	id = 0;
    while(id < param->sprite.nb_sprite)
    {
		param->sprite.distance[id] = ft_distance(param->player.x, param->player.y, param->sprite.x[id], param->sprite.y[id]);
		id++;
    }
}

void ft_sortsprite(t_param *param)
{
	int i;
	float temp_dist;
	float temp_y;
	float temp_x;
	int j;

	i = 0;
	while(i < param->sprite.nb_sprite)
	{
		j = i + 1;
		while(j < param->sprite.nb_sprite)
		{
			if(param->sprite.distance[j] > param->sprite.distance[i])
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
			j++;
		}
		i++;
	}
}

void	ft_putsprite(t_param *param)
{
	int		textureoffsetx;
	int		distancefromtop;
	int		textureoffsety;
	float distanceprojection;
	int stripe;
	float sprite_size;
	int y;
	int id = 0;
	ft_spritedistance(param);
	ft_sortsprite(param);

	while (id < param->sprite.nb_sprite)
	{
		distanceprojection = (param->win_width / 2) / tan(FOV / 2);
		sprite_size = (param->tile_s * 0.5 / param->sprite.distance[id]) * distanceprojection;
	//	printf("SIZE = %f\n", sprite_size);
		if (ft_spritevisible(param, id, sprite_size) == 1)
		{
			float spriteX = param->sprite.x[id] - param->player.x;
			float spriteY = param->sprite.y[id] - param->player.y;
			float invDet = 1.0 / (param->planx * param->diry - param->dirx * param->plany);
			float transformX = invDet * (param->diry * spriteX - param->dirx * spriteY);
			float transformY = invDet * (-param->plany * spriteX + param->planx * spriteY);
			int spriteScreenX = (int)((param->win_width / 2) * (1 + -transformX / transformY));

			int spriteHeight = sprite_size;
			int drawStartY = -spriteHeight / 2 + param->win_height / 2;
			if(drawStartY < 0) drawStartY = 0;
			int drawEndY = spriteHeight / 2 + param->win_height / 2;
			if(drawEndY >= param->win_height) drawEndY = param->win_height - 1;

			int spriteWidth = sprite_size;
			int drawStartX = -spriteWidth / 2 + spriteScreenX;
			if(drawStartX < 0) drawStartX = 0;
			int drawEndX = spriteWidth / 2 + spriteScreenX;
			if(drawEndX >= param->win_width) drawEndX = param->win_width - 1;

			stripe = drawStartX;
			while (stripe < drawEndX)
			{
			//	printf("transformY = %f      stripe = %d         len = %f\n", transformY,  stripe, param->sprite.buffer[stripe]);
				if(transformY > 0 && stripe > 0 && stripe < param->win_width && transformY < param->sprite.buffer[stripe])
				{
				//	printf("START = %d   END = %d\n", drawStartY, drawEndY);
					y = drawStartY;
					while (y < drawEndY)
					{
						textureoffsetx = (int)(256 * (stripe - (-sprite_size / 2 + spriteScreenX)) * param->sprite.width / sprite_size) / 256;
						distancefromtop = (y) * 256 - param->win_height * 128 + sprite_size * 128;
						textureoffsety = ((distancefromtop * param->sprite.height) / sprite_size) / 256;
						int color = param->sprite.data[(textureoffsety * param->sprite.width) + textureoffsetx];
					//	int color = 0xFFFFFF;
						param->img.data[y * param->win_width + stripe] = color;
						y++;
					}
				}
				stripe++;
			}
		}
		id++;
	}
//	free(param->sprite.buffer);
}