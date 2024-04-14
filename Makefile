NAME = cub3D
NAME_BONUS = cub3D_bonus
CFLAGS = -Wall -Wextra -Werror -g
CC = gcc

## COLORS ##
RED = \033[31m
GRE = \033[32m
GRA = \033[37m
BLU = \033[34m
EOC = \033[0m

##### MANDATORY FILES ####
SRCS_DIR = mandatory/srcs/
SRCS_FILES = main.c map_check.c free.c utils.c parse_map.c parse_identifiers.c create_grid.c init_textures.c init_mlx.c textures_check.c keybinds.c render.c init_player.c movements.c raycasting.c projection.c parse_map_utils.c raycasting_utils.c raycasting_utils2.c raycasting_utils3.c utils2.c utils3.c parse_identifiers_utils.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))
SRCS_OBJS = $(SRCS:.c=.o)

#### BONUS FILES ####
SRCS_DIR_BONUS = bonus/srcs/
SRCS_FILES_BONUS = main.c map_check.c free.c utils.c parse_map.c parse_identifiers.c create_grid.c init_textures.c init_mlx.c textures_check.c keybinds.c render.c init_player.c movements.c raycasting.c projection.c
SRCS_BONUS = $(addprefix $(SRCS_DIR_BONUS), $(SRCS_FILES_BONUS))
SRCS_OBJS_BONUS = $(SRCS_BONUS:.c=.o)

#### LIBFT FILES ####
LIBFT_DIR = libft/
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_DIR) $(LIBFT_NAME)

#### MLX FILES ####
MLX_DIR = minilibx-linux/
MLX_NAME = libmlx.a
MLX = $(MLX_DIR) $(MLX_NAME)


%.o: %.c
		@echo "$(BLU) ● Compiling $^ 🔧$(EOC)"
		@$(CC) $(CFLAGS) -I/usr/include -Iminilibx-linux -c $< -o $@

all: $(LIBFT) $(MLX) $(NAME)

bonus: $(LIBFT) $(MLX) $(NAME_BONUS)

$(NAME): $(SRCS_OBJS)
		@echo "$(GRE)● cub3D ready ⚙️ $(EOC)"
		@$(CC) $(CFLAGS) $(SRCS_OBJS) -Lminilibx-linux -lmlx -L/usr/lib -L$(LIBFT_DIR) -lft -Iminilibx-linux -lXext -lX11 -lm -lz -o $(NAME)

$(NAME_BONUS): $(SRCS_OBJS_BONUS)
		@echo "$(GRE)● cub3D bonus ready ⚙️ $(EOC)"
		@$(CC) $(CFLAGS) $(SRCS_OBJS_BONUS) -Lminilibx-linux -lmlx -L/usr/lib -L$(LIBFT_DIR) -lft -Iminilibx-linux -lXext -lX11 -lm -lz -o $(NAME_BONUS)

$(LIBFT):
		@echo "$(GRE) Creating libft library ⚙️ $(EOC)"
		@make -sC $(LIBFT_DIR)

$(MLX):
		@echo "$(GRE) Creating minilibx library ⚙️$(EOC)"
		@make -sC $(MLX_DIR)


clean:
		@echo "$(RED)● Cleaning .o files 📁$(EOC)"
		@rm -rf $(SRCS_OBJS)
		@make clean -sC $(MLX_DIR)
		@make clean -sC $(LIBFT_DIR)

cleanbonus:
		@echo "$(RED)● Cleaning .o bonus files 📁$(EOC)"
		@rm -rf $(SRCS_OBJS_BONUS)
		@make clean -sC $(MLX_DIR)
		@make clean -sC $(LIBFT_DIR)

fclean: clean
		@echo "$(RED)● Deleting $(NAME) $(EOC)"
		@rm -rf $(NAME)
		@make clean -sC $(LIBFT_DIR)

fcleanbonus: cleanbonus
		@echo "$(RED)● Deleting $(NAME_BONUS) $(EOC)"
		@rm -rf $(NAME_BONUS)
		@make clean -sC $(LIBFT_DIR)

re: fclean all
rebonus: fcleanbonus $(NAME_BONUS)

.PHONY: all clean fclean re



