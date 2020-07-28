/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 15:48:05 by user42            #+#    #+#             */
/*   Updated: 2020/07/28 15:48:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	ft_floor(t_param *param)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < param->win_height / 2)
	{
		while (j < param->win_width)
		{
			param->img.data[(i + param->win_height / 2) *
			param->win_width + (j + 0)] = param->f_color;
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_ceiling(t_param *param)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < param->win_height / 2)
	{
		while (j < param->win_width)
		{
			param->img.data[(i + 0) * param->win_width + (j + 0)] =
			param->c_color;
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_draw_floor_ceiling(t_param *param)
{
	ft_floor(param);
	ft_ceiling(param);
}
