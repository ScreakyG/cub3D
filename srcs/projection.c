/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 23:58:22 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/03 00:00:24 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void draw_wall(t_img *img, int ray_nbr, int t_pix, int b_pix, int color)
{
	while (t_pix < b_pix)
		my_mlx_pixel_put(img, ray_nbr, t_pix++, color);
}

void render_projection(t_data *data, t_img *img)
{
	float wall_h;
	float b_pix;
	float t_pix;
	int i = 0;
	int color;
	float corrected_angle;

	while (i < NUM_RAYS)
	{
		corrected_angle = normalize_angle(data->rays[i].ray_angle - data->player.rotation_angle);
		data->rays[i].distance *= cos(corrected_angle);
		wall_h = (TILE_SIZE / data->rays[i].distance) * ((WIN_WIDTH / 2) / tan(data->player.fov_rd / 2));
		b_pix = (WIN_HEIGHT / 2) + (wall_h / 2);
		t_pix = (WIN_HEIGHT / 2) - (wall_h / 2);
		if (b_pix > WIN_HEIGHT)
			b_pix = WIN_HEIGHT;
		if (t_pix < 0)
			t_pix = 0;
		if (data->rays[i].was_hit_vertical == 1)
			color = 0xB5B5B5FF;
		else
			color = 0xF5F5F5FF;
		draw_wall(img, i, t_pix, b_pix, color);
		i++;
	}
}
