/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 11:35:39 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/06/22 13:49:54 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

const char	map[MAP_ROWS][MAP_COLS] = {
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
	int i;
	int l;
	int col;

	i = 0;
	l = 0;
	col = 0x000000;
	while (l < MAP_ROWS)
	{
		i = 0;
		while (i < MAP_COLS)
		{
			if (map[l][i] == '1')
				col = 0xFFFFFF;
			else if (map[l][i] != '1')
				col = 0x000000;
			ft_rectangle(i * TILE_S * MINIMAP, l * TILE_S * MINIMAP,
					TILE_S * MINIMAP, col, param);
			i++;
		}
		l++;
	}
}

int		key_press(int key, void *data)
{
	t_param *param;

	param = (t_param *)data;
	if (key == 124)
		param->player.turndirection = +1;
	if (key == 123)
		param->player.turndirection = -1;
	if (key == 126)
		param->player.walkdirection = 1;
	if (key == 125)
		param->player.walkdirection = -1;
	if (key == 53)
		exit(0);
	return (1);
}

int		key_release(int key, void *data)
{
	t_param *param;

	param = (t_param *)data;
	if (key == 124)
		param->player.turndirection = 0;
	if (key == 123)
		param->player.turndirection = 0;
	if (key == 126)
		param->player.walkdirection = 0;
	if (key == 125)
		param->player.walkdirection = 0;
	return (1);
}

int		ft_iswall(float x, float y)
{
	int indexx;
	int indexy;

	if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
		return (1);
	indexx = floor(x / TILE_S);
	indexy = floor(y / TILE_S);
	if (map[indexy][indexx] == '1')
		return (1);
	return (0);
}

int		game_loop(t_param *param)
{
	param->img.img_ptr = mlx_new_image(param->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	param->img.data = (int *)mlx_get_data_addr(param->img.img_ptr,
			&param->img.bpp, &param->img.size_l, &param->img.endian);
	ft_updateplayer(param);
//	ft_rendermap(map, param);
	ft_castallrays(param);
	ft_rendermap(map, param);
	ft_renderplayer(param);
	mlx_clear_window(param->mlx_ptr, param->win_ptr);
	mlx_put_image_to_window(param->mlx_ptr, param->win_ptr, param->img.img_ptr,
			0, 0);
	mlx_destroy_image(param->mlx_ptr, param->img.img_ptr);
	return (1);
}

int		main()
{
	t_param		param;
	t_player	player;

	param.mlx_ptr = mlx_init();
	param.win_ptr = mlx_new_window(param.mlx_ptr, WIN_WIDTH,
			WIN_HEIGHT, "fuck yeah");
	ft_initplayer(map, &param);
	ft_inittexture(&param);
	mlx_hook(param.win_ptr, 2, 0, &key_press, &param);
	mlx_hook(param.win_ptr, 3, 0, &key_release, &param);
	mlx_loop_hook(param.mlx_ptr, &game_loop, &param);
//	system("leaks cub3D");
	mlx_loop(param.mlx_ptr);
	return (1);
}
