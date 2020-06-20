/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 17:42:00 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/06/20 16:54:28 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef INCLUDE_H
# define INCLUDE_H

#include "mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define NO 0
#define SO 1
#define EA 2
#define WE 3
#define TILE_S 50
#define MINIMAP 0.2
#define MAP_ROWS 13
#define MAP_COLS 20
#define WIN_WIDTH (MAP_COLS * TILE_S)
#define WIN_HEIGHT (MAP_ROWS * TILE_S)
#define FOV 60 * (M_PI / 180)
#define COLS_S 1
#define NUM_RAYS (WIN_WIDTH / COLS_S)

typedef struct s_player
{
	float x;
	float y;
	int turnDirection;
	int walkDirection;
	float rotationAngle;
	float walkSpeed;
	float turnSpeed;
}				t_player;

typedef struct	s_img
{
	void	*img_ptr;
	int	*data;
	int	bpp;
	int	endian;
	int	size_l;
}				t_image;

typedef struct	s_ray
{
	float	rayAngle;
	float	wallHitX;
	float	wallHitY;
	float	collDistance;
	int		rayDown;
	int		rayRight;
	int		wasHitVert;
	int		wallHeight;

}				t_ray;

typedef	struct	s_texture
{
	void	*ptr;
	int	*data;
	int	bpp;
	int	endian;
	int	size_l;
	int	width;
	int height;
}
				t_texture[4];
typedef struct	s_param
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_image	img;
	t_player	player;
	t_ray		ray;
	t_texture	texture;
}				t_param;


float	ft_distance(float x, float y, float xend, float yend);
void	ft_drawline(int X, int Y, float distance, int color, float angle, t_param *param);
void	ft_rectangle(int x, int y, int width, int height, int col, t_param *param);
float	ft_normalizeAngle(float angle);
void	ft_castallrays(t_param *param);
void	ft_castsingleray(t_param *param, float angle, int);
void	ft_raydirection(t_param *param, float angle);
void	ft_initrays(t_ray *ray);
int	ft_isWall(float x, float y);
void	ft_renderplayer(t_param *param);
void	ft_updateplayer(t_param *param);
void	ft_rendermap(const char map[13][20], t_param *param);
void	ft_initplayer(const char map[MAP_ROWS][MAP_COLS], t_param *param);
void	ft_renderWall(t_param *param, float angle, int i);
void	ft_inittexture(t_param *param);
void ft_puttxt(t_param *param, int y, int x, int end, int i);

#endif
