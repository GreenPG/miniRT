/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 07:46:56 by gtouzali          #+#    #+#             */
/*   Updated: 2023/04/18 16:01:01 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdlib.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/include/libft.h"
# include <math.h>
# include <fcntl.h>

# include "./config.h"
# include "structs_utils.h"
# include "camera.h"
# include "sphere.h"
# include "plane.h"
# include "ambiant_light.h"
# include "light.h"
# include "cylinder.h"
# include "scene.h"

/*	utils.c	*/

int			ft_error(char *str);
double		ft_atof(char *str);

/*	parsing.c	*/

int			check_path(char *path);
t_scene		*parsing(char *path);

/*	parsing_utils.c	*/

int			check_float(char *str, int *i);
int			check_triple_int(char *str, int *i);
int			check_int(char *str, int *i);
int			check_triple_float(char *str, int *i);

/*	ambiant_light.c	*/

t_ambiant_l	*init_ambiant_l(char *input);

/*	camera.c	*/

t_camera	*init_camera(char *input);

/*	sphere.c	*/

t_sphere	*init_sphere(char *input);

/*	structs_utils.c	*/

t_coords	*init_coords(float x, float y, float z);
t_coords	*get_coords(char *str);
t_vector	*init_vector(float x, float y, float z);
t_vector	*get_vector(char *str);
int			*get_color_values(char	*str);

/*	color.c	*/

int			get_rgba(int r, int g, int b, int a);
int			get_r(int rgba);
int			get_g(int rgba);
int			get_b(int rgba);
int			get_a(int rgba);

#endif
