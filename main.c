/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 11:35:39 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/28 15:53:18 by user42           ###   ########.fr       */
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
	if (key == 65307)
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
	ft_draw_floor_ceiling(param);
	ft_updateplayer(param);
	ft_castallrays(param);
	ft_putsprite(param);
	mlx_clear_window(param->mlx_ptr, param->win_ptr);
	mlx_put_image_to_window(param->mlx_ptr, param->win_ptr, param->img.img_ptr,
			0, 0);
	if (param->argument == 3)
	{
		ft_save(param, "save.bmp");
		exit_properly(param);
	}
	mlx_destroy_image(param->mlx_ptr, param->img.img_ptr);
	return (1);
}

int			main(int ac, char **av)
{
	t_param		param;

	ft_initeverything(&param);
	if (ft_checkarg(ac, av) == 0)
		return (0);
	if ((ft_parsing(av[1], &param) != 1))
	{
		ft_freepath(&param);
		ft_freemap(&param);
		return (0);
	}
	param.argument = ac;
	param.mlx_ptr = mlx_init();
	ft_screen_size(&param);
	param.win_ptr = mlx_new_window(param.mlx_ptr,
		param.win_width, param.win_height, "Cub3D");
	ft_initall(&param);
	mlx_hook(param.win_ptr, 17, 1L << 17, &exit_properly, &param);
	mlx_hook(param.win_ptr, KeyPress, KeyPressMask, &key_press, &param);
	mlx_hook(param.win_ptr, KeyRelease, KeyReleaseMask, &key_release, &param);
	mlx_loop_hook(param.mlx_ptr, &game_loop, &param);
	mlx_loop(param.mlx_ptr);
	return (1);
}
