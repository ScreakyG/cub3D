/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 23:58:22 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/06 09:08:34 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int get_ray_hit_direction(t_ray ray)
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
		if (ray.ray_angle > M_PI /2 && ray.ray_angle < 1.5 * M_PI)
			return (WEST);
		else
			return (EAST);
	}
	return (0);
}

static void draw_wall(t_img *img, int ray_nbr, int t_pix, int b_pix, t_data *data, int wall_h)
{
	int	y;
	int wall_color;

	int textureOffsetX;
	int textureOffsetY;

	int direction;

	direction = get_ray_hit_direction(data->rays[ray_nbr]);

	y = t_pix;
	// Calculate textureOffsetX
	if (data->rays[ray_nbr].was_hit_vertical)
		// Perform offset for the vertical hit
		textureOffsetX = (int)data->rays[ray_nbr].wall_hit_y % TILE_SIZE;
	else
		// Perform offset for the horizontal hit
		textureOffsetX = (int)data->rays[ray_nbr].wall_hit_x % TILE_SIZE;
	while (y < b_pix) // Draw wall
	{
		// Calculate textureOffsetY
		int distanceFromTop = y + (wall_h / 2) - (WIN_HEIGHT / 2);
		textureOffsetY = distanceFromTop * ((float)TEXTURE_SIZE / wall_h);
		wall_color = data->textures[direction][(TEXTURE_SIZE * textureOffsetY) + textureOffsetX];
		my_mlx_pixel_put(img, ray_nbr, y++, wall_color);
	}
}

static void draw_floor_and_ceilling(t_img *img, int ray_nbr, int t_pix, int b_pix, t_data *data)
{
	int y;

	y = b_pix;
	while (y < WIN_HEIGHT) // Draw floor
		my_mlx_pixel_put(img, ray_nbr, y++, data->f_hex);
	y = 0;
	while (y < t_pix) // Draw ceilling
		my_mlx_pixel_put(img, ray_nbr, y++, data->c_hex);
}

void render_projection(t_data *data, t_img *img)
{
	float wall_h;
	float bottom_pixel;
	float top_pixel;
	int ray_idx = 0;
	float corrected_angle;

	while (ray_idx < NUM_RAYS)
	{
		corrected_angle = normalize_angle(data->rays[ray_idx].ray_angle - data->player.rotation_angle);
		data->rays[ray_idx].distance *= cos(corrected_angle);
		wall_h = (TILE_SIZE / data->rays[ray_idx].distance) * ((WIN_WIDTH / 2) / tan(data->player.fov_rd / 2));
		bottom_pixel = (WIN_HEIGHT / 2) + (wall_h / 2);
		top_pixel = (WIN_HEIGHT / 2) - (wall_h / 2);
		if (bottom_pixel > WIN_HEIGHT)
			bottom_pixel = WIN_HEIGHT;
		if (top_pixel < 0)
			top_pixel = 0;
		draw_wall(img, ray_idx, top_pixel, bottom_pixel, data, wall_h);
		draw_floor_and_ceilling(img, ray_idx, top_pixel, bottom_pixel, data);
		ray_idx++;
	}
}
