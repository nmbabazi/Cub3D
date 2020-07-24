/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 16:16:08 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/24 16:47:41 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		ft_checktab(int *tab, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (tab[i] != 1)
		{
			free(tab);
			return (0);
		}
		i++;
	}
	free(tab);
	return (1);
}

void	ft_filltab(char *line, int *tab)
{
	int i;

	i = 0;
	if (line[i] == 'R')
		tab[0]++;
	if (line[i] == 'C')
		tab[1]++;
	if (line[i] == 'F')
		tab[2]++;
	if (line[i] == 'N')
		tab[3]++;
	if (line[i] == 'S' && line[i + 1] == 'O')
		tab[4]++;
	if (line[i] == 'E')
		tab[5]++;
	if (line[i] == 'W')
		tab[6]++;
	if (line[i] == 'S' && line[i + 1] == ' ')
		tab[7]++;
}

int		*ft_createtab(int *tab, int len)
{
	int i;

	i = 0;
	if (!(tab = malloc(sizeof(int) * len)))
		return (NULL);
	while (i < len)
		tab[i++] = 0;
	return (tab);
}

int		ft_checkdoublon(int *tab, char *line)
{
	if (tab[3] == 2 || tab[4] == 2 || tab[5] == 2
		|| tab[6] == 2 || tab[7] == 2)
	{
		ft_putstr_fd("DOUBLON TEXTURE\n", 1);
		free(line);
		return (0);
	}
	else
		return (1);
}

void	ft_freeall(char *line, int *tab)
{
	free(line);
	free(tab);
}
