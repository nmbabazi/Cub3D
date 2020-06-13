#include "mlx.h"
#include "const.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

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
	int	wasHitVert;
	
}				t_ray;
typedef struct	s_param
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_image	img;
	t_player	player;
	t_ray		ray;
}				t_param;

const char map[MAP_ROWS][MAP_COLS] = {
    "11111111111111111111",
    "10000000000000010001",
    "10000000000000010001",
    "10000000000000010001",
    "10000000000000000001",
    "10000000000000000001",
    "10000000003000000001",
    "10000000000000000001",
    "10000011100000000001",
    "10000000000000010001",
    "10100000000000010001",
    "11000000000000010001",
    "11111111111111111111",
};

float	ft_distance(float x, float y, float xend, float yend)
{
	return (sqrt((xend - x) * (xend -x) + (yend - y) * (yend - y)));
//	return (sqrt((x - xend) * (x -xend) + (y - yend) * (y - yend)));

}

void	ft_drawline(int X, int Y, float distance, int color, float angle, t_param *param)
{
	float i;
	int x;
	int y;
	int longeur;

	longeur = 0;
	i = 0;
	x = 0;
	y = 0;
	while (i < distance)
	{
		param->img.data[(Y + y) * WIN_WIDTH + (X + x)] = color;
		x = cos(angle) * longeur;
		y = sin(angle) * longeur;
		longeur++;
		i++;
	}
}

void	ft_sqare(int x, int y, int size, int col, t_param *param)
{	
	int count_y = 0;
	int count_x = 0;
	int x_start = x;
	int col_start = col;
	
	while (count_y < size)
	{
		count_x = 0;
		x = x_start;
		while(count_x < size)
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


void	ft_initplayer(const char map[MAP_ROWS][MAP_COLS], t_param *param)
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
				param->player.x = i * TILE_S + TILE_S / 2;
				param->player.y = l * TILE_S + TILE_S / 2;
				break;
			}
			i++;
		}
		l++;
	}
	param->player.rotationAngle = M_PI / 2;
	param->player.walkSpeed = 2;
	param->player.turnSpeed  = 2 * (M_PI / 180);
	return ;
}

void	ft_rendermap(const char map[13][20], t_param *param)
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
			ft_sqare(i * TILE_S, l * TILE_S, TILE_S, col, param);
			i++;
		}
		l++;
	}
}

int	key_press(int key, void *data)
{
	t_param *param;

	param = (t_param *)data;
	if (key == 124)
	{
		param->player.turnDirection = +1;
	}
	if (key == 123)
	{
		param->player.turnDirection = -1;
	}
	if (key == 126)
	{
		param->player.walkDirection = 1;
	}
	if (key == 125)
	{
		param->player.walkDirection = -1;
	}
	if (key == 53)
		exit(0);
	return (1);
}

int	key_release(int key, void *data)
{
	t_param *param;

	param = (t_param *)data;
	if (key == 124)
	{
		param->player.turnDirection = 0;
	}
	if (key == 123)
	{
		param->player.turnDirection = 0;
	}
	if (key == 126)
	{
		param->player.walkDirection = 0;
	}
	if (key == 125)
	{
		param->player.walkDirection = 0;
	}
	return (1);
}


void	ft_renderplayer(t_param *param)
{
	int l = 0;
	ft_sqare(param->player.x - 15 / 2, param->player.y - 15 / 2, 15, 0xFF0000, param);

}

int	ft_isWall(float x, float y)
{
	int indexX;
	int indexY;
	
	if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
		return (1);
	indexX = floor(x / TILE_S);
	indexY = floor(y / TILE_S);
	if (map[indexY][indexX] == '1')
		return(1);
	return (0);

}

void	ft_updateplayer(t_param *param)
{
	param->player.rotationAngle += param->player.turnDirection * param->player.turnSpeed;
	float  moveStep = param->player.walkDirection * param->player.walkSpeed;

	float NewplayerX = param->player.x + cos(param->player.rotationAngle) * moveStep;
	float NewplayerY = param->player.y + sin(param->player.rotationAngle) * moveStep;

	if (ft_isWall(NewplayerX, NewplayerY) == 0)
	{
		param->player.x = NewplayerX;
		param->player.y = NewplayerY;
	}
}


float	ft_normalizeAngle(float angle)
{
	angle = remainder(angle, M_PI * 2); 
	if (angle < 0)
		angle = (M_PI * 2) + angle;
	return (angle); 
}

void	ft_rayfacing(t_param *param, float angle)
{
	if (angle > 0 && angle < M_PI)
		param->ray.rayDown = 1;
	else
		param->ray.rayDown = -1;
	if (angle < (M_PI * 0.5) || angle > (M_PI * 1.5))
		param->ray.rayRight = 1;
	else
		param->ray.rayRight = -1;
}

void	ft_initrays(t_ray *ray)
{
	ray->rayAngle = 0;
	ray->wallHitX = 0;
	ray->wallHitY = 0;
	ray->collDistance = 0;
	ray->rayDown = 0;
	ray->rayRight = 0;
	ray->wasHitVert = 0;
	
}

