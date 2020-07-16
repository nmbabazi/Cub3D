/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 11:27:50 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/06/29 18:24:24 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

float	ft_distance(float x, float y, float xend, float yend)
{
	return (sqrt((xend - x) * (xend - x) + (yend - y) * (yend - y)));
}

void	ft_drawline(int x_start, int y_start, float distance, float angle,
		t_param *param)
{
	float	i;
	int		x;
	int		y;
	int		longeur;

	longeur = 0;
	i = 0;
	x = 0;
	y = 0;
	while (i < distance)
	{
		param->img.data[(y_start + y) * param->win_width + (x_start + x)] = 0xffff00;
		x = cos(angle) * longeur;
		y = sin(angle) * longeur;
		longeur++;
		i++;
	}
}

void	ft_rectangle(int x, int y, int size, int col, t_param *param)
{
	int count_y;
	int count_x;
	int x_start;
	int col_start;

	count_y = 0;
	count_x = 0;
	x_start = x;
	col_start = col;
	while (count_y < size)
	{
		count_x = 0;
		x = x_start;
		while (count_x < size)
		{
			param->img.data[y * param->win_width + x] = col;
			count_x++;
			x++;
		}
		count_y++;
		y++;
	}
	return ;
}

float	ft_normalizeangle(float angle)
{
	angle = remainder(angle, M_PI * 2);
	if (angle < 0)
		angle = (M_PI * 2) + angle;
	return (angle);
}

void	ft_raydirection(t_param *param, float angle, int id)
{
	if (angle > 0 && angle < M_PI)
		param->ray.raydown = 1;
	else
		param->ray.raydown = -1;
	if (angle < (M_PI * 0.5) || angle > (M_PI * 1.5))
		param->ray.rayright = 1;
	else
		param->ray.rayright = -1;
}

void	ft_putchar_fd(char c, int fd)
{
	if (fd)
		write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	}
}