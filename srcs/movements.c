/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 02:38:47 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/01 03:55:18 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool wall_colision(t_data *data, float x_step , float y_step)
{
	int	x;
	int y;

	x = floor(x_step / TILE_SIZE);
	y = floor(y_step / TILE_SIZE);
	if (x_step < 0 || x_step > WIN_WIDTH || y_step < 0 || y_step > WIN_HEIGHT)
		return (true);
	if (data->map_grid[y][x] == '1')
		return (true);
	else
		return (false);
}

void movements(t_data *data)
{
	float move_step;
	float move_x;
	float move_y;

	move_x = data->player.x;
	move_y = data->player.y;
	data->player.rotation_angle += data->player.rotation_direction * data->player.turn_speed;

	if (data->player.walk_direction == 1 || data->player.walk_direction == -1)
	{
		move_step = data->player.walk_direction * data->player.walk_speed;
		move_x = data->player.x + cos(data->player.rotation_angle) * move_step;
		move_y = data->player.y + sin(data->player.rotation_angle) * move_step;
	}
	else if (data->player.side_direction == 1 || data->player.side_direction == -1)
	{
		move_step = data->player.side_direction * data->player.walk_speed;
		move_x = data->player.x + sin(data->player.rotation_angle) * move_step;
		move_y = data->player.y + cos(data->player.rotation_angle) * move_step;
	}
	//Check collisions
	if (!wall_colision(data, move_x, move_y))
	{
		data->player.x = move_x;
		data->player.y = move_y;
	}

}
