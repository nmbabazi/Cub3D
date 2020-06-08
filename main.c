#include "mlx.h"
#include "const.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

typedef struct s_player
{
	int x;
	int y;
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

typedef struct	s_param
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_image	img;
}				t_param;
const char map[MAP_ROWS][MAP_COLS] = {
    "11111111111111111111",
    "10000000000000010001",
    "10000000000000010001",
    "10000000000000010001",
    "10000000000000000001",
    "10000000000030000001",
    "10000000000000000001",
    "10000000000000000001",
    "10000011100000000001",
    "10000000000000010001",
    "10100000000000010001",
    "11000000000000010001",
    "11111111111111111111",
};


int	deal_key(int nb, t_param *param)
{
	if (nb == 53) 
		exit(0);
	return (1);
}

void	ft_stroke(int x_st, int y_st, int x_end, int y_end, t_param *param)
{
	if (y_end < 0)
		y_end *= -1;
	if (x_end < 0)
		x_end *= -1;
	while (y_st < y_end)
	{
		while (x_st < x_end)
		{
			param->img.data[y_st * WIN_WIDTH + x_st] = 0xffff00;
			x_st++;
		}
		y_st++;
	}
}

void	ft_creattile(int x, int y, int size, int col, t_param *param)
{	
	int count_y = 0;
	int count_x = 0;
	int x_start = x;
	int col_start = col;
	
	while (count_y < TILE_S)
	{
		count_x = 0;
		x = x_start;
		while(count_x < TILE_S)
		{
			if (y % TILE_S == 0 || x % TILE_S == 0)
				col = 0xFFFFFF;
			else 
				col = col_start;
			param->img.data[y * WIN_WIDTH + x] = col;
			count_x++;
			x++;
		}
		count_y++;
		y++;
	}
	return;
}

void	ft_creatplayer(int x, int y, t_param *param)
{
	int i = 0;
	int l = 0;
	int x_start = x;
	int y_start = y;
	int x_end;
	int y_end;
	
	while (l < 10)
	{
		i = 0;
		x = x_start;
		while (i < 10)
		{
			param->img.data[y * WIN_WIDTH + x] = 0x850606;
			i++;
			x++;
		}
		l++;
		y++;
	}	
//	printf("ANGLE %6f\n", cos(70 * (PI / 180)));	
	x_end = x_start + cos(M_PI / 2) * 20;
	y_end = y_start + sin(M_PI / 2) * 20;
	ft_stroke(x_start, y_start, x_end, y_end, param);
}

void	ft_placeplayer(const char map[MAP_ROWS][MAP_COLS], t_param *param, t_player *player)
{
	int i = 0;
	int l = 0;
	
	while (l < MAP_ROWS)
	{
		i = 0;
		while(i < MAP_COLS)
		{	
			if (map[l][i] == '3')
			{
				ft_creatplayer(i * TILE_S, l * TILE_S, param);
				break;
			}
			i++;
		}
		l++;
	}
	player->x = i * TILE_S;
	player->y = l * TILE_S;
	return ;
}

void	ft_creatgrid(const char map[13][20], t_param *param)
{
	int i = 0;
	int l = 0;
	int col = 0x000000;
	
	while (l < MAP_ROWS)
	{
		i = 0;
		while(i < MAP_COLS)
		{	
			if (map[l][i] == '1')
				col = 0xFFFFFF;
			else if (map[l][i] != '1')
				col = 0x000000;	
			ft_creattile(i * TILE_S, l * TILE_S, TILE_S, col, param);
			i++;
		}
		l++;
	}
}

int main()
{
	t_param param;
	t_player player;

	param.mlx_ptr = mlx_init();
	param.win_ptr = mlx_new_window(param.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "fuck yeah");
	param.img.img_ptr = mlx_new_image (param.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	param.img.data = (int *)mlx_get_data_addr(param.img.img_ptr, &param.img.bpp, &param.img.size_l,&param.img.endian);
	ft_creatgrid(map, &param);
	ft_placeplayer(map, &param, &player);
	mlx_put_image_to_window(param.mlx_ptr, param.win_ptr, param.img.img_ptr, 0, 0);
	mlx_key_hook(param.win_ptr, deal_key, &param);
	mlx_loop(param.mlx_ptr);
}
