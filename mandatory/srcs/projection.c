/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 23:58:22 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/18 17:02:07 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	get_ray_hit_direction(t_ray ray)
{
	if (ray.was_hit_vertical == 0)
	{
		if (ray.ray_angle > 0 && ray.ray_angle < M_PI)
			return (SOUTH);
		else
			return (NORTH);
	}
	else if (ray.was_hit_vertical == 1)
	{
		if (ray.ray_angle > M_PI / 2 && ray.ray_angle < 1.5 * M_PI)
			return (WEST);
		else
			return (EAST);
	}
	return (0);
}

static void	draw_wall(t_img *img, int top_pixel, t_data *data)
{
	int	wall_color;
	int	tex_offset_x;
	int	tex_offset_y;
	int	dir;
	int	dist_from_top;

	dir = get_ray_hit_direction(data->rays[data->render.ray_idx]);
	if (data->rays[data->render.ray_idx].was_hit_vertical)
		tex_offset_x = ((float)((int)data->rays[data->render.ray_idx].wall_hit_y
					% TILE_SIZE) / TILE_SIZE) * data->textures[dir].width;
	else
		tex_offset_x = ((float)((int)data->rays[data->render.ray_idx].wall_hit_x
					% TILE_SIZE) / TILE_SIZE) * data->textures[dir].width;
	while (top_pixel < data->render.bot_pixel)
	{
		dist_from_top = top_pixel + (data->render.wall_h / 2)
			- (WIN_HEIGHT / 2);
		tex_offset_y = dist_from_top
			* ((float)data->textures[dir].height / data->render.wall_h);
		if (tex_offset_y < 0)
			tex_offset_y = 0;
		wall_color = data->textures[dir].color_buffer[(data->textures[dir].width
				* tex_offset_y) + tex_offset_x];
		my_mlx_pixel_put(img, data->render.ray_idx, top_pixel++, wall_color);
	}
}

static void	draw_floor_ceilling(t_img *img, t_data *data)
{
	int	y;
	int	ray_nbr;

	y = data->render.bot_pixel;
	ray_nbr = data->render.ray_idx;
	while (y < WIN_HEIGHT)
		my_mlx_pixel_put(img, ray_nbr, y++, data->f_hex);
	y = 0;
	while (y < data->render.top_pixel)
		my_mlx_pixel_put(img, ray_nbr, y++, data->c_hex);
}

void	render_projection(t_data *data, t_img *img)
{
	float	wall_h;
	float	fixed_angle;

	data->render.ray_idx = 0;
	while (data->render.ray_idx < NUM_RAYS)
	{
		fixed_angle = normalize_angle(data->rays[data->render.ray_idx].ray_angle
				- data->player.rotation_angle);
		data->rays[data->render.ray_idx].distance *= cos(fixed_angle);
		wall_h = (TILE_SIZE / data->rays[data->render.ray_idx].distance)
			* data->dist_plane;
		data->render.bot_pixel = (WIN_HEIGHT / 2) + (wall_h / 2);
		data->render.top_pixel = (WIN_HEIGHT / 2) - (wall_h / 2);
		if (data->render.bot_pixel > WIN_HEIGHT)
			data->render.bot_pixel = WIN_HEIGHT;
		if (data->render.top_pixel < 0)
			data->render.top_pixel = 0;
		data->render.wall_h = wall_h;
		draw_wall(img, data->render.top_pixel, data);
		draw_floor_ceilling(img, data);
		data->render.ray_idx++;
	}
}
