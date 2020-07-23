/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsingscene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nailambz <nailambz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 17:42:00 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/21 19:24:35 by nailambz         ###   ########.fr       */
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
	{
		free(temp);
		return (-1);
	}
	*i = l;
	return (nb);
}

int		*ft_fillrgb(char *line, int *temp, int *m, int n)
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
			return (0);
		if (line[i] == ',')
		{
			i++;
			n++;
		}
	}
	*m = n;
	return (temp);
}

int		ft_color(char *line, t_param *param, int *tab)
{
	int n;
	int *temp;

	n = 0;
	temp = NULL;
	temp = ft_createtab(temp, 3);
	ft_filltab(line, tab);
	if ((temp = ft_fillrgb(line, temp, &n, n)) == 0)
	{
		free(line);
		free(temp);
		return (4);
	}
	if (n != 2)
	{
		free(line);
		free(temp);
		return (4);
	}
	ft_fillcolor(line, param, temp);
	free(line);
	free(temp);
	return (1);
}

int		ft_fillrez(t_param *param, int i, char *line, int n)
{
	while ((line[i] >= '0' && line[i] <= '9') && line[i] != 32 && line[i])
	{
		if (n > 1)
		{
			free(line);
			return (0);
		}
		if (n == 0)
			param->win_width = (param->win_width * 10) + (line[i] - 48);
		if (n == 1)
			param->win_height = (param->win_height * 10) + (line[i] - 48);
		i++;
	}
	return (i);
}

