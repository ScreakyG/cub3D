/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:30:34 by fgonzale          #+#    #+#             */
/*   Updated: 2024/03/08 05:18:10 by fgonzale         ###   ########.fr       */
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
	int	wall_nb;

	i = 0;
	wall_nb = 0;
	if (!str || !str[i])
		return (false);
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'))
			i++;
		if (str[i] == '1')
			wall_nb++;
		else if (str[i] == '\0' && wall_nb > 1)
			return (true);
		else if (str[i] != '1')
			return (false);
		i++;
	}
	if (wall_nb > 1)
		return (true);
	else
		return (false);
}

static bool verify_left_side(t_data *data)
{
	int	i;
	int	j;

	i = data->idx_map_start + 1;
	while (data->map_tab[i] && i < data->idx_map_end)
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

static bool verify_right_side(t_data *data)
{
	int	i;
	int	j;

	i = data->idx_map_start + 1;
	while (data->map_tab[i] && i < data->idx_map_end)
	{
		j = ft_strlen(data->map_tab[i]);
		j--;
		while (data->map_tab[i][j] && (data->map_tab[i][j] == ' ' || data->map_tab[i][j] == '\t' || data->map_tab[i][j] == '\r'))
			j--;
		if (j == str_len_skip_ws(data->map_tab[i]))
			return (false);
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

	i = data->idx_map_start;
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
	data->idx_map_start = i;
}



void check_if_closed_map(t_data *data)
{
	if (data->idx_map_end - data->idx_map_start < 3)//verifier si la map fait au moins 3 lignes.
		ft_exit_error("Map miniumum size is 3 lines", 1, data);
	if (verify_top_line(data->map_tab[data->idx_map_start]) == false) //Espaces apres la topline non geres.
		ft_exit_error("Top of map not closed", 1, data);
	if (verify_left_side(data) == false)
		ft_exit_error("Sides not closed", 1, data);
	if (verify_right_side(data) == false)
		ft_exit_error("Sides not closed", 1, data);
	// if (verify_bottom_line(data) == false)
	// 	ft_exit_error("Bottom of map not closed", 1, data);
}

void get_map_end_idx(t_data *data)
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
		while (data->map_tab[end][j] && (data->map_tab[end][j] == ' ' || data->map_tab[end][j] == '\t' || data->map_tab[end][j] == '\r'))
			j++;
		if (data->map_tab[end][j] != '\0')
			break ;
		end--;
	}
	data->idx_map_end = end + 1; // Index juste derriere la derniere ligne de map.
}

void parse_map(t_data *data)
{
	int	i;

	skip_white_lines(data);
	i = data->idx_map_start;
	while (data->map_tab[i])
	{
		if (characters_check(data->map_tab[i]) == false)
			ft_exit_error("Invalid characters in map", 1, data);
		i++;
	}
	get_map_end_idx(data);
	check_if_closed_map(data);
}
