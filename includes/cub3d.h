/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:20:17 by fgonzale          #+#    #+#             */
/*   Updated: 2024/03/08 03:06:17 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <string.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "../includes/Color.h"



typedef struct s_data
{
	char **map_tab;
	int		idx_map_start;
	int		idx_map_end;
	int		height;
	int		width;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
}	t_data;

/////// FREE FUNCTIONS ///////

void ft_exit_error(char *msg, int exit_code, t_data *data);


/////// CHECK MAP FUNCTIONS ///////

void check_map_validity(int argc, char **argv, t_data *data);

/////// PARSE IDENTIFIERS FUNCTIONS ///////

void parse_identifiers(t_data *data);
bool enough_identifiers(t_data *data);

/////// PARSE MAP FUNCTIONS ///////

void parse_map(t_data *data);
void skip_white_lines(t_data *data);
void check_if_closed_map(t_data *data);

/////// UTILS FUNCTIONS ///////

int	get_number_lines(char *map_arg);
void print_map(t_data *data);
void print_identifiers(t_data *data);
void free_strs(char **strs);

#endif
