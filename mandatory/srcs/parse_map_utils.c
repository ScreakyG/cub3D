/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 00:10:59 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/09 00:15:45 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	skip_white_lines(t_data *data)
{
	int	i;
	int	j;

	i = data->idx_map_start;
	while (data->map_tab[i])
	{
		j = 0;
		if (data->map_tab[i][j] == '\0')
			i++;
		else
		{
			while (data->map_tab[i] && (data->map_tab[i][j] == ' '
				|| data->map_tab[i][j] == '\t' || data->map_tab[i][j] == '\r'))
				j++;
			if (data->map_tab[i][j] != '\0')
				break ;
			i++;
		}
	}
	if (data->map_tab[i] == NULL)
		ft_exit_error("There is no map", 1, data);
	data->idx_map_start = i;
}

void	get_map_end_idx(t_data *data)
{
	int	end;
	int	j;

	end = 0;
	while (data->map_tab[data->idx_map_start + end])
		end++;
	end = data->idx_map_start + end - 1;
	while (data->map_tab[end])
	{
		j = 0;
		while (data->map_tab[end][j] && (data->map_tab[end][j] == ' '
			|| data->map_tab[end][j] == '\t' || data->map_tab[end][j] == '\r'))
			j++;
		if (data->map_tab[end][j] != '\0')
			break ;
		end--;
	}
	data->idx_map_end = end + 1;
}

bool	verify_right_side(t_data *data)
{
	int	i;
	int	j;

	i = data->idx_map_start + 1;
	while (data->map_tab[i] && i < data->idx_map_end)
	{
		j = ft_strlen(data->map_tab[i]);
		j--;
		while (data->map_tab[i][j] && (data->map_tab[i][j] == ' '
			|| data->map_tab[i][j] == '\t' || data->map_tab[i][j] == '\r'))
			j--;
		if (j == str_len_skip_ws(data->map_tab[i]))
			return (false);
		if (data->map_tab[i][j] != '1')
			return (false);
		i++;
	}
	return (true);
}

bool	verify_left_side(t_data *data)
{
	int	i;
	int	j;

	i = data->idx_map_start + 1;
	while (data->map_tab[i] && i < data->idx_map_end)
	{
		j = 0;
		while (data->map_tab[i][j] && (data->map_tab[i][j] == ' '
			|| data->map_tab[i][j] == '\t' || data->map_tab[i][j] == '\r'))
			j++;
		if (data->map_tab[i][j] != '1')
			return (false);
		i++;
	}
	return (true);
}
