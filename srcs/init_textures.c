/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:02:40 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/06 03:36:29 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int *convert_xpm_to_img(t_data *data, char *path)
{
	t_img	temp;
	int		*color_buffer;
	int		*addr;

	temp.addr = NULL;
	temp.img = NULL;
	temp.bpp = 0;
	temp.endian = 0;
	temp.line_length = 0;

	temp.img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, path, &data->tex_size, &data->tex_size);
	if (temp.img == NULL)
		ft_exit_error("Error texture file\n", 1, data);
	addr = (int *)mlx_get_data_addr(temp.img, &temp.bpp, &temp.line_length, &temp.endian);
	color_buffer = malloc(sizeof(int) * (data->tex_size * data->tex_size));
	if (!color_buffer)
		ft_exit_error("Error texture file\n", 1, data);
	for (int y = 0; y < data->tex_size; y++)
		for(int x = 0; x < data->tex_size; x++)
			color_buffer[(y * data->tex_size) + x] = addr[(y * data->tex_size) + x];
	mlx_destroy_image(data->mlx.mlx_ptr, temp.img);
	return (color_buffer);
}

static void init_walls(t_data *data)
{
	data->textures = ft_calloc(5, sizeof(int *));
	if (!data->textures)
		ft_exit_error("Error texture malloc\n", 1, data);
	data->textures[NORTH] = convert_xpm_to_img(data, data->no);
	data->textures[SOUTH] = convert_xpm_to_img(data, data->so);
	data->textures[EAST] = convert_xpm_to_img(data, data->ea);
	data->textures[WEST] = convert_xpm_to_img(data, data->we);
}


int rgb_to_hex(int red, int green, int blue)
{
    return ((red << 16) + (green << 8) + blue);
}

void init_floor_ceiling_colors(t_data *data)
{
	char **splitted_floor;
	char **splitted_ceiling;

	int	f_hex;
	int	c_hex;

	splitted_floor = ft_split(data->f, ',');
	if (!splitted_floor)
		ft_exit_error("Error malloc floor rgb numbers", 1, data);
	f_hex = rgb_to_hex(ft_atoi(splitted_floor[0]), ft_atoi(splitted_floor[1]), ft_atoi(splitted_floor[2]));
	free_strs(splitted_floor);
	splitted_ceiling = ft_split(data->c, ',');
	if (!splitted_ceiling)
		ft_exit_error("Error malloc ceiling rgb numbers", 1, data);
	c_hex = rgb_to_hex(ft_atoi(splitted_ceiling[0]), ft_atoi(splitted_ceiling[1]), ft_atoi(splitted_ceiling[2]));
	free_strs(splitted_ceiling);
	data->c_hex = c_hex;
	data->f_hex = f_hex;
}

void init_textures(t_data *data)
{
	init_walls(data);
	init_floor_ceiling_colors(data);
}
