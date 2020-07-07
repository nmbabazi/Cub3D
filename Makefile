
MLX = -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

NAME = cub3D

SRCS = 	main.c \
		ft_ray.c\
		ft_player.c \
		utiles.c \
		ft_texture.c \
		ft_walls.c	\
		ft_sprite.c \

OBJSRCS = $(SRCS:.c=.o) 

$(NAME) : $(OBJSRCS)
	@echo "\033[33m[Remove last version...]"
	@rm -rf Cub3D
	@echo "\033[33m[Cub3D compilation...]"
	@gcc -o $(NAME) -I include.h $(OBJSRCS) $(MLX)  -Wall -Wextra -Werror -g
	@echo "\033[33m[Done !]"

all : $(NAME)

clean :
	rm -rf $(OBJSRCS)

fclean : clean
	rm -rf $(NAME)
	rm -rf cub3d.bmp

re : fclean all
