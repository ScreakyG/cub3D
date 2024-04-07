/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 21:36:02 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/07 06:33:02 by fgonzale         ###   ########.fr       */
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

static void render_grid_cells(t_img *img, int pos_x, int pos_y, int color, float x_scale, float y_scale)
{
	int	y;
	int	x;

	y = 0;
	while (y < y_scale)
	{
		x = 0;
		while (x < x_scale)
		{
			my_mlx_pixel_put(img, pos_x + x, pos_y + y, color);
			x++;
		}
		y++;
	}
}

void render_minimap(t_data *data, t_img *img)
{
	int	x;
	int	y;
	int	tile_x;
	int tile_y;
	int	cell_color;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			tile_x = x * ((WIN_WIDTH / data->width) * MINIMAP_SCALE);
			tile_y = y * ((WIN_HEIGHT / data->height) * MINIMAP_SCALE);
			if (data->map_grid[y][x] == '1')
				cell_color = 0x000000;
			else if (data->map_grid[y][x] == '0')
				cell_color = 0xFFFFFF;
			render_grid_cells(img, tile_x, tile_y, cell_color, ((WIN_WIDTH / data->width) * MINIMAP_SCALE), ((WIN_HEIGHT / data->height) * MINIMAP_SCALE));
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
	float player_x_pix;
	float player_y_pix;
	float	end_x;
	float	end_y;


	float	x_cell_scale = WIN_WIDTH / data->width;
	float y_cell_scale = WIN_HEIGHT / data->height;

	float player_pos_x = data->player.x / TILE_SIZE;
	float player_pos_y = data->player.y / TILE_SIZE;

	player_x_pix = ((player_pos_x * x_cell_scale)) * MINIMAP_SCALE;
	player_y_pix = ((player_pos_y * y_cell_scale)) * MINIMAP_SCALE;

	render_grid_cells(img, player_x_pix - (data->player.width / 2 * MINIMAP_SCALE), player_y_pix - (data->player.height / 2 * MINIMAP_SCALE), 0xFE0000, 10 * MINIMAP_SCALE, 10 * MINIMAP_SCALE);


	end_x = player_x_pix + cos(data->player.rotation_angle) * (40 * MINIMAP_SCALE);
	end_y = player_y_pix + sin(data->player.rotation_angle) * (40 * MINIMAP_SCALE);
	draw_line(img, player_x_pix, player_y_pix, end_x, end_y, 0xF5F5F5FF);

}

void render_rays(t_data *data, t_img *img)
{
   // Convertir la position du joueur en coordonnées de la minimap
    float player_x_pix = (data->player.x / TILE_SIZE) * (WIN_WIDTH / data->width) * MINIMAP_SCALE;
    float player_y_pix = (data->player.y / TILE_SIZE) * (WIN_HEIGHT / data->height) * MINIMAP_SCALE;

	//float scale_factor_x = (WIN_WIDTH / data->width) * MINIMAP_SCALE / TILE_SIZE;
   // float scale_factor_y = (WIN_HEIGHT / data->height) * MINIMAP_SCALE / TILE_SIZE;

    // Calculer la direction de la ligne à 30 degrés par rapport à l'angle du joueur
	int	i = 0;
	float ray_angle = 0;
	float ray_dir_x = 0;
    float ray_dir_y = 0;
	while (i < NUM_RAYS)
	{
    	ray_angle = data->rays[i].ray_angle;
    	ray_dir_x = cos(ray_angle);
    	ray_dir_y = sin(ray_angle);

    // Définir une longueur arbitraire pour la ligne
   		 float line_length = data->rays[i].distance;


    // Ajuster les coordonnées de fin de la ligne à l'échelle de la minimap
    	float end_x = player_x_pix + ray_dir_x * (line_length * MINIMAP_SCALE);
    	float end_y = player_y_pix + ray_dir_y * (line_length * MINIMAP_SCALE);

    // Dessiner la ligne à 30 degrés
    	draw_line(img, player_x_pix, player_y_pix, end_x, end_y, 0xFE0000);
		i++;
	}
}