void	ft_renderrays(t_param *param, float angle)
{
	float horzHitDistance = 0;
	float vertHitDistance = 0;
//////////////////////HORIZONTAL//////////////////////////
	ft_initrays(&param->ray);
	angle = ft_normalizeAngle(angle);
	ft_rayfacing(param, angle);
	int	horzHit = 0;
	float	horzWallHitX = 0;
	float	horzWallHitY = 0;
	float yintercept;
	float xintercept;
	float xstep;
	float ystep;
	
	yintercept = floor(param->player.y / TILE_S) * TILE_S;
	if (param->ray.rayDown == 1)
		yintercept += TILE_S;
	xintercept = param->player.x + ((yintercept - param->player.y) / tan(angle));
	ystep = TILE_S;
	if (param->ray.rayDown == -1)
		ystep *= -1;
	xstep = TILE_S / tan(angle);
	if (param->ray.rayRight == -1 && xstep > 0)
		xstep *= -1;
	if (param->ray.rayRight == 1 && xstep < 0)
		xstep *= -1;
	float	nextHorzY = yintercept;
	float	nextHorzX = xintercept;
	if (param->ray.rayDown == -1)
		nextHorzY--;
	while (nextHorzX >= 0 && nextHorzX <= WIN_WIDTH  && nextHorzY >= 0 && nextHorzY <= WIN_HEIGHT)
	{
		if (ft_isWall(nextHorzX, nextHorzY) == 1)
		{
			horzHit = 1;
			horzWallHitX = nextHorzX;
			horzWallHitY = nextHorzY;
			break;
		}
		else
			nextHorzX += xstep;
			nextHorzY += ystep;
	}
/////////////////////VERTICAL//////////////////////////
	int	vertHit = 0;
	float	vertWallHitX = 0;
	float	vertWallHitY = 0;
	xintercept = floor(param->player.x / TILE_S) * TILE_S;
	if (param->ray.rayRight == 1)
		xintercept += TILE_S;
	yintercept = param->player.y + ((xintercept - param->player.x) * tan(angle));
	xstep = TILE_S;
	if (param->ray.rayRight == -1)
		xstep *= -1;
	ystep = TILE_S * tan(angle);
	if (param->ray.rayDown == -1 && ystep > 0)
		ystep *= -1;
	if (param->ray.rayDown == 1 && ystep < 0)
		ystep *= -1;
	float	nextVertY = yintercept;
	float	nextVertX = xintercept;
	if (param->ray.rayRight == -1)
		nextVertX--;
	while (nextVertX >= 0 && nextVertX <= WIN_WIDTH  && nextVertY >= 0 && nextVertY <= WIN_HEIGHT)
	{
		if (ft_isWall(nextVertX, nextVertY) == 1)
		{
			vertHit = 1;
			vertWallHitX = nextVertX;
			vertWallHitY = nextVertY;
			break;
		}
		else
			nextVertX += xstep;
			nextVertY += ystep;
	}
//////////////////////DISTANCES////////////////////
	if (horzHit == 1)
		horzHitDistance = ft_distance(param->player.x, param->player.y, horzWallHitX, horzWallHitY);
	else 
		horzHitDistance = INT_MAX;
	if (vertHit == 1)
		vertHitDistance = ft_distance(param->player.x, param->player.y, vertWallHitX, vertWallHitY);
	else 
		vertHitDistance = INT_MAX;
///////////////////RESULTAT////////////////////
	if (horzHitDistance <= vertHitDistance)
	{
		param->ray.wallHitX = horzWallHitX;
		param->ray.wallHitY = horzWallHitY;
		param->ray.collDistance = horzHitDistance;
		param->ray.wasHitVert = 0;
	}
	if (horzHitDistance > vertHitDistance)
	{
		param->ray.wallHitX = vertWallHitX;
		param->ray.wallHitY = vertWallHitY;
		param->ray.collDistance = vertHitDistance;
		param->ray.wasHitVert = 1;
	}
/////////////////RENDER////////////////////////
	ft_drawline(param->player.x, param->player.y, param->ray.collDistance, 0xffff00, angle, param);
}

void	ft_castrays(t_param *param)
{
	float angle = param->player.rotationAngle - (FOV / 2);
	int i = 0;
	angle = ft_normalizeAngle(angle);

	while (i < NUM_RAYS)
	{
		ft_renderrays(param, angle);
		angle += FOV / NUM_RAYS;
		i++;
	}
}


int	game_loop(t_param *param)
{
	param->img.img_ptr = mlx_new_image(param->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	param->img.data = (int *)mlx_get_data_addr(param->img.img_ptr, &param->img.bpp, &param->img.size_l, &param->img.endian);
	ft_rendermap(map, param);
	ft_updateplayer(param);
	ft_castrays(param);
	ft_renderplayer(param);
	mlx_put_image_to_window(param->mlx_ptr, param->win_ptr, param->img.img_ptr, 0, 0);
	mlx_destroy_image(param->mlx_ptr, param->img.img_ptr);
	return (1);
}

int main()
{
	t_param param;
	t_player player;

	param.mlx_ptr = mlx_init();
	param.win_ptr = mlx_new_window(param.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "fuck yeah");
	ft_initplayer(map, &param);
	mlx_hook(param.win_ptr, 2, 0, &key_press, &param);
	mlx_hook(param.win_ptr, 3, 0, &key_release, &param);
	mlx_loop_hook(param.mlx_ptr, &game_loop, &param);
	mlx_loop(param.mlx_ptr);
}
