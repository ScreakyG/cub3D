/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 00:18:08 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/14 19:48:14 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_x_y_step(t_ray *ray, t_ray_inter *r, int horz)
{
	if (horz == 1)
	{
		r->y_step = TILE_SIZE;
		if (ray->is_ray_facing_up)
			r->y_step *= -1;
		r->x_step = TILE_SIZE / tan(ray->ray_angle);
		if (ray->is_ray_facing_left && r->x_step > 0)
			r->x_step *= -1;
		if (ray->is_ray_facing_right && r->x_step < 0)
			r->x_step *= -1;
	}
	else if (horz == 0)
	{
		r->x_step = TILE_SIZE;
		if (ray->is_ray_facing_left)
			r->x_step *= -1;
		r->y_step = TILE_SIZE * tan(ray->ray_angle);
		if (ray->is_ray_facing_up && r->y_step > 0)
			r->y_step *= -1;
		if (ray->is_ray_facing_down && r->y_step < 0)
			r->y_step *= -1;
	}
}

void	print_debug_rays(t_ray *ray)
{
	printf("Ray angle = %f\n", ray->ray_angle);
	printf("Wall hit x = %f\n", ray->wall_hit_x);
	printf("Wall hit y = %f\n", ray->wall_hit_y);
	printf("Wall hit x_grid = %d\n", (int)floor(ray->wall_hit_x / TILE_SIZE));
	printf("Wall hit y_grid = %d\n", (int)floor(ray->wall_hit_y / TILE_SIZE));
	printf("Hit content = %d\n", ray->hit_content);
	printf("Vertical hit = %d\n", ray->was_hit_vertical);
	printf("Distance = %f\n", ray->distance);
	printf("Hit content = %d\n", ray->hit_content);
}

void	init_ray(t_ray *ray)
{
	ray->ray_angle = normalize_angle(ray->ray_angle);
	init_ray_directions(ray);
	ray->wall_hit_x = 0;
	ray->wall_hit_y = 0;
	ray->distance = 0;
	ray->was_hit_vertical = false;
	ray->hit_content = 0;
}

int	get_cell_content(t_data *data, float x, float y)
{
	int	y_grid;
	int	x_grid;

	if (x < 0 || y < 0)
		return ('1');
	y_grid = floor(y / TILE_SIZE);
	x_grid = floor (x / TILE_SIZE);
	if (data->map_grid[y_grid] && data->map_grid[y_grid][x_grid])
		return (data->map_grid[y_grid][x_grid]);
	else
		return ('1');
}
