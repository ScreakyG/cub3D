/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:02:40 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/07 02:12:29 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int *convert_xpm_to_img(t_data *data, char *path, t_texture *texture)
{
	t_img	temp;
	int		*color_buffer;
	int		*addr;

	temp.addr = NULL;
	temp.img = NULL;
	temp.bpp = 0;
	temp.endian = 0;
	temp.line_length = 0;

	temp.img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, path, &texture->width, &texture->height);
	if (temp.img == NULL)
		ft_exit_error("Error texture file\n", 1, data);
	addr = (int *)mlx_get_data_addr(temp.img, &temp.bpp, &temp.line_length, &temp.endian);

	printf("File = %s, Texture height = %d\n", path, texture->height);
	printf("File = %s, Texture width = %d\n", path, texture->width);

	color_buffer = malloc(sizeof(int) * (texture->width * texture->height));
	if (!color_buffer)
		ft_exit_error("Error texture file\n", 1, data);
	for (int y = 0; y < texture->height; y++)
		for(int x = 0; x < texture->width; x++)
			color_buffer[(y * texture->width) + x] = addr[(y * texture->width) + x];
	mlx_destroy_image(data->mlx.mlx_ptr, temp.img);
	return (color_buffer);
}

static void init_walls(t_data *data)
{
	data->textures = ft_calloc(5, sizeof(t_texture));
	if (!data->textures)
		ft_exit_error("Error texture malloc\n", 1, data);
	data->textures[NORTH].color_buffer = convert_xpm_to_img(data, data->no, &data->textures[NORTH]);
	data->textures[SOUTH].color_buffer = convert_xpm_to_img(data, data->so, &data->textures[SOUTH]);
	data->textures[EAST].color_buffer = convert_xpm_to_img(data, data->ea, &data->textures[EAST]);
	data->textures[WEST].color_buffer = convert_xpm_to_img(data, data->we, &data->textures[WEST]);
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
