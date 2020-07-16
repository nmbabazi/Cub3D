
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

int	ft_verifline(char *line)
{
	int i;
	i = 0;
	if (!(line[i] == '.'))
		return (0);
	i++;
	if (!(line[i] == '/'))
		return (0);
	i++;
	if (!(line[i] || ((line[i] >= 'a' && line[i] <= 'z') || line[i] == '_')))
		return (0);
	while(line[i] && ((line[i] >= 'a' && line[i] <= 'z') || line[i] == '_'))
		i++;
	while (line[i] != '\0')
	{
		if (line[i] == '/')
		{
			i++;
			if (!(line[i] || ((line[i] >= 'a' && line[i] <= 'z') || line[i] == '_')))
				return (0);
			while(line[i] && ((line[i] >= 'a' && line[i] <= 'z') || line[i] == '_'))
				i++;
		}
		if (line[i] == '.')
			break;
		i++;
	}
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
	return (1);
	
}

char	*ft_strdup(char *src)
{
	int		i;
	int		len;
	char	*p;

	i = 0;
	len = ft_strlen(src);
	if (!(p = calloc((len + 1), sizeof(char))))
		return (NULL);
	while(src[i])
	{
		p[i] = src[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	p = malloc(count * size);
	if (p == NULL)
		return (0);
	ft_bzero(p, count * size);
	return (p);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)s;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}

int	ft_lstsize(t_list *lst)
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

int	ft_definedirection(char *line)
{
	int i = 0;
	int n = 22;
	if (line[i] == 'N' && line [i + 1] == 'O')
		n = NO;
	if (line[i] == 'S' && line [i + 1] == 'O')
		n = SO;
	if (line[i] == 'W' && line [i + 1] == 'E')
		n = WE;
	if (line[i] == 'E' && line [i + 1] == 'A')
		n = EA;
	if (line[i] == 'S' && line [i + 1] == 32)
		n = S;
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

int	ft_getlen(t_list *maps)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (maps)
	{
		while (maps->str[i])
			i++;
		if (i > len)
			len = i;
		maps = maps->next;
	}
	return (len);
}

t_list	*add_link(t_list *maps, char *line)
{
	t_list	*tmp;
	char *swp;

	if (!(tmp = (t_list *)malloc(sizeof(t_list) * 1)))
		return (NULL);
	if (tmp)
	{
		tmp->str = ft_strdup(line);
		tmp->next = maps;
	}
	return (tmp);
}

int		*ft_createtab(int *tab)
{
	int i;

	i = 0;
	if (!(tab = malloc(sizeof(int) * 3)))
		return (NULL);
	while (i < 3)
		tab[i++] = 0;
	return (tab);
}