int		ft_resolution(char *line, t_param *param, int *tab)
{
	int i;
	int n;

	i = 1;
	n = 0;
	ft_filltab(line, tab);
	while (line[i])
	{
		while (line[i] == 32)
			i++;
		if (!(line[i] >= '0' && line[i] <= '9') && n >= 2)
		{
			free(line);
			return (2);
		}
		if ((i = ft_fillrez(param, i, line, n)) == 0)
			return (2);
		if (line[i] == 32)
		{
			i++;
			n++;
		}
	}
	free(line);
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
			ft_putstr_fd("CAN'T OPEN TEXTURE\n", 1);
			return (0);
		}
	}
	if (n < 4)
	{
		param->texture[n].path = ft_strdup(&line[i]);
		if (ft_open(param->texture[n].path) == -1)
		{
			ft_putstr_fd("CAN'T OPEN TEXTURE\n", 1);
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

void	ft_printparsing(t_param *param)
{
	int i;

	i = 0;
	printf("HEIGHT =%d     WIDTH =%d\n", param->win_height, param->win_width);
	printf("TXT_NO =%s    TXT_SO =%s    TXT_WE =%s   TXT_EA =%s\n",
		param->texture[NO].path, param->texture[SO].path,
		param->texture[WE].path, param->texture[EA].path);
	printf("TXT_SPRITE =%s\n", param->sprite.path);
	printf("cieling =%x      flour =%x\n", param->c_color, param->f_color);
	while (i < param->map_rows)
	{
		printf("%s--%zu--%d\n", param->map[i], ft_strlen(param->map[i]), i);
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
			param->map[i][l] = ' ';
			l++;
		}
	}
	param->map[i][l] = '\0';
}

int		ft_checksurrounding(char c, int i, int j, char **map)
{
	if (map[i][j + 1] == ' '
		|| map[i][j - 1] == ' ' || map[i + 1][j] == ' '
		|| map[i - 1][j] == ' ')
	{
		ft_putstr_fd("Error format map. Map not surrounded by wall.....\n", 1);
		return (0);
	}
	return (1);
}

int		ft_checkcorner(t_param *param, int i, int j, char **map)
{
	if (((i == 0 || j == 0) && (map[i][j] == '0'
		|| map[i][j] == '2' || map[i][j] == 'N' || map[i][j] == 'S'
		|| map[i][j] == 'W' || map[i][j] == 'E')))
		return (0);
	if (((i == param->map_rows - 1 || j == param->map_cols - 1) &&
		(map[i][j] == '0' || map[i][j] == '2' || map[i][j] == 'N'
		|| map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')))
		return (0);
	return (1);
}

int		ft_checkmap(char **map, t_param *param)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '2' && map[i][j] != 'N'
				&& map[i][j] != 'S' && map[i][j] != 'W' && map[i][j] != 'E'
				&& map[i][j] != '1' && map[i][j] != ' ')
				return (0);
			if (ft_checkcorner(param, i, j, map) == 0)
				return (0);
			else if ((map[i][j] != '1' && map[i][j] != ' ')
				&& ft_checksurrounding(map[i][j], i, j, map) == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int		ft_oneplayer(char **map, t_param *param)
{
	int i;
	int j;
	int n;

	i = 0;
	j = 0;
	n = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
				n++;
			if (n > 1)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_fillgap(t_param *param)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < param->map_rows)
	{
		j = 0;
		while (j < param->map_cols)
		{
			if (param->map[i][j] == ' ')
				param->map[i][j] = '1';
			j++;
		}
		i++;
	}
}

int		ft_creatmap(t_list *maps, t_param *param)
{
	int i;

	i = 0;
	param->map_rows = ft_lstsize(maps);
	param->map_cols = ft_getlen(maps);
	if (!(param->map = (char **)malloc(sizeof(char *) * param->map_rows + 1)))
		return (0);
	while (i < param->map_rows)
	{
		if (!(param->map[i] = malloc(sizeof(char) * param->map_cols + 1)))
			return (0);
		i++;
	}
	while (--i >= 0 && maps)
	{
		ft_fillrows(maps->str, param, param->map_cols, i);
		maps = maps->next;
	}
	if (ft_checkmap(param->map, param) == 0)
		return (0);
	if (ft_oneplayer(param->map, param) == 0)
		return (0);
	ft_fillgap(param);
	return (1);
}

int		ft_pars(t_param *param, char *line, int *tab)
{
	if (*line == '1' || *line == ' ')
		return (-2);
	if (*line == 'R')
		return (ft_resolution(line, param, tab));
	if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
	{
		ft_filltab(line, tab);
		if (ft_checkdoublon(tab, line) == 0)
			return (3);
		return (ft_texture(line, param, tab));
	}
	if (*line == 'C' || *line == 'F')
		return (ft_color(line, param, tab));
	if (*line == '\0' || *line == '\n')
	{
		free(line);
		return (1);
	}
	ft_putstr_fd("WRONG CHARACTER IN SCENE\n", 1);
	free(line);
	return (0);
}

int		ft_checklastline(char *line, t_list *maps)
{
	if (!(*line == '1' || *line == ' ') || *line == '\0')
	{
		free(line);
		ft_lstclear(&maps, &ft_freestr);
		return (0);
	}
	return (1);
}

int		ft_buildmap(t_param *param, char *line, int *r, int fd)
{
	int		ret;
	t_list	*maps;

	ret = 0;
	maps = NULL;
	maps = add_link(maps, line);
	while ((*r = get_next_line(&line, fd)) > 0)
	{
		if (ft_checklastline(line, maps) != 1)
			return (5);
		maps = add_link(maps, line);
	}
	if (ft_checklastline(line, maps) != 1)
		return (5);
	maps = add_link(maps, line);
	if (ft_creatmap(maps, param) != 1)
	{
		ft_lstclear(&maps, &ft_freestr);
		return (5);
	}
	param->tile_s = param->win_width / param->map_cols;
	param->num_rays = param->win_width;
	ft_lstclear(&maps, &ft_freestr);
	return (1);
}

int		ft_suiteparsing(t_param *param, char *line, int *r, int fd)
{
	int ret;

	ret = 0;
	if (*r == 0)
	{
		free(line);
		return (5);
	}
	if ((ret = ft_buildmap(param, line, r, fd)) != 1)
		return (ret);
	printf("OK\n");
	return (1);
}

int		ft_parsingscene(int fd, t_param *param, char *line)
{
	int		r;
	int		*tab;
	int		ret;

	r = 0;
	tab = ft_createtab(tab, 8);
	while ((r = get_next_line(&line, fd)) > 0)
	{
		ret = ft_pars(param, line, tab);
		if (ret == -2)
			break ;
		if (ret != 1)
		{
			free(tab);
			return (ret);
		}
	}
	if ((ret = ft_suiteparsing(param, line, &r, fd)) != 1)
	{
		free(tab);
		return (ret);
	}
	if (ft_checktab(tab, 8) == 0)
		return (6);
	return (ret);
}

void	ft_errormessage(int ret, char *line)
{
	if (ret == 2)
		ft_putstr_fd("ERROR: resolution\n", 1);
	else if (ret == 3)
		ft_putstr_fd("ERROR: texture\n", 1);
	else if (ret == 4)
		ft_putstr_fd("ERROR: colors\n", 1);
	else if (ret == 5)
		ft_putstr_fd("ERROR: map\n", 1);
	else if (ret == 6)
		ft_putstr_fd("WRONG NUMBER OF ELENMENT IN SCENE\n", 1);
}

int		ft_parsing(char *fichier, t_param *param)
{
	int		fd;
	int		ret;
	char	*line;

	ret = 0;
	line = NULL;
	fd = open(fichier, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("CAN'T OPEN SCENE\n", 1);
		return (0);
	}
	ret = ft_parsingscene(fd, param, line);
	if (ret != 1)
		ft_errormessage(ret, line);
	close(fd);
	return (ret);
}
