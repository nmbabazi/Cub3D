/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 17:42:00 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/06/29 15:25:41 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include "./minilibx_opengl_20191021/mlx.h"
# include "parsing/parsing.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <math.h>
# include <fcntl.h>
# include <pthread.h>


# define NO 0
# define SO 1
# define EA 2
# define WE 3
# define S 4
# define CAM_LEFT 123
# define CAM_RIGHT 124
# define KEY_LEFT 0
# define KEY_RIGHT 2
# define KEY_UP 13
# define KEY_DOWN 1
# define VERT 1
# define HORZ 0
# define TILE_S 50
# define MINIMAP 0.2
# define MAP_ROWS 13
# define MAP_COLS 20
# define WIN_WIDTH (MAP_COLS * TILE_S)
# define WIN_HEIGHT (MAP_ROWS * TILE_S)
# define FOV 60 * (M_PI / 180)
# define COLS_S 1
# define NUM_RAYS (WIN_WIDTH / COLS_S)
# define NUM_SPRITE 6

typedef struct	s_player
{
	float	x;
	float	y;
	int		turndirection;
	int		walkdirection;
	float	rotationangle;
	float	walkspeed;
	float	turnspeed;
	int		lodev;
	int 	velocity;
	int		facingvert;	
}				t_player;

typedef struct	s_img
{
	void	*img_ptr;
	int		*data;
	int		bpp;
	int		endian;
	int		size_l;
}				t_image;

typedef struct	s_ray
{
	float	rayangle;
	float	wallhitx;
	float	wallhity;
	float	colldistance;
	int		raydown;
	int		rayright;
	int		washitvert;
	int		wallheight;
	float	horzhity;
	float	horzhitx;
	float	verthity;
	float	verthitx;

}				t_ray[NUM_RAYS];

typedef	struct	s_texture
{
	void	*ptr;
	int		*data;
	int		bpp;
	int		endian;
	int		size_l;
	int		width;
	int		height;
	char	*path;
}				t_texture[4];

typedef struct	s_sprite
{
	float	x[NUM_SPRITE];
	float	y[NUM_SPRITE];
	float	distance[NUM_SPRITE];
	int		order[NUM_SPRITE];
	float	angle;
	int		isvisible[NUM_SPRITE];
	void	*ptr;
	int		*data;
	int		bpp;
	int		endian;
	int		size_l;
	int		width;
	int		height;
	char	*path;
	char	**map;
	float	buffer[NUM_RAYS];
}				t_sprite;

typedef	struct	s_list
{
	char		*str;
	struct s_map	*next;
}				t_list;		

typedef struct	s_param
{
	void		*mlx_ptr;
	void		*win_ptr;
	float		diry;
	float		dirx;
	float		plany;
	float		planx;
	int			win_width;
	int			win_height;
	int			f_color;
	int			c_color;
	t_image		img;
	t_player	player;
	t_ray		ray;
	t_texture	texture;
	t_sprite	sprite;
	int			argument;
}				t_param;

typedef	struct	s_file_header
{
	char			type[2];
	unsigned int	size;
	unsigned int	reserved;
	unsigned int	offset;
}				t_file_header;

typedef struct		s_info_header
{
	unsigned int	size;
	int				width;
	int				height;
	unsigned short	planes;
	unsigned short	bpp;
	unsigned int	compression;
	unsigned int	img_size;
	int				x_ppm;
	int				y_ppm;
	unsigned int	total_color;
	unsigned int	important_color;
}					t_info_header;

float	ft_distance(float x, float y, float xend, float yend);
void	ft_drawline(int x_start, int y_start, float distance, float angle,
t_param *param);
void	ft_rectangle(int x, int y, int size, int col, t_param *param);
float	ft_normalizeangle(float angle);
void	ft_castallrays(t_param *param);
void	ft_raydirection(t_param *param, float angle, int id);
void	ft_initrays(t_param *param, int id);
int		ft_iswall(float x, float y);
void	ft_renderplayer(t_param *param);
void	ft_updateplayer(t_param *param);
void	ft_rendermap(const char map[13][20], t_param *param);
void	ft_initplayer(const char map[MAP_ROWS][MAP_COLS], t_param *param);
void	ft_render3d(t_param *param, int id);
void	ft_inittexture(t_param *param);
void	ft_puttxt(t_param *param, int y, int x, int end, int i);
void	ft_rendermap(const char map[13][20], t_param *param);
int		ft_iswall(float x, float y);
void	ft_drawwall(int walltop, int wallbottom, t_param *param, int id);
void	ft_initsprite(const char map[MAP_ROWS][MAP_COLS], t_param *param);
int		ft_issprite(float x, float y);
void    ft_initsprite(const char map[MAP_ROWS][MAP_COLS], t_param *param);
void	ft_spritetxt(t_param *param);
float	ft_angle(t_param *param);
void	ft_drawsprite(float y_start, float y_end, float sprite_size, t_param *param, int id);
void	ft_putsprite(t_param *param);
float	ft_angle(t_param *param);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void    ft_save(t_param *param, char *name);
void	ft_writecolor(int fd, t_param *param);
#endif
