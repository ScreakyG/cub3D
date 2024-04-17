/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:20:17 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/18 01:37:59 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdbool.h>
# include <stdint.h>
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

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define MINIMAP_SCALE 0.2

# define TILE_SIZE 64
# define FOV 60
# define NUM_RAYS WIN_WIDTH

enum e_texture_index
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};

typedef struct s_ray_inter
{
	float	x_intercept;
	float	y_intercept;
	float	x_step;
	float	y_step;
	int		found_wall_hit;
	float	wall_hit_x;
	float	wall_hit_y;
	int		wall_content;
	float	next_touch_x;
	float	next_touch_y;
	float	x_to_check;
	float	y_to_check;
	float	distance;
}	t_ray_inter;

typedef struct s_texture
{
	int		*color_buffer;
	int		width;
	int		height;
}	t_texture;

typedef struct s_ray
{
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	int		is_ray_facing_up;
	int		is_ray_facing_down;
	int		is_ray_facing_left;
	int		is_ray_facing_right;
	int		hit_content;
	bool	was_hit_vertical;
}	t_ray;

typedef struct s_map
{
	int		player_pos_y;
	int		player_pos_x;
}	t_map;

typedef struct s_player
{
	float	fov_rd;
	float	x;
	float	y;
	float	width;
	float	height;
	int		rotation_direction;
	int		walk_direction;
	int		side_direction;
	float	rotation_angle;
	float	walk_speed;
	float	turn_speed;
}	t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*mlx_win;
}	t_mlx;

typedef struct s_render
{
	float		top_pixel;
	float		bot_pixel;
	float		wall_h;
	int			ray_idx;
}	t_render;


typedef struct s_data
{
	t_mlx		mlx;
	t_img		*img;
	t_player	player;
	t_map		map;
	t_ray		rays[NUM_RAYS];
	t_texture	*textures;
	t_render	render;
	char		**map_tab;
	char		**map_grid;
	int			idx_map_start;
	int			idx_map_end;
	int			height;
	int			width;
	float		width_world;
	float		height_world;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*f;
	char		*c;
	int			f_hex;
	int			c_hex;
	float		dist_plane;
}	t_data;

/////// FREE FUNCTIONS ///////

void	ft_exit_error(char *msg, int exit_code, t_data *data);
int		clean_exit(t_data *data);
void	free_textures(t_data *data);

/////// CHECK MAP FUNCTIONS ///////

void	check_map_validity(int argc, char **argv, t_data *data);
bool	is_directory(char *filename);
bool	verify_right_side(t_data *data);
bool	verify_left_side(t_data *data);
void	get_map_end_idx(t_data *data);

/////// CHECK TEXTURES FUNCTIONS ///////

void	verify_textures(t_data *data);

/////// PARSE IDENTIFIERS FUNCTIONS ///////

void	parse_identifiers(t_data *data);
bool	enough_identifiers(t_data *data);
void	add_value_to_identifier(char *value, char *identifier, t_data *data);
void	get_identifier_value(t_data *data, char **map_tab,
			int value_start, char *identifier);
bool	word_is_identifier(char *word, t_data *data);
bool	fill_identifier(t_data *data, char *identifier, char *value);
char	*get_identifier_name(t_data *data, char **map_tab, int *j);

/////// PARSE MAP FUNCTIONS ///////

void	parse_map(t_data *data);
void	skip_white_lines(t_data *data);
void	check_if_closed_map(t_data *data);
void	create_map_grid(t_data *data);

/////// INIT TEXTURES FUNCTIONS ///////

void	init_textures(t_data *data);
int		rgb_to_hex(int red, int green, int blue);
void	init_floor_ceiling_colors(t_data *data);
int		*fill_color_buffer(t_texture *texture, int *addr);

///// INIT PLAYER FUNCTIONS ///////

void	init_player(t_data *data);

/////// INIT MLX FUNCTIONS ///////

void	init_mlx(t_data *data);

/////// GAME LOOP FUNCTIONS ///////

void	start_game(t_data *data);
int		game_loop(void *data);

/////// KEYBINDS FUNCTIONS ///////

int		handle_keypress(int keycode, void *data);
int		handle_keyrelease(int keycode, void *data);
void	movements(t_data *data);

////// RAYCASTING FUNCTIONS ////////

void		cast_all_rays(t_data *data);
void		cast_ray(t_ray *ray, t_data *data);
float		normalize_angle(float ray_angle);
void		init_ray_directions(t_ray *ray);
float		get_distance(float x1, float y1, float x2, float y2);
void		init_ray(t_ray *ray);
bool		map_has_wall_hat(float x, float y, t_data *data);
void		print_debug_rays(t_ray *ray);
int			get_cell_content(t_data *data, float x, float y);
t_ray_inter	get_h_inter(t_data *data, t_ray *ray);
t_ray_inter	get_v_inter(t_data *data, t_ray *ray);
void		get_x_y_step(t_ray *ray, t_ray_inter *r, int horz);
void		get_intercepts(t_data *data, t_ray *ray, t_ray_inter *r, int horz);
void		init_ray_inter(t_ray_inter *r);
int			pixel_force(t_ray *ray, bool horz);
void		fill_values(t_data *data, t_ray_inter *r);
void		fill_ray_values(t_ray *ray, t_ray_inter *r, bool vert_hit);

////// RENDER FUNCTIONS ////////

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	render_background(t_data *data, t_img *img);
void	render_minimap(t_data *data, t_img *img);
void	render_player(t_data *data, t_img *img);
void	render_rays(t_data *data, t_img *img);

//// PROJECTION FUNCTIONS /////

void	render_projection(t_data *data, t_img *img);

/////// UTILS FUNCTIONS ///////

int		get_number_lines(char *map_arg);
void	print_map(t_data *data);
void	print_identifiers(t_data *data);
void	free_strs(char **strs);
int		str_len_skip_ws(char *str);
void	print_grid(t_data *data);
int		get_player_number(t_data *data);
int		tab_len(char **tab);
bool	only_digit(char *str);
bool	is_empty(char *str);
void	error_identifier_name(char *identifier, t_data *data);
void	error_identifier_value(char *identifier, t_data *data);
int		get_player_pos(t_data *data, char axis);
bool	wall_colision(t_data *data, float x_step, float y_step);
void	init_img(t_img *img);

#endif
