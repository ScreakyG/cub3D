/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 19:13:49 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/14 19:47:52 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_ray_inter	get_h_inter(t_data *data, t_ray *ray)
{
	t_ray_inter	h;

	init_ray_inter(&h);
	get_intercepts(data, ray, &h, 1);
	get_x_y_step(ray, &h, 1);
	h.next_touch_x = h.x_intercept;
	h.next_touch_y = h.y_intercept;
	while (h.next_touch_x >= 0 && h.next_touch_x <= data->width_world
		&& h.next_touch_y >= 0 && h.next_touch_y <= data->height_world)
	{
		h.x_to_check = h.next_touch_x;
		h.y_to_check = h.next_touch_y + pixel_force(ray, true);
		if (wall_colision(data, h.x_to_check, h.y_to_check))
		{
			fill_values(data, &h);
			break ;
		}
		else
		{
			h.next_touch_x += h.x_step;
			h.next_touch_y += h.y_step;
		}
	}
	return (h);
}

t_ray_inter	get_v_inter(t_data *data, t_ray *ray)
{
	t_ray_inter	v;

	init_ray_inter(&v);
	get_intercepts(data, ray, &v, 0);
	get_x_y_step(ray, &v, 0);
	v.next_touch_x = v.x_intercept;
	v.next_touch_y = v.y_intercept;
	while (v.next_touch_x >= 0 && v.next_touch_x <= data->width_world
		&& v.next_touch_y >= 0 && v.next_touch_y <= data->height_world)
	{
		v.x_to_check = v.next_touch_x + pixel_force(ray, false);
		v.y_to_check = v.next_touch_y;
		if (wall_colision(data, v.x_to_check, v.y_to_check))
		{
			fill_values(data, &v);
			break ;
		}
		else
		{
			v.next_touch_x += v.x_step;
			v.next_touch_y += v.y_step;
		}
	}
	return (v);
}

void	cast_ray(t_ray *ray, t_data *data)
{
	t_ray_inter	h;
	t_ray_inter	v;

	init_ray(ray);
	h = get_h_inter(data, ray);
	v = get_v_inter(data, ray);
	if (h.found_wall_hit)
		h.distance = get_distance(data->player.x,
				data->player.y, h.wall_hit_x, h.wall_hit_y);
	else
		h.distance = INT_MAX;
	if (v.found_wall_hit)
		v.distance = get_distance(data->player.x,
				data->player.y, v.wall_hit_x, v.wall_hit_y);
	else
		v.distance = INT_MAX;
	if (v.distance < h.distance)
		fill_ray_values(ray, &v, true);
	else
		fill_ray_values(ray, &h, false);
}

void	cast_all_rays(t_data *data)
{
	int		strip_id;
	float	ray_angle;

	strip_id = 0;
	while (strip_id < NUM_RAYS)
	{
		ray_angle = data->player.rotation_angle
			+ atan((strip_id - NUM_RAYS / 2) / data->dist_plane);
		data->rays[strip_id].ray_angle = ray_angle;
		cast_ray(&data->rays[strip_id], data);
		strip_id++;
	}
}
