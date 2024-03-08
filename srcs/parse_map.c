/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:30:34 by fgonzale          #+#    #+#             */
/*   Updated: 2024/03/08 02:54:40 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool characters_check(char *str)
{
	int	i;
	int	j;
	bool found;
	char charset[] = "01NWSE \t\r";

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

static bool verify_top_line(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (false);
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'))
			i++;
		if (str[i] != '1')
			return (false);
		i++;
	}
	return (true);
}

static bool verify_left_side(t_data *data)
{
	int	i;
	int	j;

	i = data->idx_map + 1;
	while (data->map_tab[i])
	{
		j = 0;
		while (data->map_tab[i][j] && (data->map_tab[i][j] == ' ' || data->map_tab[i][j] == '\t' || data->map_tab[i][j] == '\r'))
			j++;
		if (data->map_tab[i][j] != '1')
			return (false);
		i++;
	}
	return (true);
}

void skip_white_lines(t_data *data)
{
	int	i;
	int	j;

	i = data->idx_map;
	while (data->map_tab[i])
	{
		j = 0;
		if (data->map_tab[i][j] == '\0')
			i++;
		else
		{
			while (data->map_tab[i] && (data->map_tab[i][j] == ' ' || data->map_tab[i][j] == '\t'|| data->map_tab[i][j] == '\r'))
				j++;
			if (data->map_tab[i][j] != '\0')
				break ;
			i++;
		}
	}
	if (data->map_tab[i] == NULL)
		ft_exit_error("There is no map", 1, data);
	data->idx_map = i;
}



void check_if_closed_map(t_data *data)
{
	//verifier si la map fait au moins 3 lignes.
	if (verify_top_line(data->map_tab[data->idx_map]) == false)
		ft_exit_error("Top of map not closed", 1, data);
	if (verify_left_side(data) == false)
		ft_exit_error("Sides not closed", 1, data);
}

void parse_map(t_data *data)
{
	int	i;

	skip_white_lines(data);
	i = data->idx_map;
	while (data->map_tab[i])
	{
		if (characters_check(data->map_tab[i]) == false)
			ft_exit_error("Invalid characters in map", 1, data);
		i++;
	}
	check_if_closed_map(data);
}
