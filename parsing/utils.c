/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:50:54 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/24 15:24:46 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		ft_isxpm(char *line)
{
	int i;

	i = 0;
	if (line[i] == '.')
	{
		i++;
		if (line[i] != 'x')
			return (0);
		i++;
		if (line[i] != 'p')
			return (0);
		i++;
		if (line[i] != 'm')
			return (0);
		i++;
	}
	if (line[i] != '\0')
		return (0);
	return (i);
}

int		ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

void	ft_freestr(char *str)
{
	free(str);
}

void	ft_lstclear(t_list **lst, void (*del)(char *))
{
	t_list	*current;
	t_list	*previous;

	if (lst)
	{
		current = *lst;
		while (current)
		{
			previous = current;
			current = current->next;
			(*del)(previous->str);
			free(previous);
			previous = 0;
		}
	}
	*lst = 0;
}

int		ft_getlen(t_list *maps)
{
	int len;
	int check;

	len = 0;
	check = 0;
	while (maps)
	{
		check = ft_strlen(maps->str);
		if (check >= len)
			len = check;
		maps = maps->next;
	}
	return (len);
}

t_list	*add_link(t_list *maps, char *line)
{
	t_list	*tmp;
	char	*swp;

	if (!(tmp = (t_list *)malloc(sizeof(t_list) * 1)))
	{
		free(line);
		return (NULL);
	}
	if (tmp)
	{
		tmp->str = ft_strdup(line);
		tmp->next = maps;
	}
	free(line);
	return (tmp);
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

int		ft_open(char *path)
{
	return (open(path, O_RDONLY));
}

int		ft_checktab(int *tab, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		printf("TAB de %d = %d\n", i, tab[i]);
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
