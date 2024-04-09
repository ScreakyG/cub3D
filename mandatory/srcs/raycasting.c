/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 19:13:49 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/09 00:20:04 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_ray_directions(t_ray *ray)
{
	ray->is_ray_facing_down = 0;
	ray->is_ray_facing_up = 0;
	ray->is_ray_facing_left = 0;
	ray->is_ray_facing_right = 0;
	if (ray->ray_angle > 0 && ray->ray_angle < M_PI)
		ray->is_ray_facing_down = 1;
	ray->is_ray_facing_up = !ray->is_ray_facing_down;
	if (ray->ray_angle < (M_PI / 2) || ray->ray_angle > (1.5 * M_PI))
		ray->is_ray_facing_right = 1;
	ray->is_ray_facing_left = !ray->is_ray_facing_right;
}

float	normalize_angle(float ray_angle)
{
	if (ray_angle > (2 * M_PI))
		ray_angle -= (2 * M_PI);
	if (ray_angle < 0)
		ray_angle += (2 * M_PI);
	return (ray_angle);
}

float	get_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void cast_ray(t_ray *ray, t_data *data)
{
	float width_world = data->width * TILE_SIZE;
	float height_world = data->height * TILE_SIZE;

	init_ray(ray);
	float x_intercept;
	float y_intercept;
	float x_step;
	float y_step;

	////////////////////////////////////
	//////// HORIZONTAL RAYCAST ////////
	////////////////////////////////////

	int		found_horz_wall_hit = false;
	float 	horz_wall_hit_x = 0;
	float 	horz_wall_hit_y = 0;
	int		horz_wall_content = 0;

	// Find the y-coordinate of the closest horizontal grid intersection
	y_intercept = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
	if (ray->is_ray_facing_down)
		y_intercept += TILE_SIZE;

	// Find the x-coordinate of the closest horizontal grid intersection

	x_intercept = data->player.x + (y_intercept - data->player.y) / tan(ray->ray_angle);

	// Calculate the xstep and the ystep

	y_step = TILE_SIZE;
	if (ray->is_ray_facing_up)
		y_step *= -1;

	x_step = TILE_SIZE / tan(ray->ray_angle);
	if (ray->is_ray_facing_left && x_step > 0)
		x_step *= -1;
	if (ray->is_ray_facing_right && x_step < 0)
		x_step *= -1;

	float next_horz_touch_x = x_intercept;
	float next_horz_touch_y = y_intercept;

	// Increment x_step and y_step until we hit a wall

	while (next_horz_touch_x >= 0 && next_horz_touch_x <= width_world && next_horz_touch_y >= 0 && next_horz_touch_y <= height_world) // Peut etre changer pour les vrai dimensions de la map
	{
		float x_to_check = next_horz_touch_x;
		float y_to_check = next_horz_touch_y + (ray->is_ray_facing_up ? -1 : 0);

		if (wall_colision(data, x_to_check, y_to_check))
		{
			horz_wall_hit_x = next_horz_touch_x;
			horz_wall_hit_y = next_horz_touch_y;
			horz_wall_content = get_cell_content(data, x_to_check, y_to_check);//data->map_grid[(int)floor(y_to_check / TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)]; // genere des segfaults
			found_horz_wall_hit = true;
			break ;
		}
		else
		{
			next_horz_touch_x += x_step;
			next_horz_touch_y += y_step;
		}
	}
	////////////////////////////////////
	//////// VERTICAL RAYCAST ////////
	////////////////////////////////////

	int		found_vert_wall_hit = false;
	float 	vert_wall_hit_x = 0;
	float 	vert_wall_hit_y = 0;
	int		vert_wall_content = 0;

	// Find the x-coordinate of the closest vertical grid intersection
	x_intercept = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
	if (ray->is_ray_facing_right)
		x_intercept += TILE_SIZE;

	// Find the y-coordinate of the closest vertical grid intersection

	y_intercept = data->player.y + (x_intercept - data->player.x) * tan(ray->ray_angle);

	// Calculate the xstep and the ystep

	x_step = TILE_SIZE;
	if (ray->is_ray_facing_left)
		x_step *= -1;

	y_step = TILE_SIZE * tan(ray->ray_angle);
	if (ray->is_ray_facing_up && y_step > 0)
		y_step *= -1;
	if (ray->is_ray_facing_down && y_step < 0)
		y_step *= -1;

	float next_vert_touch_x = x_intercept;
	float next_vert_touch_y = y_intercept;

	// Increment x_step and y_step until we hit a wall

	while (next_vert_touch_x >= 0 && next_vert_touch_x <= width_world && next_vert_touch_y >= 0 && next_vert_touch_y <= height_world) // Peut etre changer pour les vrai dimensions de la map
	{
		float x_to_check = next_vert_touch_x + (ray->is_ray_facing_left ? -1 : 0);
		float y_to_check = next_vert_touch_y;

		if (wall_colision(data, x_to_check, y_to_check))
		{
			vert_wall_hit_x = next_vert_touch_x;
			vert_wall_hit_y = next_vert_touch_y;
			vert_wall_content = get_cell_content(data, x_to_check, y_to_check);//data->map_grid[(int)floor(y_to_check / TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)]; // Genere des segfaults.
			found_vert_wall_hit = true;
			break ;
		}
		else
		{
			next_vert_touch_x += x_step;
			next_vert_touch_y += y_step;
		}
	}

	// Calculate horizontal and vertical wall distances and choose the smallest one
	float horz_hit_distance = found_horz_wall_hit ? get_distance(data->player.x, data->player.y, horz_wall_hit_x, horz_wall_hit_y) : INT_MAX;
	float vert_hit_distance = found_vert_wall_hit ? get_distance(data->player.x, data->player.y, vert_wall_hit_x, vert_wall_hit_y) : INT_MAX;
	if (vert_hit_distance < horz_hit_distance)
	{
		ray->distance = vert_hit_distance;
		ray->wall_hit_x = vert_wall_hit_x;
		ray->wall_hit_y = vert_wall_hit_y;
		ray->was_hit_vertical = true;
		ray->hit_content = vert_wall_content;
	}
	else
	{
		ray->distance = horz_hit_distance;
		ray->wall_hit_x = horz_wall_hit_x;
		ray->wall_hit_y = horz_wall_hit_y;
		ray->was_hit_vertical = false;
		ray->hit_content = horz_wall_content;
	}
}

void	cast_all_rays(t_data *data)
{
	int		strip_id;
	float	ray_angle;

	strip_id = 0;
	//ray_angle = data->player.rotation_angle - (data->player.fov_rd / 2);
	while (strip_id < NUM_RAYS)
	{
		ray_angle = data->player.rotation_angle
			+ atan((strip_id - NUM_RAYS / 2) / data->dist_plane);
		data->rays[strip_id].ray_angle = ray_angle;
		cast_ray(&data->rays[strip_id], data);
		strip_id++;
		//ray_angle += (data->player.fov_rd / NUM_RAYS);
	}
}
