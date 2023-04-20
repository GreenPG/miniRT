/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 07:46:56 by gtouzali          #+#    #+#             */
/*   Updated: 2023/04/20 15:51:40 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>

# include <unistd.h>
# include <math.h>
# include <string.h>
# include <stdlib.h>
# include <libft.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"

# include "./config.h"
# include "structs_utils.h"
# include "sphere.h"
# include "camera.h"

# include "ambiant_light.h"
# include "light.h"
# include "cylinder.h"
# include "plane.h"
# include "scene.h"

int			ft_error(char *str);
double		dot_product(const t_vector v, const t_vector u);
int			get_rgba(int r, int g, int b, int a);
int			ray_launcher(mlx_t *mlx, mlx_image_t *img, t_camera camera);

/*	utils.c	*/

double		ft_atof(char *str);
/*	parsing.c	*/

int			check_path(char *path);
t_scene		*parsing(char *path);

/*	obj.c	*/

void		choose_component(char *line, t_scene *scene);

/*	choose_component.c	*/

void		init_obj(char *line, t_obj_list **list_ptr, t_type type);
void		add_obj_error(t_scene *scene);

/*	parsing_utils.c	*/

void		pass_to_next_element(char *str, int *i);
int			check_triple_int(char *str, int *i);
int			check_int(char *str, int *i);
int			check_float(char *str, int *i);
int			check_triple_float(char *str, int *i);

/*	ambiant_light.c	*/

t_ambiant_l	*init_ambiant_l(char *input);

/*	camera.c	*/

t_camera	*init_camera(char *input);
void		free_camera(t_camera **camera);

/*	sphere.c	*/

t_sphere	*init_sphere(char *input);
void		free_sphere(t_sphere **sphere);

/*	light.c	*/

t_light		*init_light(char *str);
void		free_light(t_light **light);

/*	plane.c	*/

t_plane		*init_plane(char *str);
void		free_plane(t_plane **plane);

/*	cylinder.c */

t_cylinder	*init_cylinder(char *str);
void		free_cylinder(t_cylinder **cylinder);

/*	structs_utils.c	*/

t_coords	*init_coords(float x, float y, float z);
t_coords	*get_coords(char *str);
t_vector	*init_vector(char *str);
t_vector	*get_vector(char *str);
int			*get_color_values(char	*str);

/*	free_scene.c	*/

void		free_scene(t_scene **scene);

#endif
