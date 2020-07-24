/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parstexture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 15:12:03 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/24 15:24:33 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		ft_definedirection(char *line)
{
	int i;
	int n;

	i = 0;
	n = 22;
	if (line[i] == 'N' && line[i + 1] == 'O')
		n = NO;
	if (line[i] == 'S' && line[i + 1] == 'O')
		n = SO;
	if (line[i] == 'W' && line[i + 1] == 'E')
		n = WE;
	if (line[i] == 'E' && line[i + 1] == 'A')
		n = EA;
	if (line[i] == 'S' && line[i + 1] == 32)
		n = S;
	else if (line[i] == 'S' && line[i + 1] != 'O' && line[i + 1] != 32)
		free(line);
	return (n);
}

int		ft_checkname(char *line, int i)
{
	while (line[i] != '\0')
	{
		if (line[i] == '/')
		{
			i++;
			if (ft_isalnum(line[i]) != 1 && line[i] != '_')
				return (0);
			while (line[i] && (ft_isalnum(line[i]) == 1 || line[i] == '_'))
				i++;
			if (line[i] != '/' && line[i] != '.')
				return (0);
		}
		if (line[i] == '.')
			break ;
		i++;
	}
	return (i);
}

int		ft_veriftxt(char *line)
{
	int i;

	i = 0;
	if (!(line[i] == '.'))
		return (0);
	i++;
	if (!(line[i] == '/'))
		return (0);
	i++;
	if (!(ft_isalnum(line[i]) == 1 || line[i] == '_'))
		return (0);
	while (line[i] && (ft_isalnum(line[i]) == 1 || line[i] == '_'))
		i++;
	if (line[i] != '/' && line[i] != '.')
		return (0);
	if ((i = ft_checkname(line, i)) == 0)
		return (0);
	if ((i = ft_isxpm(&line[i])) == 0)
		return (0);
	return (1);
}

int		ft_wichtexture(t_param *param, char *line, int i)
{
	int n;

	n = ft_definedirection(line);
	if (n == 22)
		return (0);
	if (n == S)
	{
		param->sprite.path = ft_strdup(&line[i]);
		if (ft_open(param->sprite.path) == -1)
		{
			ft_putstr_fd("ERROR:\n CAN'T OPEN TEXTURE\n", 1);
			return (0);
		}
	}
	if (n < 4)
	{
		param->texture[n].path = ft_strdup(&line[i]);
		if (ft_open(param->texture[n].path) == -1)
		{
			ft_putstr_fd("ERROR:\n CAN'T OPEN TEXTURE\n", 1);
			return (0);
		}
	}
	return (1);
}

int		ft_texture(char *line, t_param *param, int *tab)
{
	int i;

	i = 1;
	if (line[i] == 'O' || line[i] == 'E' || line[i] == 'A')
		i++;
	while (line[i] == 32)
		i++;
	if (line[i] != '.')
	{
		free(line);
		return (3);
	}
	if (!(ft_veriftxt(&line[i]) == 1))
	{
		free(line);
		return (3);
	}
	if (ft_wichtexture(param, line, i) != 1)
	{
		free(line);
		return (3);
	}
	free(line);
	return (1);
}
