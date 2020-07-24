/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parscolor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 15:07:03 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/24 16:46:58 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_fillcolor(char *line, t_param *param, int *temp)
{
	int n;

	n = 0;
	if (*line == 'F')
		param->f_color = (((temp[n]) << 16) +
		((temp[n + 1]) << 8) + (temp[n + 2]));
	if (*line == 'C')
		param->c_color = (((temp[n]) << 16) +
		((temp[n + 1]) << 8) + (temp[n + 2]));
	return ;
}

int		ft_convertint(char *line, int *i, int *temp)
{
	int l;
	int nb;

	l = *i;
	nb = 0;
	while (ft_isdigit(line[l]) == 1 && line[l])
	{
		nb = (nb * 10) + (line[l] - 48);
		l++;
	}
	if (nb < 0 || nb > 255)
		return (-1);
	*i = l;
	return (nb);
}

int		ft_fillrgb(char *line, int *temp, int *m, int n)
{
	int i;

	i = 1;
	while (line[i])
	{
		while (line[i] == 32)
			i++;
		if (ft_isdigit(line[i]) == 0)
			return (0);
		if ((temp[n] = ft_convertint(line, &i, temp)) < 0)
			return (0);
		while (line[i] == 32 && n < 2)
			i++;
		if (line[i] != '\0' && line[i] != ',')
		{
			return (0);
		}
		if (line[i] == ',')
		{
			i++;
			n++;
		}
	}
	*m = n;
	return (1);
}

int		ft_color(char *line, t_param *param, int *tab)
{
	int n;
	int *temp;

	n = 0;
	temp = NULL;
	temp = ft_createtab(temp, 3);
	ft_filltab(line, tab);
	if (ft_fillrgb(line, temp, &n, n) == 0)
	{
		ft_freeall(line, temp);
		return (4);
	}
	if (n != 2)
	{
		ft_freeall(line, temp);
		return (4);
	}
	ft_fillcolor(line, param, temp);
	ft_freeall(line, temp);
	return (1);
}
