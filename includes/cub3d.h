/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:20:17 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/01 20:59:34 by fgonzale         ###   ########.fr       */
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
# include <limits.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "../includes/Color.h"

# define WIN_WIDTH 1500
# define WIN_HEIGHT 800

 #ifndef M_PI
	# define M_PI 3.13159265
 #endif
# define TWO_PI 6.28318530

# define MINIMAP_SCALE 1

# define TILE_SIZE 32
# define FOV 60
# define NUM_RAYS WIN_WIDTH

typedef struct s_ray
{
	float ray_angle;
	float wall_hit_x;
	float wall_hit_y;
	float distance;
	int		is_ray_facing_up;
	int		is_ray_facing_down;
	int		is_ray_facing_left;
	int		is_ray_facing_right;
	int		hit_content;
	bool	was_hit_vertical;
} t_ray;

typedef struct s_map
{
	int player_pos_y;
	int player_pos_x;
} t_map;

typedef struct s_player
{
	float fov_rd; // PLAYER FOV IN RADIANT
	float x; // POSITION X OF PLAYER IN PIXEL
	float y; // POSITION Y OF PLAYER IN PIXEL
	float width; // WIDTH OF PLAYER IN MINIMAP
	float height; // HEIGHT OF PLAYER IN MINIMAP
	int rotation_direction; // -1 for left , +1 for right
	int walk_direction; // -1 for back , +1 for front
	int	side_direction; // -1 for left, +1 for right
	float rotation_angle; // START ROTATION ANGLE
	float walk_speed; // MOVE SPEED IN PIXELS
	float turn_speed; // RADIANT PER SECOND WE RORATE
} t_player;

typedef struct s_img
{
	void 	*img;
	char 	*addr;
	int		bpp;
	int		line_length;
	int		endian;
} t_img;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*mlx_win;
}	t_mlx;

typedef struct s_data
{
	t_mlx	mlx;
	t_img	*img;
	t_player player;
	t_map	map;
	t_ray	*rays;
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

///// INIT PLAYER FUNCTIONS ///////

void init_player(t_data *data);

/////// INIT MLX FUNCTIONS ///////

void init_mlx(t_data *data);

/////// GAME LOOP FUNCTIONS ///////

void	start_game(t_data *data);
int		game_loop(void *data);

/////// KEYBINDS FUNCTIONS ///////

int handle_keypress(int keycode, void *data);
int handle_keyrelease(int keycode, void *data);
void movements(t_data *data);

////// RAYCASTING FUNCTIONS ////////

void cast_all_rays(t_data *data);
void cast_ray(t_ray *ray, t_data *data);
float normalize_angle(float ray_angle);
void init_ray_directions(t_ray *ray);
float get_distance(float x1, float y1, float x2, float y2);
void init_ray(t_ray *ray);
bool map_has_wall_hat(float x, float y, t_data *data);

////// RENDER FUNCTIONS ////////

void my_mlx_pixel_put(t_img *img, int x, int y, int color);
void render_background(t_data *data, t_img *img);
void render_minimap(t_data *data, t_img *img);
void render_player(t_data *data, t_img *img);

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
int	get_player_pos(t_data *data, char axis);
bool wall_colision(t_data *data, float x_step , float y_step);

#endif
