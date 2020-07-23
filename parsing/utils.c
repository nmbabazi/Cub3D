/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:50:54 by nmbabazi          #+#    #+#             */
/*   Updated: 2019/11/15 11:32:25 by nmbabazi         ###   ########.fr       */
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

/*int ft_checkdoublon(int *tab, char *line)
{
	if (tab[3] == 2 || tab[4] == 2 || tab[5] == 2 || tab[6] == 2 || tab[7] == 2 )
	{
		ft_putstr_fd("ERROR DOUBLON\n", 1);
		ft_freeall(line, tab);
		return (0);
	}
	else
		return (1);
}
	if (ft_checkdoublon(tab, line) == 0)
		return (3)*/