
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

#include "../include.h"
#include "parsing.h"
#include <stdio.h>

/*t_list	*add_link(t_list *maps, char *line)
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
}*/

int 	ft_color(char *line, t_param *param)
{
	int i = 1;
	int n = 0;
	int *temp;

	if (!(temp = (int *)malloc(sizeof(int) * 3)))
		return (0);
	while (temp[n])
	{
		temp[n] = 0;
		n++;
	}
	n = 0;
	while(line[i])
	{
		while(line [i] == 32)
			i++;
		if (!(line[i] >= '0' && line[i] <= '9'))
			return (0);
		while ((line[i] >= '0' && line[i] <= '9') && line[i] != ',' && line[i])
		{
			temp[n] = (temp[n] * 10) + (line[i] - 48);
			i++;
		}
		printf("TEMP %d\n", temp[n]);
		if (line[i] == ',')
		{
			if (temp[n] < 0 || temp[n] > 255)
				return (0);
			i++;
			n++;
		}
	}
	n = 0;
	if (*line == 'F')
		param->f_color = (((temp[n]) << 16) + ((temp[n + 1]) << 8) + (temp[n + 2]));
	if (*line == 'C')
		param->c_color = (((temp[n]) << 16) + ((temp[n + 1]) << 8) + (temp[n + 2]));
	free(temp);
	return (1);	
}

int 	ft_resolution(char *line, t_param *param)
{
	int i = 1;
	int n = 0;
	while(line[i])
	{
		while(line[i] == 32)
			i++;
		if (!(line[i] >= '0' && line[i] <= '9'))
			return (0);
		while ((line[i] >= '0' && line[i] <= '9') && line[i] != 32 && line[i])
		{
			if (n == 0)
				param->win_width = (param->win_width * 10) + (line[i] - 48);
			if (n == 1)
				param->win_height = (param->win_height * 10) + (line[i] - 48);
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

int	ft_texture(char *line, t_param *param)
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
	if (n == S)
		param->sprite.path = ft_strdup(&line[i]);
	else 
		param->texture[n].path = ft_strdup(&line[i]);
	return (1);
}

void	ft_printparsing(t_param *param)
{
	printf("HEIGHT =%d     WIDTH =%d\n", param->win_height, param->win_width);
	printf("TXT_NO =%s    TXT_SO =%s    TXT_WE =%s   TXT_EA =%s\n", param->texture[NO].path, param->texture[SO].path, param->texture[WE].path, param->texture[EA].path);
	printf("TXT_SPRITE =%s\n", param->sprite.path);
	printf("cieling =%x      flour =%x\n", param->c_color, param->f_color);
	return;
}

int	ft_parsingscene(int fd, t_param *param)
{
//	t_list	*maps;
	int r;
	char *line;
	
	r = 0;
	line = NULL;
//	maps = NULL;
	while ((r = get_next_line(&line, fd)) > 0)
	{
		if (*line == 'R')
		{
			if (!(ft_resolution(line, param) == 1))
				return (0) ;
		}
		if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
		{
			if (!(ft_texture(line, param) == 1))
				return (0);
		}
		if (*line == 'C' || *line == 'F')
		{
			if (!(ft_color(line, param) == 1))
				return (0) ;
		}
		if (*line == '1' || *line == ' ')
			break;
	}
	if (!r)
		return (0);
/*	maps = add_link(maps, line);
	while ((r = get_next_line(&line, fd)) > 0)
	{
		if (!(*line == '1' || *line == ' '))
			return (0);
		maps = add_link(maps, line);
	}
	ft_creatmap(&maps)*/
	ft_printparsing(param);
	return (1);
}

void	ft_parsing(char *fichier, t_param *param)
{
	int fd; 

	fd = open(fichier, O_RDONLY);
	if (ft_parsingscene(fd, param) == 0)
		ft_putstr_fd("ERROR PARSING\n", 1);
	return ;
}
