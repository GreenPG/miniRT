/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 07:46:56 by gtouzali          #+#    #+#             */
/*   Updated: 2023/04/14 15:12:06 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdlib.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/include/libft.h"

# include "./config.h"
# include "structs_utils.h"
# include "sphere.h"

int			ft_error(char *str);

/*	parsing.c	*/

int			check_path(char *path);
t_coords	*init_coords(float x, float y, float z);
t_vector	*init_vector(float x, float y, float z);
t_color		*init_color(int r, int g, int b);

#endif
