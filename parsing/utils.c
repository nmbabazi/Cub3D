
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

#include "include.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	int i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			ft_putchar(s[i]);
			i++;
		}
	}
}

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
