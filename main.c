/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 11:35:39 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/06/29 18:35:28 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	ft_rendermap(t_param *param)
{
	int i;
	int l;
	int col;

	i = 0;
	l = 0;
	col = 0x000000;
	while (l < param->map_rows)
	{
		i = 0;
		while (i < param->map_cols)
		{
			if (param->map[l][i] == '1')
				col = 0xFFFFFF;
			else if (param->map[l][i] != '1')
				col = 0x000000;
			ft_rectangle(i * param->tile_s  * MINIMAP, l * param->tile_s * MINIMAP,
					param->tile_s * MINIMAP, col, param);
			i++;
		}
		l++;
	}
}

int		key_press(int key, void *data)
{
	t_param *param;

	param = (t_param *)data;
	if (key == CAM_RIGHT)
	{
		param->player.turndirection = +1;
		param->player.lodev = -1;
	}
	if (key == CAM_LEFT)
	{
		param->player.turndirection = -1;
		param->player.lodev = +1;
	}
		if (key == KEY_LEFT)
	{
		param->player.walkdirection = -1;
		param->player.velocity = -1;
	}
	if (key == KEY_RIGHT)
	{
		param->player.walkdirection = 1;
		param->player.velocity = +1;
	}
	if (key == KEY_UP)
	{
		param->player.walkdirection = 1;
		param->player.velocity = 0;
	}
	if (key == KEY_DOWN)
	{
		param->player.walkdirection = -1;
		param->player.velocity = 0;
	}
	if (key == 53)
		exit(0);
	return (1);
}

int		key_release(int key, void *data)
{
	t_param *param;

	param = (t_param *)data;
	if (key == CAM_RIGHT)
	{
		param->player.turndirection = 0;
		param->player.lodev = 0;
	}
	if (key == CAM_LEFT)
	{
		param->player.turndirection = 0;
		param->player.lodev = 0;
	}
	if (key == KEY_LEFT)
	{
		param->player.walkdirection = 0;
		param->player.velocity = 0;
	}
	if (key == KEY_RIGHT)
	{
		param->player.walkdirection = 0;
		param->player.velocity = 0;
	}
	if (key == KEY_UP)
	{
		param->player.walkdirection = 0;
		param->player.velocity = 0;
	}
	if (key == KEY_DOWN)
	{
		param->player.walkdirection = 0;
		param->player.velocity = 0;
	}
	return (1);
}

int		exit_properly(void *data)
{
	t_param *param;

	param = (t_param *)data;
	exit(0);
	return (1);
}

int		ft_iswall(float x, float y, t_param *param)
{
	int indexx;
	int indexy;

	if (x < 0 || x > param->map_cols * param->tile_s || y < 0 || y > param->map_rows * param->tile_s)
		return (1);
	indexx = floor(x / param->tile_s);
	indexy = floor(y / param->tile_s);
	if (param->map[indexy][indexx] == '1')
		return (1);
	return (0);
}

void	ft_initvecteur(t_param *param)
{
	float angledown = 0.5 * M_PI;
	float angleeast = 0;
	float anglewest = M_PI;
	float angleup = 1.5 * M_PI;
	if (param->player.rotationangle == angleeast)
	{
		param->dirx = 1;
		param->diry = 0;
		param->planx = 0;
		param->plany = -0.6;
	}
	if (param->player.rotationangle == angledown)
	{
		param->dirx = 0;
		param->diry = 1;
		param->planx = 0.6;
		param->plany = 0;
	}
	if (param->player.rotationangle == anglewest)
	{
		param->dirx = -1;
		param->diry = 0;
		param->planx = 0;
		param->plany = 0.6;
	}
	if (param->player.rotationangle == angleup)
	{
		param->dirx = 0;
		param->diry = -1;
		param->planx = -0.6;
		param->plany = 0;
	}
}

int		game_loop(t_param *param)
{
	param->img.img_ptr = mlx_new_image(param->mlx_ptr, param->win_width, param->win_height);
	param->img.data = (int *)mlx_get_data_addr(param->img.img_ptr,
			&param->img.bpp, &param->img.size_l, &param->img.endian);
	ft_updateplayer(param);
	ft_castallrays(param);
	ft_rendermap(param);
	ft_putsprite(param);
	ft_renderplayer(param);
	mlx_clear_window(param->mlx_ptr, param->win_ptr);
	if (param->argument == 3)
	{
		ft_save(param, "save.bmp");
		exit_properly(param);
	}
	mlx_put_image_to_window(param->mlx_ptr, param->win_ptr, param->img.img_ptr,
			0, 0);
	mlx_destroy_image(param->mlx_ptr, param->img.img_ptr);
	return (1);
}

int	main(int ac, char **av)
{
	t_param		param;

	ft_parsing(av[1], &param);
	param.argument = ac;
	param.mlx_ptr = mlx_init();
	param.win_ptr = mlx_new_window(param.mlx_ptr, param.win_width, param.win_height, "Cub3D");
	ft_initplayer(&param);
	ft_inittexture(&param);
	ft_initsprite(&param);
	ft_initvecteur(&param);
	mlx_hook(param.win_ptr, 17, 0, &exit_properly, &param);
	mlx_hook(param.win_ptr, 2, 0, &key_press, &param);
	mlx_hook(param.win_ptr, 3, 0, &key_release, &param);
	mlx_loop_hook(param.mlx_ptr, &game_loop, &param);
//	system("leaks cub3D");
	mlx_loop(param.mlx_ptr);
	return (1);
}
