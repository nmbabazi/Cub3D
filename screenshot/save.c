/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:38:57 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/24 16:37:49 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

void	ft_fillheader(t_file_header *file_header,
			t_info_header *info_header, t_param *param)
{
	file_header->type[0] = 0x42;
	file_header->type[1] = 0x4D;
	file_header->size = (param->win_height * param->win_width * 4) + 54;
	file_header->reserved = 0x00000000;
	file_header->offset = 0x36;
	info_header->size = 40;
	info_header->width = param->win_width;
	info_header->height = -param->win_height;
	info_header->planes = 1;
	info_header->bpp = 32;
	info_header->compression = 0;
	info_header->img_size = (param->win_width * param->win_height * 4);
	info_header->x_ppm = param->win_width;
	info_header->y_ppm = param->win_height;
	info_header->total_color = 0;
	info_header->important_color = 0;
}

void	ft_writebmp(t_file_header *file_header,
			t_info_header *info_header, int fd)
{
	write(fd, &file_header->type, 2);
	write(fd, &file_header->size, 4);
	write(fd, &file_header->reserved, 4);
	write(fd, &file_header->offset, 4);
	write(fd, &info_header->size, 4);
	write(fd, &info_header->width, 4);
	write(fd, &info_header->height, 4);
	write(fd, &info_header->planes, 2);
	write(fd, &info_header->bpp, 2);
	write(fd, &info_header->compression, 4);
	write(fd, &info_header->img_size, 4);
	write(fd, &info_header->x_ppm, 4);
	write(fd, &info_header->y_ppm, 4);
	write(fd, &info_header->total_color, 4);
	write(fd, &info_header->important_color, 4);
}

void	ft_writecolor(int fd, t_param *param)
{
	char	*pixel_array;
	int		image_size;
	int		i;
	int		j;

	image_size = param->win_width * param->win_height;
	if (!(pixel_array = malloc(sizeof(char) * param->img.size_l)))
	{
		ft_putstr_fd("pbm de malloc", 1);
		return ;
	}
	i = 0;
	j = 0;
	while (i < image_size)
	{
		pixel_array[j++] = param->img.data[i] & 255;
		pixel_array[j++] = (param->img.data[i] & 255 << 8) >> 8;
		pixel_array[j++] = (param->img.data[i] & 255 << 16) >> 16;
		pixel_array[j++] = 0;
		i++;
	}
	write(fd, pixel_array, param->img.size_l * param->win_height);
	free(pixel_array);
}

void	ft_save(t_param *param, char *name)
{
	int				fd;
	t_file_header	file_header;
	t_info_header	info_header;

	if (!((fd = open(name, O_WRONLY | O_CREAT
			| O_TRUNC, S_IRUSR | S_IWUSR)) > 0))
	{
		ft_putstr_fd("ERREUR OUVERTURE DE BMP", 1);
		return ;
	}
	ft_fillheader(&file_header, &info_header, param);
	ft_writebmp(&file_header, &info_header, fd);
	ft_writecolor(fd, param);
	close(fd);
}
