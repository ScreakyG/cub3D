/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:23:11 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/08 05:12:53 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	get_starting_direction(char **map_grid)
{
	int	x;
	int	y;

	y = 0;
	while (map_grid[y])
	{
		x = 0;
		while (map_grid[y][x])
		{
			if (map_grid[y][x] == 'N' || map_grid[y][x] == 'S' ||
			map_grid[y][x] == 'W' || map_grid[y][x] == 'E')
				return (map_grid[y][x]);
			x++;
		}
		y++;
	}
	return ('\0');
}

static float	get_start_angle(t_data *data)
{
	char	c;

	c = get_starting_direction(data->map_grid);
	if (c == 'S')
		return (M_PI / 2);
	else if (c == 'E')
		return (2 * M_PI);
	else if (c == 'W')
		return (M_PI);
	else if (c == 'N')
		return ((3 * M_PI) / 2);
	return (0);
}

static void	remove_position_in_grid(char **map_grid)
{
	int	x;
	int	y;

	y = 0;
	while (map_grid[y])
	{
		x = 0;
		while (map_grid[y][x])
		{
			if (map_grid[y][x] == 'N' || map_grid[y][x] == 'S' ||
			map_grid[y][x] == 'W' || map_grid[y][x] == 'E')
				map_grid[y][x] = '0';
			x++;
		}
		y++;
	}
	return ;
}

void	init_player(t_data *data)
{
	data->player.fov_rd = FOV * (M_PI / 180);
	data->dist_plane = (WIN_WIDTH / 2) / tan(data->player.fov_rd / 2);
	data->map.player_pos_x = get_player_pos(data, 'x');
	data->map.player_pos_y = get_player_pos(data, 'y');
	data->player.x = data->map.player_pos_x * TILE_SIZE;
	data->player.y = data->map.player_pos_y * TILE_SIZE;
	data->player.width = 10;
	data->player.height = 10;
	data->player.side_direction = 0;
	data->player.walk_direction = 0;
	data->player.rotation_angle = get_start_angle(data);
	data->player.walk_speed = 2;
	data->player.turn_speed = 2 * (M_PI / 180);
	remove_position_in_grid(data->map_grid);
}
