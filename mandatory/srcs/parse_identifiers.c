/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 19:25:53 by fgonzale          #+#    #+#             */
/*   Updated: 2024/04/13 03:28:21 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	word_is_identifier(char *word, t_data *data)
{
	char	*identifier[6] = {"NO", "SO", "WE", "EA", "F", "C"};
	int		i;

	i = 0;
	if (!word)
		return (false);
	while (i < 6)
	{
		if (ft_strlen(word) == ft_strlen(identifier[i])
			&& !ft_strncmp(word, identifier[i], ft_strlen(identifier[i])))
			return (true);
		i++;
	}
	(void)data;
	return (false);
}

static bool	fill_identifier(t_data *data, char *identifier, char *value)
{
	if (!ft_strncmp(identifier, "NO", 2) && data->no == NULL)
		data->no = ft_strdup2(value);
	else if (!ft_strncmp(identifier, "SO", 2) && data->so == NULL)
		data->so = ft_strdup2(value);
	else if (!ft_strncmp(identifier, "WE", 2) && data->we == NULL)
		data->we = ft_strdup2(value);
	else if (!ft_strncmp(identifier, "EA", 2) && data->ea == NULL)
		data->ea = ft_strdup2(value);
	else if (!ft_strncmp(identifier, "F", 1) && data->f == NULL)
		data->f = ft_strdup2(value);
	else if (!ft_strncmp(identifier, "C", 1) && data->c == NULL)
		data->c = ft_strdup2(value);
	else
		return (false);
	return (true);
}

static void	add_value_to_identifier(char *value, char *identifier, t_data *data)
{
	char	*trimmed_value;

	trimmed_value = ft_strtrim(value, " \t\r");
	if (!trimmed_value)
	{
		if (value)
			free(value);
		ft_exit_error("Error with value memory allocation", 1, data);
	}
	if (fill_identifier(data, identifier, trimmed_value) == false)
	{
		free(value);
		free(identifier);
		free(trimmed_value);
		ft_exit_error("Error with idenfitier, check for doubles", 1, data);
	}
	free(trimmed_value);
}

bool	enough_identifiers(t_data *data)
{
	if (data->no == NULL)
		return (false);
	if (data->so == NULL)
		return (false);
	if (data->we == NULL)
		return (false);
	if (data->ea == NULL)
		return (false);
	if (data->f == NULL)
		return (false);
	if (data->c == NULL)
		return (false);
	return (true);
}

void	parse_identifiers(t_data *data)
{
	int		i;
	int		j;
	int		word_start;
	int		value_start;
	char	*word;
	char	*value;

	j = 0;
	i = 0;
	while (data->map_tab[i] && enough_identifiers(data) == false)
	{
		j = 0;
		while (data->map_tab[i] && data->map_tab[i][j] == '\0')
			i++;
		while (data->map_tab[i] && data->map_tab[i][j] && (data->map_tab[i][j] == ' ' || data->map_tab[i][j] == '\t' || data->map_tab[i][j] == '\r'))
			j++;
		if (data->map_tab[i] == NULL)
			break ;
		if (data->map_tab[i] && data->map_tab[i][j] == '\0')
		{
			i++;
			continue ;
		}
		word_start = j;
		while (data->map_tab[i][j] && (data->map_tab[i][j] != ' ' && data->map_tab[i][j] != '\t' && data->map_tab[i][j] != '\r')) //Rajouter \t et \r
			j++;
		word = ft_substr(data->map_tab[i], word_start, j - word_start);
		if (word_is_identifier(word, data) == false)
			error_identifier_name(word, data);
		if (data->map_tab[i][j] == '\0' || is_empty(&data->map_tab[i][j]))
			error_identifier_value(word, data);
		j++; // Avancer apres l'espace de l'identifiant
		value_start = j;
		while (data->map_tab[i][j])
			j++;
		value = ft_substr(data->map_tab[i], value_start, j - value_start);
		add_value_to_identifier(value, word, data);
		free(word);
		free(value);
		i++;
	}
	if (enough_identifiers(data) == false)
		ft_exit_error("You need to define SO, NO, WE, EA, F and C", 1, data);
	data->idx_map_start = i;
}
