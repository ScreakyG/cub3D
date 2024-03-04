/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:30:34 by fgonzale          #+#    #+#             */
/*   Updated: 2024/03/04 22:04:04 by fgonzale         ###   ########.fr       */
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
		ft_exit_error("Make sure you have a map after identifiers", 1, data); // Si il n'y a rien apres les identifiants.
	//idx_map_start = i; // Pour recuperer le debut de la partie map.
	while (data->map_tab[i])
	{
		if (characters_check(data->map_tab[i]) == false)
			ft_exit_error("Invalid character in map", 1, data);
		i++;
	}
}
