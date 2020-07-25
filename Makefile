
MLX = -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

NAME = cub3D

SRCS = 	main.c \
		player/player.c \
		player/vecteur.c \
		player/initplayer.c \
		ray/ray.c \
		ray/horzandvert.c \
		wall/wall.c	\
		texture.c \
		sprite/putsprite.c \
		sprite/initsprite.c \
		sprite/drawsprite.c \
		sprite/sortsprite.c \
		screenshot/save.c \
		utiles/exit.c \
		utiles/utiles.c \
		parsing/checkarg.c \
		parsing/checkmap.c \
		parsing/parscolor.c \
		parsing/parsmap.c \
		parsing/parsresolution.c \
		parsing/parstexture.c \
		parsing/startparsing.c \
		parsing/tab.c \
		parsing/utils.c \
		parsing/gnl.c \

SRCS_BONUS = bonus_main.c \
			player/player.c \
			player/vecteur.c \
			player/initplayer.c \
			ray/ray.c \
			ray/horzandvert.c \
			wall/wall.c	\
			texture.c \
			sprite/putsprite.c \
			sprite/initsprite.c \
			sprite/drawsprite.c \
			sprite/sortsprite.c \
			screenshot/save.c \
			utiles/exit.c \
			utiles/utiles.c \
			parsing/checkarg.c \
			parsing/checkmap.c \
			parsing/parscolor.c \
			parsing/parsmap.c \
			parsing/parsresolution.c \
			parsing/parstexture.c \
			parsing/startparsing.c \
			parsing/tab.c \
			parsing/utils.c \
			parsing/gnl.c \

OBJSRCS = $(SRCS:.c=.o) 
OBJSRCS_BONUS = $(SRCS_BONUS:.c=.o) 

$(NAME) : $(OBJSRCS)
	@echo "\033[33m[Remove last version...]"
	@rm -rf Cub3D
	@echo "\033[33m[Cub3D compilation...]"
	@echo "\033[33m[Libft compilation...]"
	$(MAKE) -C ./libft
	@gcc -o $(NAME) -I include.h $(OBJSRCS) $(MLX) ./libft/libft.a -Wall -Wextra -Werror -g
	@echo "\033[33m[Done !]"

all : $(NAME)

bonus :$(OBJSRCS_BONUS)
	@echo "\033[33m[Remove last version...]"
	@rm -rf Cub3D
	@echo "\033[33m[Cub3D compilation...]"
	@echo "\033[33m[Libft compilation...]"
	$(MAKE) -C ./libft
	@gcc -o $(NAME) -I include.h $(OBJSRCS_BONUS) $(MLX) ./libft/libft.a -Wall -Wextra -Werror -g
	@echo "\033[33m[Done !]"

clean :
	rm -rf $(OBJSRCS)
	rm -rf $(OBJSRCS_BONUS)
	$(MAKE) clean -C ./libft

fclean : clean
	$(MAKE) fclean -C ./libft
	rm -rf $(NAME)
	rm -rf save.bmp

re : fclean all