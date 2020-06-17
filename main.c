/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 11:35:39 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/06/17 11:33:43 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include.h"

const char map[MAP_ROWS][MAP_COLS] = {
    "11111111111111111111",
    "10000000000000010001",
    "10000000000000010001",
    "10000000000000010001",
    "10000000000000000001",
    "10000000000000000001",
    "10000000003000000001",
    "10000000000000000001",
    "10000011100000000001",
    "10000000000000010001",
    "10100000000000010001",
    "11000000000000010001",
    "11111111111111111111",
};

void	ft_rendermap(const char map[13][20], t_param *param)
{
	int i = 0;
	int l = 0;
	int col = 0x000000;
	
	while (l < MAP_ROWS)
	{
		i = 0;
		while(i < MAP_COLS)
		{	
			if (map[l][i] == '1')
				col = 0xFFFFFF;
			else if (map[l][i] != '1')
				col = 0x000000;	
			ft_rectangle(i * TILE_S * MINIMAP, l * TILE_S * MINIMAP, TILE_S * MINIMAP,  TILE_S * MINIMAP, col, param);
			i++;
		}
		l++;
	}
}

int	key_press(int key, void *data)
{
	t_param *param;

	param = (t_param *)data;
	if (key == 124)
		param->player.turnDirection = +1;
	if (key == 123)
		param->player.turnDirection = -1;
	if (key == 126)
		param->player.walkDirection = 1;
	if (key == 125)
		param->player.walkDirection = -1;
	if (key == 53)
		exit(0);
	return (1);
}

int	key_release(int key, void *data)
{
	t_param *param;

	param = (t_param *)data;
	if (key == 124)
		param->player.turnDirection = 0;
	if (key == 123)
		param->player.turnDirection = 0;
	if (key == 126)
		param->player.walkDirection = 0;
	if (key == 125)
		param->player.walkDirection = 0;
	return (1);
}


int	ft_isWall(float x, float y)
{
	int indexX;
	int indexY;
	
	if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
		return (1);
	indexX = floor(x / TILE_S);
	indexY = floor(y / TILE_S);
	if (map[indexY][indexX] == '1')
		return(1);
	return (0);

}

void	ft_renderWall(t_param *param, float angle, int i)
{
	float	distanceProjection;
	float	distanceRay;
	float wallHeight;
	float correctDistance;

	distanceRay = param->ray.collDistance;
	correctDistance = distanceRay * cos(angle - param->player.rotationAngle);
	distanceProjection = (WIN_WIDTH / 2) / tan(FOV / 2);
	wallHeight = (TILE_S / correctDistance) * distanceProjection;
	ft_rectangle(i * COLS_S, (WIN_HEIGHT / 2) - (wallHeight / 2), wallHeight, COLS_S, 0xFFFFFF, param);

}

int	game_loop(t_param *param)
{
	param->img.img_ptr = mlx_new_image(param->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	param->img.data = (int *)mlx_get_data_addr(param->img.img_ptr, 
			&param->img.bpp, &param->img.size_l, &param->img.endian);
	ft_updateplayer(param);
	ft_rendermap(map, param);
	ft_castallrays(param);
	ft_renderplayer(param);
	mlx_put_image_to_window(param->mlx_ptr, param->win_ptr, param->img.img_ptr, 
			0, 0);
	mlx_destroy_image(param->mlx_ptr, param->img.img_ptr);
	return (1);
}

int main()
{
	t_param param;
	t_player player;

	param.mlx_ptr = mlx_init();
	param.win_ptr = mlx_new_window(param.mlx_ptr, WIN_WIDTH, 
			WIN_HEIGHT, "fuck yeah");
	ft_initplayer(map, &param);
	mlx_hook(param.win_ptr, 2, 0, &key_press, &param);
	mlx_hook(param.win_ptr, 3, 0, &key_release, &param);
	mlx_loop_hook(param.mlx_ptr, &game_loop, &param);
	mlx_loop(param.mlx_ptr);
}
