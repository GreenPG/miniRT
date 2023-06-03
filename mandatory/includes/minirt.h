/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 07:46:56 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/02 15:12:31 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>

# include <unistd.h>
# include <math.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <libft.h>
# include "../../lib/MLX42/include/MLX42/MLX42.h"

# include "./config.h"
# include "structs_utils.h"
# include "sphere.h"
# include "camera.h"
# include "ambiant_light.h"
# include "light.h"
# include "cylinder.h"
# include "plane.h"
# include "scene.h"

typedef struct s_data {
	mlx_t	*mlx;
	t_scene	*scene;
}	t_data;

double		*ft_swap(double *pair);
int			ft_error(char *str);
int			get_rgba(int r, int g, int b, int a);
int			get_r(int rgba);
int			get_g(int rgba);
int			get_b(int rgba);
int			get_obj_color(t_obj_list *nearest, t_vector ray, t_scene *scene,
				double distance);
/*	main.c	*/

/*	utils.c	*/

double		ft_atof(char *str);
/*	parsing.c	*/

int			check_path(char *path);
t_scene		*parsing(char *path);

/*	choose_component.c	*/

void		choose_component(char *line, t_scene **scene);

/*	obj.c	*/

int			init_obj(char *line, t_obj_list **list_ptr, t_type type);

/*	obj_utils.c	*/

void		add_obj_error(t_scene **scene);
void		add_obj(t_obj_list **list_ptr, t_obj_list *obj);

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

/*	sphere_calculations.c	*/
double		get_root(double a, double b, double d);
double		sphere_hit(t_sphere *sphere, t_vector ray);
t_normal	get_sphere_normal(t_sphere *sphere, t_vector ray,
				double distance);

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

t_vector	*init_coords(float x, float y, float z);
t_vector	*get_coords(char *str);
int			*get_color_values(char	*str);

/*	vector.c	*/

t_vector	vector_cross(t_vector a, t_vector b);
double		dot_product(const t_vector v, const t_vector u);
t_vector	*init_vector(char *str);

	/*	render.c	*/

int			render(mlx_image_t *img, t_scene *scene);
int			init_rays(t_scene *scene);

	/*	rotation.c	*/

void		vector_rot_x(t_vector *vec, double angle);
void		vector_rot_y(t_vector *vec, double angle);
void		rotation_x(t_scene *scene, double angle);
void		rotation_y(t_scene *scene, double angle);
void		world_rotate(t_scene *scene, double alpha, double beta);

	/* 	cylinder_move.c	*/
void		cylinder_rot_y(t_cylinder *cylinder, double angle);
void		cylinder_rot_x(t_cylinder *cylinder, double angle);
void		cylinder_translate(t_cylinder *cylinder, double x, double y,
				double z);

	/*	plane_move.c	*/
void		plane_rot_y(t_plane *plane, double angle);
void		plane_rot_x(t_plane *plane, double angle);
void		plane_translate(t_plane *plane, double x, double y, double z);

	/*	sphere_move.c	*/
void		sphere_rot_y(t_sphere *sphere, double angle);
void		sphere_rot_x(t_sphere *sphere, double angle);
void		sphere_translate(t_sphere *sphere, double x, double y, double z);

	/*	light_rotation.c	*/
void		light_rot_x(t_light *light, double angle);
void		light_rot_y(t_light *light, double angle);

	/*	translate.c	*/

void		world_translate(t_scene *scene, double x, double y, double z);

	/*	free_functions.c	*/
void		free_all(t_data *data, t_scene *scene);
void		free_scene(t_scene **scene);

	/*	hit_functions.c */
double		plane_hit(t_plane *obj, t_vector ray);

	/*	math_utils.c	*/
double		*cyl_quadratic(double a, double b, double c);
double		quadratic(double a, double b, double c);
double		get_alpha(t_vector vec);
double		get_beta(t_vector vec);
double		get_theta(t_vector vec);

	/*	rgba.c	*/
int			get_rgba(int r, int g, int b, int a);
int			get_r(int rgba);
int			get_g(int rgba);
int			get_b(int rgba);
int			get_a(int rgba);

	/*	normal.c	*/
t_normal	get_plane_normal(t_plane *plane, t_vector ray, double distance);
t_normal	get_cylinder_normal(t_cylinder *cylinder, t_vector ray,
				double distance);
t_normal	orient_normal(t_scene *scene, t_normal normal, t_vector light_dir);
t_normal	get_normal(t_obj_list *nearest, t_vector ray, double distance);

/*	light_calculations.c	*/
int			get_diffuse_ratio(t_scene *scene, t_normal normal, t_vector ray);

/*	keypress_handle.c	*/
void		handle_keypress(mlx_key_data_t keydata, void *ptr);

/*	move_obj.c	*/
void		mouse_handle(mouse_key_t button, action_t action,
				modifier_key_t mods, void *param);
void		move_one(t_obj_list *nearest, double x, double y, double z);

/*	shadow.c	*/

double		plane_shadow(t_plane *plane, t_vector light_dir,
				t_normal normal);
double		sphere_shadow(t_sphere *sphere, t_normal normal,
				t_vector light_dir);
double		cylinder_shadow(t_cylinder *cylinder, t_normal normal,
				t_vector light_dir);
double		get_shadow_distance(t_obj_list *cursor, t_normal normal,
				t_vector light_dir);

/*	cylinder_calculations.c 	*/
double		*caps_hit(t_vector ray, t_vector rayo, t_cylinder *cylinder);
double		*body_hit(t_vector ray, t_vector rayo, t_cylinder *cylinder);
void		free_cyl_roots(double *root, double *caps);
double		*between_caps(double *root, t_vector light_o,
				t_vector light_dir, t_cylinder *cylinder);
double		cylinder_hit(t_cylinder *cylinder, t_vector ray);

/*	cylinder_calculations2.c	*/
double		min_cyl(double t_1, double t_2, double t_3, double t_4);

/*	ray.c	*/
t_vector	calculate_ray_direction(unsigned int x, unsigned int y,
				t_camera *camera);
t_vector	ray_direction(unsigned int x, unsigned int y, t_camera camera);
void		free_rays(t_rays *ray_list);
int			init_rays(t_scene *scene);

/*	normal_color.c	*/
int			get_normal_color(t_obj_list *nearest, t_vector ray,
				t_normal normal);

/*	ray_transforms.c	*/
t_vector	transform_rayo(t_vector ray, t_cylinder *cylinder);
t_vector	transform_ray(t_vector ray, t_cylinder *cylinder);
t_vector	revert_transform(t_vector vec, t_cylinder *cylinder);

/*	cylinder_shadow.c	*/
t_normal	get_cylinder_normal(t_cylinder *cylinder, t_vector ray,
				double distance);

#endif