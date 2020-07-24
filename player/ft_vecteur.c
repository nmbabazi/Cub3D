/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecteur.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:02:53 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/24 14:06:12 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

void			ft_initplan(t_param *param)
{
	if (param->player.c == 'E')
	{
		param->player.planx = 0;
		param->player.plany = -0.6;
	}
	if (param->player.c == 'S')
	{
		param->player.planx = 0.6;
		param->player.plany = 0;
	}
	if (param->player.c == 'W')
	{
		param->player.planx = 0;
		param->player.plany = 0.6;
	}
	if (param->player.c == 'N')
	{
		param->player.planx = -0.6;
		param->player.plany = 0;
	}
}

void			ft_initdir(t_param *param)
{
	if (param->player.c == 'E')
	{
		param->player.dirx = 1;
		param->player.diry = 0;
	}
	if (param->player.c == 'S')
	{
		param->player.dirx = 0;
		param->player.diry = 1;
	}
	if (param->player.c == 'W')
	{
		param->player.dirx = -1;
		param->player.diry = 0;
	}
	if (param->player.c == 'N')
	{
		param->player.dirx = 0;
		param->player.diry = -1;
	}
}

void			ft_updatevect(t_param *param)
{
	float olddirx;
	float oldplanx;
	float vectangle;

	olddirx = param->player.dirx;
	oldplanx = param->player.planx;
	vectangle = param->player.turndirection * param->player.turnspeed;
	param->player.dirx = param->player.dirx * cos(vectangle)
		- param->player.diry * sin(vectangle);
	param->player.diry = olddirx * sin(vectangle) +
		param->player.diry * cos(vectangle);
	param->player.planx = param->player.planx * cos(vectangle)
		- param->player.plany * sin(vectangle);
	param->player.plany = oldplanx * sin(vectangle) +
		param->player.plany * cos(vectangle);
}
