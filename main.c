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

static void	ft_key(t_param *param, int key, int n)
{
	if (key == KEY_LEFT)
	{
		param->player.walkdirection = -n;
		param->player.translation = n;
	}
	if (key == KEY_RIGHT)
	{
		param->player.walkdirection = n;
		param->player.translation = n;
	}
	if (key == KEY_UP)
	{
		param->player.walkdirection = n;
		param->player.translation = 0 * n;
	}
	if (key == KEY_DOWN)
	{
		param->player.walkdirection = -n;
		param->player.translation = 0 * n;
	}
}

int			key_press(int key, void *data)
{
	t_param *param;

	param = (t_param *)data;
	if (key == CAM_RIGHT)
		param->player.turndirection = +1;
	if (key == CAM_LEFT)
		param->player.turndirection = -1;
	ft_key(param, key, 1);
	if (key == 53)
		exit_properly(param);
	return (1);
}

int			key_release(int key, void *data)
{
	t_param *param;

	param = (t_param *)data;
	if (key == CAM_RIGHT)
		param->player.turndirection = 0;
	if (key == CAM_LEFT)
		param->player.turndirection = 0;
	ft_key(param, key, 0);
	return (1);
}

int			game_loop(t_param *param)
{
	param->img.img_ptr = mlx_new_image(param->mlx_ptr,
		param->win_width, param->win_height);
	param->img.data = (int *)mlx_get_data_addr(param->img.img_ptr,
		&param->img.bpp, &param->img.size_l, &param->img.endian);
	ft_updateplayer(param);
	ft_castallrays(param);
	ft_putsprite(param);
	ft_rendermap(param);
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

int			main(int ac, char **av)
{
	t_param		param;
//	int			width;
//	int			height;

	ft_parsing(av[1], &param);
	param.argument = ac;
	param.mlx_ptr = mlx_init();
	param.win_ptr = mlx_new_window(param.mlx_ptr,
		param.win_width, param.win_height, "Cub3D");
	ft_initplayer(&param);
//	mlx_get_screen_size(&param.mlx_ptr, &width, &height);
//	ft_initwin_size(&param, width, height);
	ft_inittexture(&param);
	ft_initsprite(&param);
	ft_initdir(&param);
	ft_initplan(&param);
	mlx_hook(param.win_ptr, 17, 0, &exit_properly, &param);
	mlx_hook(param.win_ptr, 2, 0, &key_press, &param);
	mlx_hook(param.win_ptr, 3, 0, &key_release, &param);
	mlx_loop_hook(param.mlx_ptr, &game_loop, &param);
	system("leaks cub3D");
	mlx_loop(param.mlx_ptr);
	return (1);
}
