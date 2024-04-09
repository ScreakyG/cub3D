/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 00:20:56 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/09 01:58:02 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error_identifier_value(char *identifier, t_data *data)
{
	printf(RED"No value for identifier : %s\n"RESET, identifier);
	free(identifier);
	ft_exit_error("", 1, data);
}

bool	is_empty(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (true);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\r')
			return (false);
		i++;
	}
	return (true);
}

bool	only_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	tab_len(char **tab)
{
	int	len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

int	get_player_number(t_data *data)
{
	int	y;
	int	x;
	int	count;

	y = 0;
	count = 0;
	if (!data->map_grid)
		return (0);
	while (data->map_grid[y])
	{
		x = 0;
		while (data->map_grid[y][x])
		{
			if (data->map_grid[y][x] == 'N' || data->map_grid[y][x] == 'W'
			|| data->map_grid[y][x] == 'S' || data->map_grid[y][x] == 'E')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}
