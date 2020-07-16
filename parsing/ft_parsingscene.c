
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
# include "../include.h"
#include "parsing.h"

void	ft_fillcolor(char *line, t_param *param, int *temp)
{
	int n;

	n = 0;
	if (*line == 'F')
		param->f_color = (((temp[n]) << 16) + ((temp[n + 1]) << 8) + (temp[n + 2]));
	if (*line == 'C')
		param->c_color = (((temp[n]) << 16) + ((temp[n + 1]) << 8) + (temp[n + 2]));
	return ;
}

int 	ft_color(char *line, t_param *param)
{
	int i = 1;
	int n = 0;
	int *temp;

	temp = NULL;
	temp = ft_createtab(temp);
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
		if (line[i] == ',')
		{
			if (temp[n] < 0 || temp[n] > 255)
			{
				free(temp);
				return (0);
			}
			i++;
			n++;
		}
	}
	ft_fillcolor(line, param, temp);
	free(temp);
	return (1);	
}

int 	ft_resolution(char *line, t_param *param)
{
	int i;
	int n;

	i = 1;
	n = 0;
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

int	ft_texture(char *line, t_param *param)
{
	int i;
	int n;

	n = ft_definedirection(line);
	i = 1;
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
	int i = 0;
/*	printf("HEIGHT =%d     WIDTH =%d\n", param->win_height, param->win_width);
	printf("TXT_NO =%s    TXT_SO =%s    TXT_WE =%s   TXT_EA =%s\n", param->texture[NO].path, param->texture[SO].path, param->texture[WE].path, param->texture[EA].path);
	printf("TXT_SPRITE =%s\n", param->sprite.path);
	printf("cieling =%x      flour =%x\n", param->c_color, param->f_color);
*/	while (i < param->map_rows)
	{
		printf("%s\n", param->map[i]);
		i++;
	}
	return ;
}

void	ft_fillrows(char *src, t_param *param, int len, int i)
{
	int l;
	l = 0;
	while (src[l])
	{
		param->map[i][l] = src[l];
		l++;
	}
	if (l < len)
	{
		while (l < len)
		{
			param->map[i][l] = '1';
			l++;
		}
	}
	param->map[i][l] = '\0';
}


void	ft_creatmap(t_list *maps, t_param *param)
{
	int i = 0;
	int j = 0;

	param->map_rows = ft_lstsize(maps);
	param->map_cols = ft_getlen(maps);
	if(!(param->map = (char **)malloc(sizeof(char *) * param->map_rows + 1)))
		return ;
	while (i < param->map_rows)
	{
		if(!(param->map[i] = malloc(sizeof(char) * param->map_cols + 1)))
			return ;
		i++;
	}
	while (--i >= 0 && maps)
	{
		ft_fillrows(maps->str, param, param->map_cols, i);
		maps = maps->next;
	}	
}

/*void	ft_freemap(t_param *param)
{
	int l = 0;
	while (l < param->map_rows)
	{
		free(param->map[l]);
		l++;
	}
	free(param->map);
}*/

int	ft_parsingscene(int fd, t_param *param)
{
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
			if (!(ft_resolution(line, param) == 1))
			{
				free(line);
				return (2);
			}
			free(line);
		}
		if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
		{
			if (!(ft_texture(line, param) == 1))
			{
			free(line);
				return (3);
			}
			free(line);
		}
		if (*line == 'C' || *line == 'F')
		{
			if (!(ft_color(line, param) == 1))
			{
				free(line);
				return (4);
			}
			free(line);
		}
		if (*line == '1' || *line == ' ')
			break;
	}
	if (!r)
	{
		free(line);
		return (0);
	}
	maps = add_link(maps, line);
	free(line);
	while ((r = get_next_line(&line, fd)) > 0)
	{
		if (!(*line == '1' || *line == ' '))
		{
			free(line);
			ft_lstclear(&maps, &ft_freestr);
			return (5);
		}
		maps = add_link(maps, line);
		free(line);
	}
	if (!(*line == '1' || *line == ' ') || *line == '\0')
	{
		free(line);
		ft_lstclear(&maps, &ft_freestr);
		return (6);
	}
	if (*line == '1' || *line == ' ')
		maps = add_link(maps, line);
	free(line);
	ft_creatmap(maps, param);
	ft_printparsing(param);
	ft_lstclear(&maps, &ft_freestr);
	param->tile_s = param->win_width / param->map_cols;
	param->num_rays = param->win_width;
//	ft_freemap(param);
//	free(line);
	return (1);
}

void	ft_parsing(char *fichier, t_param *param)
{
	int fd; 

	fd = open(fichier, O_RDONLY);
	printf("retour %d\n", ft_parsingscene(fd, param));
/*	if (ft_parsingscene(fd, param) == 0)
		ft_putstr_fd("ERROR PARSING\n", 1);*/
	return ;
}
