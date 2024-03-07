/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:30:34 by fgonzale          #+#    #+#             */
/*   Updated: 2024/03/07 19:45:34 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool characters_check(char *str)
{
	int	i;
	int	j;
	bool found;
	char charset[] = "01NSEW \t\r";

	i = 0;
	while (str[i])
	{
		found = false;
		j = 0;
		while (charset[j])
		{
			if (str[i] == charset[j])
			{
				found = true;
				break ;
			}
			j++;
		}
		if (found == true)
		{
			i++;
			continue ;
		}
		return (false);
	}
	return (true);
}

static void get_map_dimensions(t_data *data, int start)
{
	int	idx;
	int	line_len;

	idx = start;
	line_len = 0;
	data->height = 0;
	data->width = 0;

	while (data->map_tab[idx])
	{
		line_len = ft_strlen(data->map_tab[idx]);
		if (line_len > data->width)
			data->width = line_len;
		idx++;
	}
	data->height = idx - start;
}

void parse_map(t_data *data)
{
	int	i;
	//int	idx_map_start;

	int	j;

	i = data->idx_map;
	j = 0;
	while (data->map_tab[i] && data->map_tab[i][j] == '\0')
		i++;
	if (data->map_tab[i] == NULL)
		ft_exit_error("There is no map", 1, data); // Si il n'y a rien apres les identifiants.
	//idx_map_start = i; // Pour recuperer le debut de la partie map.
	get_map_dimensions(data, i);
	printf("Height = %d, width = %d\n", data->height, data->width); // Test dimensions.
	while (data->map_tab[i])
	{
		if (characters_check(data->map_tab[i]) == false)
			ft_exit_error("Invalid map", 1, data);
		i++;
	}
}
