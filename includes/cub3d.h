/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:20:17 by fgonzale          #+#    #+#             */
/*   Updated: 2024/03/25 09:45:48 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <string.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "../includes/Color.h"

# define WIN_WIDTH 600
# define WIN_HEIGHT 300

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*mlx_win;
}	t_mlx;

typedef struct s_data
{
	t_mlx	mlx;
	char **map_tab;
	char **map_grid;
	int		idx_map_start;
	int		idx_map_end;
	int		height;
	int		width;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	int		f_hex;
	int		c_hex;
}	t_data;

/////// FREE FUNCTIONS ///////

void ft_exit_error(char *msg, int exit_code, t_data *data);
void clean_exit(t_data *data);


/////// CHECK MAP FUNCTIONS ///////

void check_map_validity(int argc, char **argv, t_data *data);
bool is_directory(char *filename);

/////// CHECK TEXTURES FUNCTIONS ///////

void verify_textures(t_data *data);

/////// PARSE IDENTIFIERS FUNCTIONS ///////

void parse_identifiers(t_data *data);
bool enough_identifiers(t_data *data);

/////// PARSE MAP FUNCTIONS ///////

void parse_map(t_data *data);
void skip_white_lines(t_data *data);
void check_if_closed_map(t_data *data);
void create_map_grid(t_data *data);

/////// INIT TEXTURES FUNCTIONS ///////

void init_textures(t_data *data);
int rgb_to_hex(int red, int green, int blue);
void init_floor_ceiling_colors(t_data *data);

/////// INIT MLX FUNCTIONS ///////

void init_mlx(t_data *data);

/////// GAME LOOP FUNCTIONS ///////

void	start_game(t_data *data);
int		game_loop(void *data);

/////// KEYBINDS FUNCTIONS ///////

int handle_keypress(int keycode, void *data);

/////// UTILS FUNCTIONS ///////

int	get_number_lines(char *map_arg);
void print_map(t_data *data);
void print_identifiers(t_data *data);
void free_strs(char **strs);
int	str_len_skip_ws(char *str);
void print_grid(t_data *data);
int	get_player_number(t_data *data);
int	tab_len(char **tab);
bool only_digit(char *str);
bool is_empty(char *str);
void error_identifier_name(char *identifier, t_data *data);
void error_identifier_value(char *identifier, t_data *data);

#endif
