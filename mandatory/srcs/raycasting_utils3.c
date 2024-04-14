/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:43:14 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/14 19:44:14 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	get_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float	normalize_angle(float ray_angle)
{
	if (ray_angle > (2 * M_PI))
		ray_angle -= (2 * M_PI);
	if (ray_angle < 0)
		ray_angle += (2 * M_PI);
	return (ray_angle);
}

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
