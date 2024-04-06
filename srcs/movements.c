/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 02:38:47 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/06 21:25:30 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool wall_colision(t_data *data, float x_step , float y_step)
{
	float x_world = data->width * TILE_SIZE;
	float y_world = data->height * TILE_SIZE;
	int	x_grid;
	int y_grid;

	if (x_step < 0 || x_step > x_world || y_step < 0 || y_step > y_world)
		return (true);
	x_grid = floor(x_step / TILE_SIZE);
	y_grid = floor(y_step / TILE_SIZE);
	if (y_grid >= data->height || x_grid >= data->width)
		return (true);
	if (data->map_grid[y_grid][x_grid] == '1')
		return (true);
	else
		return (false);
}

static bool movement_colision(t_data *data, float move_x, float move_y)
{
	int	x_grid;
	int y_grid;

	if (move_x < 0 || move_y < 0)
		return (true);
	x_grid = floor(move_x / TILE_SIZE);
	y_grid = floor(move_y / TILE_SIZE);
	if (x_grid >= data->width || y_grid >= data->height)
		return (true);
	if (data->map_grid[y_grid][x_grid] != '1' && (data->map_grid[y_grid][(int)data->player.x / TILE_SIZE] != '1' && data->map_grid[(int)data->player.y / TILE_SIZE][x_grid] != '1'))
		return (false);
	else
		return (true);
}

void movements(t_data *data)
{
	float move_step;
	float move_x;
	float move_y;

	move_x = data->player.x;
	move_y = data->player.y;
	data->player.rotation_angle += data->player.rotation_direction * data->player.turn_speed;
	data->player.rotation_angle = normalize_angle(data->player.rotation_angle); //May remove
	if (data->player.walk_direction == 1 || data->player.walk_direction == -1)
	{
		move_step = data->player.walk_direction * data->player.walk_speed;
		move_x = data->player.x + cos(data->player.rotation_angle) * move_step;
		move_y = data->player.y + sin(data->player.rotation_angle) * move_step;
	}
	if (data->player.side_direction == 1)
	{
		move_x = data->player.x + -sin(data->player.rotation_angle) * data->player.walk_speed;
		move_y = data->player.y + cos(data->player.rotation_angle) * data->player.walk_speed;
	}
	if (data->player.side_direction == -1)
	{
		move_x = data->player.x + sin(data->player.rotation_angle) * data->player.walk_speed;
		move_y = data->player.y + -cos(data->player.rotation_angle) * data->player.walk_speed;
	}
	if (!movement_colision(data, move_x, move_y))
	{
		data->player.x = move_x;
		data->player.y = move_y;
	}
}
