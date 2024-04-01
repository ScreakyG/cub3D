/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 21:36:02 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/01 02:05:01 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	if (x < 0)
		return ;
	else if (x >= WIN_WIDTH)
		return ;
	if (y < 0)
		return ;
	else if (y >= WIN_HEIGHT)
		return ;

	dst = img->addr + (y * img->line_length + x *(img->bpp / 8));
	*(unsigned int*)dst = color;
}

void render_background(t_data *data, t_img *img)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		if (y < WIN_HEIGHT / 2)
		{
			while (x++ < WIN_WIDTH)
				my_mlx_pixel_put(img, x, y, data->c_hex);
		}
		else if (y > WIN_HEIGHT / 2)
		{
			while (x++ < WIN_WIDTH)
				my_mlx_pixel_put(img, x, y, data->f_hex);
		}
		y++;
	}
}

static void render_cells(t_img *img, int pos_x, int pos_y, int color, float scale_factor)
{
	int	i;
	int	j;

	i = 0;
	while (i < scale_factor)
	{
		j = 0;
		while (j < scale_factor)
		{
			my_mlx_pixel_put(img, pos_x + j, pos_y + i, color);
			j++;
		}
		i++;
	}
}

void render_minimap(t_data *data, t_img *img)
{
	int	x;
	int	y;
	int	tile_x;
	int tile_y;
	int	cell_color;

	//float scale_factor = fmin(WIN_WIDTH / (float)(data->width * TILE_SIZE), WIN_HEIGHT / (float)(data->height * TILE_SIZE)) * MINIMAP_SCALE;
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			tile_x = x * TILE_SIZE * MINIMAP_SCALE;
			tile_y = y * TILE_SIZE * MINIMAP_SCALE;
			if (data->map_grid[y][x] == '1')
				cell_color = 0x000000;
			else if (data->map_grid[y][x] == '0')
				cell_color = 0xFFFFFF;
			render_cells(img, tile_x, tile_y, cell_color, TILE_SIZE * MINIMAP_SCALE);
			x++;
		}
		y++;
	}
}

static void draw_line(t_img *img, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */

    while (1) {
        my_mlx_pixel_put(img, x0, y0, color); /* draw pixel at (x0, y0) */
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void render_player(t_data *data, t_img *img)
{
	int	color;

	color = 0xFE0000;
	int player_x_pix;
	int player_y_pix;
	int	end_x;
	int	end_y;

	player_x_pix = data->player.x * MINIMAP_SCALE;
	player_y_pix = data->player.y * MINIMAP_SCALE;
	render_cells(img, player_x_pix, player_y_pix, color, data->player.width * MINIMAP_SCALE);

	end_x = MINIMAP_SCALE * data->player.x + cos(data->player.rotation_angle) * (40 * MINIMAP_SCALE);
	end_y = MINIMAP_SCALE * data->player.y + sin(data->player.rotation_angle) * (40 * MINIMAP_SCALE);
	draw_line(img, player_x_pix, player_y_pix, end_x, end_y, color);

}
