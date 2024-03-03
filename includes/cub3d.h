/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:20:17 by fgonzale          #+#    #+#             */
/*   Updated: 2024/03/03 18:02:53 by fgonzale         ###   ########.fr       */
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
}	t_data;

/////// FREE FUNCTIONS ///////

void ft_exit_error(char *msg, int exit_code, t_data *data);


void check_map_validity(int argc, char **argv, t_data *data);

/////// UTILS FUNCTIONS ///////

int	get_number_lines(char *map_arg);
void print_map(t_data *data);
void free_strs(char **strs);

#endif
