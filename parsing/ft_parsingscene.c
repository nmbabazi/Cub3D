
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 17:42:00 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/02/03 10:16:11 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include <stdio.h>


typedef struct	s_pars
{
	int	*rez;
	int	color[2][3];
	char	*textur[5];
}
			t_pars;

typedef	struct	s_list
{
	char		*str;
	struct s_list	*next;
}
			t_list;			


t_list	*add_link(t_list *maps, char *line)
{
	t_list	*tmp;
	if (!(tmp = malloc(sizeof(t_list))))
		return (NULL);
	if (tmp)
	{
		tmp->str = line;
		tmp->next = maps;
	}
	return (tmp);
}

int 	ft_color(char *line, t_pars *scn)
{
	int i = 1;
	int n = 0;
	int l = 0;

	if (*line == 'F')
		l = 0;
	if (*line == 'C')
		l = 1;
	while(line[i])
	{
		while(line [i] == 32)
			i++;
		if (!(line[i] >= '0' && line[i] <= '9'))
			return (0);
		while ((line[i] >= '0' && line[i] <= '9') && line[i] != ',' && line[i])
		{
			scn->color[l][n] = (scn->color[l][n] * 10) + (line[i] - 48);
			i++;
		}
		if (line[i] == ',')
		{
			i++;
			n++;
		}
	}
	return (1);	
}

int 	ft_resolution(char *line, t_pars *scn)
{
	int i = 1;
	int n = 0;
	scn->rez = calloc(2, sizeof(int));
	while(line[i])
	{
		while(line[i] == 32)
			i++;
		if (!(line[i] >= '0' && line[i] <= '9'))
			return (0);
		while ((line[i] >= '0' && line[i] <= '9') && line[i] != 32 && line[i])
		{
			scn->rez[n] = (scn->rez[n] * 10) + (line[i] - 48);
			i++;
		}
		if (line[i] == 32)
		{
			i++;
			n++;
		}
	}
	return (1);	
}

int	ft_definedirection(char *line)
{
	int i = 0;
	int n = 22;
	if (line[i] == 'N' && line [i + 1] == 'O')
		n = 0;
	if (line[i] == 'S' && line [i + 1] == 'O')
		n = 1;
	if (line[i] == 'W' && line [i + 1] == 'E')
		n = 2;
	if (line[i] == 'E' && line [i + 1] == 'A')
		n = 3;
	if (line[i] == 'S' && line [i + 1] == 32)
		n = 4;
	return (n);
}

int	ft_textur(char *line, t_pars *scn)
{
	int i = 1;
	int n;

	n = ft_definedirection(line);
	if (n == 22)
		return (0);
	if(line[i] == 'O' || line[i] == 'E' || line[i] == 'A')
		i++;
	while(line[i] == 32)
		i++;
	if (line[i] != '.')
		return (0);
	if (!(ft_verifline(&line[i]) == 1))
		return (0);
	scn->textur[n] = ft_strdup(&line[i]);
	return (1);
}


void	ft_printstruct(t_pars *scn, t_list *maps)
{

	printf("R--%d--%d \n", scn->rez[0], scn->rez[1]);
	printf("--%s\n", scn->textur[0]);
	printf("--%s\n", scn->textur[1]);
	printf("--%s\n", scn->textur[2]);
	printf("--%s\n", scn->textur[3]);
	printf("--%s\n", scn->textur[4]);
	printf("F--%d--%d--%d \n", scn->color[0][0], scn->color[0][1], scn->color[0][2]);
	printf("N--%d--%d--%d \n", scn->color[1][0], scn->color[1][1], scn->color[1][2]);
	while (maps)
	{
		printf("MAPS--%s--\n", maps->str);
		maps = maps->next;
	}	
}


int	ft_parsingscene(int fd)
{
	t_pars	scn;
	t_list	*maps;
	int r;
	char *line;
	
	r = 0;
	line = NULL;
	maps = NULL;
	while ((r = get_next_line(&line, fd)) > 0)
	{
		if (*line == 'R')
		{
			if (!(ft_resolution(line, &scn) == 1))
				return (0) ;
		}
		if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
		{
			if (!(ft_textur(line, &scn) == 1))
				return (0);
		}
		if (*line == 'C' || *line == 'F')
		{
			if (!(ft_color(line, &scn) == 1))
				return (0) ;
		}
		if (*line == '1' || *line == ' ')
			break;
	}
	if (!r)
		return (0);
	maps = add_link(maps, line);
	while ((r = get_next_line(&line, fd)) > 0)
	{
		if (!(*line == '1' || *line == ' '))
			return (0);
		maps = add_link(maps, line);
	}
	ft_printstruct(&scn, maps);
	return (1);
}

int main(int ac, char **av)
{
	int fd; 

	fd = open(av[1], O_RDONLY);
	printf("fd = %d\n", fd);
	if (ft_parsingscene(fd) == 0)
		printf("ERROR\n");
	return (0);
	
}
