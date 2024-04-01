/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 19:13:49 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/01 22:15:58 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_ray_directions(t_ray *ray)
{
	ray->is_ray_facing_down = 0;
	ray->is_ray_facing_up = 0;
	ray->is_ray_facing_left = 0;
	ray->is_ray_facing_right = 0;

	if (ray->ray_angle > 0 && ray->ray_angle < M_PI)
		ray->is_ray_facing_down = 1;
	if (ray->ray_angle > M_PI && ray->ray_angle < (2 * M_PI))
		ray->is_ray_facing_up = 1;
	if (ray->ray_angle < (M_PI / 2) || ray->ray_angle > (1.5 * M_PI))
		ray->is_ray_facing_right = 1;
	if (ray->ray_angle > (M_PI / 2) || ray->ray_angle < (1.5 * M_PI))
		ray->is_ray_facing_down = 1;
}

float normalize_angle(float ray_angle)
{
	if (ray_angle > (2 * M_PI))
		ray_angle -= (2 * M_PI);
	if (ray_angle < 0)
		ray_angle += (2 * M_PI);
	return ray_angle;
}

// float get_distance(float x1, float y1, float x2, float y2)
// {
// 	return (sqrt(((x2 - x1) * (x2 - x1))) + ((y2 - y1) * (y2 - y1)));
// }

// bool map_has_wall_hat(float x, float y, t_data *data)
// {
// 	if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
// 		return (true);
// 	if (data->map_grid[(int)floor(y / TILE_SIZE)][(int)floor(x / TILE_SIZE)] == '1')
// 		return (true);
// 	else
// 		return (false);
// }

void init_ray(t_ray *ray)
{
	init_ray_directions(ray);
	ray->ray_angle = normalize_angle(ray->ray_angle);
	ray->wall_hit_x = 0;
	ray->wall_hit_y = 0;
	ray->distance = 0;
	ray->was_hit_vertical = false;
	ray->hit_content = 0;
}

// void get_horizontal_inter(t_ray *ray, t_data *data)
// {
// 	float x_intercept;
// 	float y_intercept;
// 	float x_step;
// 	float y_step;

// 	y_step = TILE_SIZE;
// 	x_step = TILE_SIZE / tan(ray->ray_angle);
// }

void cast_ray(t_ray *ray, t_data *data)
{
	init_ray(ray);
	(void)data;
	//get_horizontal_inter(ray, data);
}

void cast_all_rays(t_data *data)
{
	int	strip_id;
	float ray_angle;

	printf("%f\n", data->player.rotation_angle);
	strip_id = 0;
	ray_angle = data->player.rotation_angle - (data->player.fov_rd / 2);
	data->rays = malloc(sizeof(t_ray) * NUM_RAYS);
	if (!data->rays)
		ft_exit_error("Error with rays malloc", 1, data);
	while (strip_id < 1) //NUM_RAYS)
	{
		data->rays[strip_id].ray_angle = ray_angle;
		cast_ray(&data->rays[strip_id], data);
		strip_id++;
		ray_angle += (WIN_WIDTH / NUM_RAYS);
	}
}
