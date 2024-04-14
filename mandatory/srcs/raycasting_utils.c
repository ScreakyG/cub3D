/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:38:58 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/14 19:42:00 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	fill_ray_values(t_ray *ray, t_ray_inter *r, bool vert_hit)
{
	ray->distance = r->distance;
	ray->wall_hit_x = r->wall_hit_x;
	ray->wall_hit_y = r->wall_hit_y;
	ray->hit_content = r->wall_content;
	ray->was_hit_vertical = vert_hit;
}

void	fill_values(t_data *data, t_ray_inter *r)
{
	r->wall_hit_x = r->next_touch_x;
	r->wall_hit_y = r->next_touch_y;
	r->wall_content = get_cell_content(data, r->x_to_check, r->y_to_check);
	r->found_wall_hit = true;
}

int	pixel_force(t_ray *ray, bool horz)
{
	if (horz == true)
	{
		if (ray->is_ray_facing_up)
			return (-1);
		else
			return (0);
	}
	else if (horz == false)
	{
		if (ray->is_ray_facing_left)
			return (-1);
		else
			return (0);
	}
	return (0);
}

void	init_ray_inter(t_ray_inter *r)
{
	r->found_wall_hit = false;
	r->wall_hit_x = 0;
	r->wall_hit_y = 0;
	r->wall_content = 0;
}

void	get_intercepts(t_data *data, t_ray *ray, t_ray_inter *r, int horz)
{
	if (horz == 1)
	{
		r->y_intercept = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
		if (ray->is_ray_facing_down)
			r->y_intercept += TILE_SIZE;
		r->x_intercept = data->player.x
			+ (r->y_intercept - data->player.y) / tan(ray->ray_angle);
	}
	else if (horz == 0)
	{
		r->x_intercept = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
		if (ray->is_ray_facing_right)
			r->x_intercept += TILE_SIZE;
		r->y_intercept = data->player.y
			+ (r->x_intercept - data->player.x) * tan(ray->ray_angle);
	}
}
