/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 17:42:00 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/28 16:19:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include "./minilibx-linux/mlx.h"
# include "./minilibx-linux/mlx_int.h"
# include "parsing/parsing.h"
# include "./libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <math.h>
# include <fcntl.h>
# include <pthread.h>
# include <X11/X.h>

# define NO 0
# define SO 1
# define EA 2
# define WE 3
# define S 4
# define CAM_LEFT 65361
# define CAM_RIGHT 65363
# define KEY_LEFT 97
# define KEY_RIGHT 100
# define KEY_UP 119
# define KEY_DOWN 115
# define VERT 1
# define HORZ 0
# define MINIMAP 0.3
# define FOV 1.0471975511965977f

typedef struct		s_player
{
	float		x;
	float		y;
	int			turndirection;
	int			walkdirection;
	float		rotationangle;
	float		walkspeed;
	float		turnspeed;
	int			translation;
	int			facingvert;
	char		c;
	float		diry;
	float		dirx;
	float		plany;
	float		planx;
}					t_player;

typedef struct		s_image
{
	void	*img_ptr;
	int		*data;
	int		bpp;
	int		endian;
	int		size_l;
}					t_image;

typedef struct		s_ray
{
	float	rayangle;
	float	wallhitx;
	float	wallhity;
	float	colldistance;
	int		raydown;
	int		rayright;
	int		washitvert;
	int		wallheight;
	float	vertwallhitx;
	float	vertwallhity;
	float	horzwallhitx;
	float	horzwallhity;
	float	yintercept;
	float	xintercept;
	float	xstep;
	float	ystep;
	float	nextcheck;
}					t_ray;

typedef	struct		s_texture
{
	void	*ptr;
	int		*data;
	int		bpp;
	int		endian;
	int		size_l;
	int		width;
	int		height;
	char	*path;
}					t_texture[4];

typedef struct		s_sprite
{
	float	*x;
	float	*y;
	float	*distance;
	float	angle;
	void	*ptr;
	int		*data;
	int		bpp;
	int		endian;
	int		size_l;
	int		width;
	int		height;
	char	*path;
	int		nb_sprite;
	float	*buffer;
	int		spritescreenx;
	int		drawstarty;
	int		drawendy;
	int		drawstartx;
	int		drawendx;
}					t_sprite;

typedef struct		s_param
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			win_width;
	int			win_height;
	int			f_color;
	int			c_color;
	char		**map;
	int			map_cols;
	int			map_rows;
	int			tile_s;
	int			num_rays;
	int			argument;
	t_image		img;
	t_player	player;
	t_ray		ray;
	t_texture	texture;
	t_sprite	sprite;
}					t_param;

typedef	struct		s_file_header
{
	char			type[2];
	unsigned int	size;
	unsigned int	reserved;
	unsigned int	offset;
}					t_file_header;

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

float				ft_distance(float x, float y, float xend, float yend);
void				ft_drawline(int x_start, int y_start, float angle,
						t_param *param);
void				ft_drawmap(int x, int y, int col, t_param *param);
float				ft_normalizeangle(float angle);
void				ft_castallrays(t_param *param);
void				ft_raydirection(t_param *param, float angle, int id);
void				ft_initrays(t_param *param, int id);
void				ft_renderplayer(t_param *param);
void				ft_updateplayer(t_param *param);
void				ft_drawplayer(int x, int y, int col, t_param *param);
void				ft_initplayer(t_param *param);
void				ft_render3d(t_param *param, int id);
void				ft_inittexture(t_param *param);
void				ft_puttxt(t_param *param, int y, int x, int i);
void				ft_rendermap(t_param *param);
int					ft_iswall(float x, float y, t_param *param);
void				ft_drawwall(int walltop, int wallbottom,
						t_param *param, int id);
void				ft_initsprite(t_param *param);
void				ft_spritetxt(t_param *param);
float				ft_angle(t_param *param);
void				ft_putsprite(t_param *param);
float				ft_angle(t_param *param);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_save(t_param *param, char *name);
void				ft_writecolor(int fd, t_param *param,
					unsigned int img_size);
void				ft_initwin_size(t_param *param);
void				ft_initvecteur(t_param *param);
int					exit_properly(void *data);
int					ft_checkarg(int ac, char **av);
int					ft_checksave(char *str);
int					ft_checkcub(char *str);
void				ft_initall(t_param *param);
void				ft_initplan(t_param *param);
void				ft_initdir(t_param *param);
int					ft_findhithorz(t_param *param,
						float nexthorzx, float nexthorzy);
int					ft_findhitvert(t_param *param,
						float nextvertx, float nextverty);
float				ft_casthorzray(t_param *param);
float				ft_castvertray(t_param *param);
void				ft_spritedistance(t_param *param);
void				ft_drawsprite(t_param *param,
						float transformy, float sprite_size);
void				ft_zero(t_param *param);
int					ft_parsing(char *fichier, t_param *param);
int					ft_color(char *line, t_param *param, int *tab);
int					ft_resolution(char *line, t_param *param, int *tab);
int					ft_buildmap(t_param *param, char *line, int *r, int fd);
int					ft_oneplayer(char **map, t_param *param);
int					ft_checkmap(char **map, t_param *param);
int					ft_buildmap(t_param *param, char *line, int *r, int fd);
void				ft_fillcolor(char *line, t_param *param, int *temp);
void				ft_sortsprite(t_param *param);
void				ft_updatevect(t_param *param);
int					ft_texture(char *line, t_param *param, int *tab);
void				ft_checksize(t_param *param);
void				ft_initeverything(t_param *param);
void				ft_freemap(t_param *param);
void				ft_freepath(t_param *param);
void				ft_screen_size(t_param *param);
void				ft_draw_floor_ceiling(t_param *param);
void				ft_initimg(t_param *param);

#endif
