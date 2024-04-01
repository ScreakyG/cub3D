/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:02:40 by fgonzale          #+#    #+#             */
/*   Updated: 2024/03/25 22:38:25 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// static void init_walls(t_data *data)
// {
// 	// Voir mcombeau
// 	// Creer une structure t_img
// }


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
	//init_walls(data);
	init_floor_ceiling_colors(data);
}
