/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:01:10 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/09 00:31:57 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	get_map_width(t_data *data)
{
	int	i;
	int	biggest_len;
	int	line_len;

	i = data->idx_map_start;
	biggest_len = 0;
	while (data->map_tab[i] && i < data->idx_map_end)
	{
		line_len = ft_strlen(data->map_tab[i]);
		if (line_len > biggest_len)
			biggest_len = line_len;
		i++;
	}
	data->width = biggest_len;
}

static void	trim_spaces(t_data *data)
{
	int		i;
	char	*trimmed_line;

	i = data->idx_map_start;
	trimmed_line = NULL;
	while (data->map_tab[i] && i < data->idx_map_end)
	{
		trimmed_line = ft_strtrim(data->map_tab[i], " \r\t");
		if (!trimmed_line)
			ft_exit_error("", 1, data);
		free(data->map_tab[i]);
		data->map_tab[i] = trimmed_line;
		i++;
	}
}

static char	*copy_fill(char *src, t_data *data)
{
	int		i;
	char	*new;

	i = 0;
	new = malloc((data->width + 1) * sizeof(char));
	if (!new)
		ft_exit_error("", 1, data);
	while (i < data->width)
	{
		if (i < (int)ft_strlen(src))
		{
			new[i] = src[i];
			if (new[i] == ' ' || new[i] == '\t' || new[i] == '\r')
				new[i] = '1';
		}
		else
			new[i] = '1';
		i++;
	}
	new[i] = '\0';
	return (new);
}

static void	malloc_grid(t_data *data)
{
	int	i;

	i = 0;
	data->height = data->idx_map_end - data->idx_map_start;
	data->map_grid = malloc((data->height + 1) * sizeof(char *));
	if (!data->map_grid)
		ft_exit_error("Error creating map grid", 1, data);
	while (i < data->height)
	{
		data->map_grid[i] = copy_fill(data->map_tab[data->idx_map_start + i],
				data);
		i++;
	}
	data->map_grid[i] = NULL;
}

void	create_map_grid(t_data *data)
{
	trim_spaces(data);
	get_map_width(data);
	malloc_grid(data);
}
