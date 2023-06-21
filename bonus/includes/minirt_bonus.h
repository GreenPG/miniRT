/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 07:46:56 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/21 07:22:06 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

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

# include "config_bonus.h"
# include "structs_utils_bonus.h"
# include "sphere_bonus.h"
# include "camera_bonus.h"
# include "ambiant_light_bonus.h"
# include "light_bonus.h"
# include "cylinder_bonus.h"
# include "plane_bonus.h"
# include "ellipsoid_bonus.h"
# include "triangle_bonus.h"
# include "scene_bonus.h"

typedef struct s_data {
	mlx_t	*mlx;
	t_scene	*scene;
}	t_data;

double			*ft_swap(double *pair);
int				ft_error(char *str);
int				get_rgba(int r, int g, int b, int a);
int				get_r(int rgba);
int				get_g(int rgba);
int				get_b(int rgba);
int				get_obj_color(t_obj_list *nearest, t_vector ray, t_scene *scene,
					double distance);
/*	main.c	*/

/*	utils.c	*/

double			ft_atof(char *str);
/*	parsing.c	*/

int				check_path(char *path);
t_scene			*parsing(char *path);

/*	choose_component.c	*/

void			choose_component(char *line, t_scene **scene);

/*	obj.c	*/

int				init_obj(char *line, t_obj_list **list_ptr, t_type type);

/*	obj_type_bonus.c	*/
int				sphere_obj(t_obj_list *obj, char *line);
int				plane_obj(t_obj_list *obj, char *line);
int				cylinder_obj(t_obj_list *obj, char *line);
int				ellipsoid_obj(t_obj_list *obj, char *line);
int				triangle_obj(t_obj_list *obj, char *line);

/*	obj_utils.c	*/

int				get_bonus_data(t_obj_list **obj_ptr, char *line);
void			add_obj_error(t_scene **scene);
void			add_obj(t_obj_list **list_ptr, t_obj_list *obj);

/*	bonus_data_parsing.g	*/

int				get_bonus_data(t_obj_list **obj_ptr, char *line);

/*	parsing_utils.c	*/

void			pass_to_next_element(char *str, int *i);

/*	check_input.c	*/
int				check_specular(char *str, int *i);
int				check_bump(char *str, int *i);
int				check_triple_int(char *str, int *i);
int				check_int(char *str, int *i);
int				check_float(char *str, int *i);
int				check_triple_float(char *str, int *i);

/*	check_input2.c	*/
int				check_bonus_var(char *str);
int				check_triangle(char *input);
int				check_cylinder(char *str);

/*	ambiant_light.c	*/

t_ambiant_l		*init_ambiant_l(char *input);

/*	camera.c	*/

t_camera		*init_camera(char *input);
void			free_camera(t_camera **camera);

/*	sphere.c	*/

t_sphere		*init_sphere(char *input);

/*	sphere_calculations.c	*/
double			get_root(double a, double b, double d);
double			sphere_hit(t_sphere *sphere, t_vector ray);
t_normal		get_sphere_normal(t_sphere *sphere, t_vector ray,
					double distance);

/*	light.c	*/

t_light			*init_light(char *str);
void			free_light(t_light **light);

/*	plane.c	*/

t_plane			*init_plane(char *str);

/*	cylinder.c */

t_cylinder		*init_cylinder(char *str);

/*	ellipsoid.c	*/

t_ellipsoid		*init_ellipsoid(char *str);

/*	ellipsoid_normal.c*/

t_normal		get_ellipsoid_normal(t_ellipsoid *ellipsoid, t_vector ray,
					double distance);

/*	triangle_bonus.c */
t_triangle		*init_triangle(char	*input);

/*	structs_utils.c	*/

t_vector		*init_coords(float x, float y, float z);
t_vector		*get_coords(char *str);
int				*get_color_values(char	*str);

/*	vector.c	*/

t_vector		*init_vector(char *str);

/*	vector_calcuations.c	*/
t_vector		vector_norm(t_vector vec);
t_vector		invert_vector(t_vector u);
t_vector		vector_cross_tr(t_vector a, t_vector b);
t_vector		vector_cross(t_vector a, t_vector b);
double			dot_product(const t_vector v, const t_vector u);

/*	render.c	*/

int				render(mlx_image_t *img, t_scene *scene);
int				init_rays(t_scene *scene);

/*	rotation.c	*/

void			rotation_x(t_scene *scene, double angle);
void			rotation_y(t_scene *scene, double angle);
void			rotation_z(t_scene *scene, double angle);
void			world_rotate(t_scene *scene, double alpha,
					double beta, double theta);

/*	rotation_obj_bonus.c	*/
void			rotate_one(t_obj_list *nearest, int x, int y, int z);

/*	vector_rotation_bonus.c */
void			vector_rot_x(t_vector *vec, double angle);
void			vector_rot_y(t_vector *vec, double angle);
void			vector_rot_z(t_vector *vec, double angle);

/* 	world_move.c	*/

void			world_rot_x(t_scene *scene, double angle);
void			world_rot_y(t_scene *scene, double angle);
void			world_rot_z(t_scene *scene, double angle);

/* 	cylinder_move.c	*/

void			cylinder_rot_y(t_cylinder *cylinder, double angle);
void			cylinder_rot_x(t_cylinder *cylinder, double angle);
void			cylinder_rot_z(t_cylinder *cylinder, double angle);
void			cylinder_translate(t_cylinder *cylinder, double x, double y,
					double z);

/*	plane_move.c	*/
void			plane_rot_y(t_plane *plane, double angle);
void			plane_rot_x(t_plane *plane, double angle);
void			plane_rot_z(t_plane *plane, double angle);
void			plane_translate(t_plane *plane, double x, double y, double z);

	/*	ellipsoid_move.c	*/
void			ellipsoid_rot_y(t_ellipsoid *ellipsoid, double angle);
void			ellipsoid_rot_x(t_ellipsoid *ellipsoid, double angle);
void			ellipsoid_rot_z(t_ellipsoid *ellipsoid, double angle);
void			ellipsoid_translate(t_ellipsoid *ellipsoid, double x,
					double y, double z);

	/*	sphere_move.c	*/
void			sphere_rot_y(t_sphere *sphere, double angle);
void			sphere_rot_x(t_sphere *sphere, double angle);
void			sphere_rot_z(t_sphere *sphere, double angle);
void			sphere_translate(t_sphere *sphere, double x, double y,
					double z);

/*	triangle_move.c	*/
void			triangle_rot_y(t_triangle *triangle, double angle);
void			triangle_rot_z(t_triangle *triangle, double angle);
void			triangle_rot_x(t_triangle *triangle, double angle);
void			triangle_translate(t_triangle *triangle, double x,
					double y, double z);

/*	rotate_around_triangle_bonus.c	*/
void			triangle_rotate(t_triangle *triangle, int x, int y, int z);

/*	light_rotation.c	*/
void			light_rot_x(t_light_list *light_list, double angle);
void			light_rot_y(t_light_list *light_list, double angle);
void			light_rot_z(t_light_list *light_list, double angle);

/*	translate.c	*/

void			world_translate(t_scene *scene, double x, double y, double z);

/*	free_functions.c	*/
void			free_all(t_data *data, t_scene *scene);
void			free_scene(t_scene **scene);

/*	free_obj_bonus.c	*/
void			free_triangle(t_triangle **triangle_ptr);
void			free_ellipsoid(t_ellipsoid **cylinder);
void			free_cylinder(t_cylinder **cylinder);
void			free_plane(t_plane **plane);
void			free_sphere(t_sphere **sphere);

/*	hit_functions.c */
double			plane_hit(t_plane *obj, t_vector ray);

/*	math_utils.c	*/
double			*cyl_quadratic(double a, double b, double c);
double			quadratic(double a, double b, double c);
double			get_alpha(t_vector vec);
double			get_beta(t_vector vec);
double			get_theta(t_vector vec);

/*	utils_calc.c	*/
void			get_angle(t_cyl_calc *data, t_ellipsoid *ellipsoid, int dir);

/*	rgba.c	*/
int				get_rgba(int r, int g, int b, int a);
int				get_r(int rgba);
int				get_g(int rgba);
int				get_b(int rgba);
int				get_a(int rgba);

/*	normal.c	*/
t_normal		get_plane_normal(t_plane *plane, t_vector ray, double distance);
t_normal		get_cylinder_normal(t_cylinder *cylinder, t_vector ray,
					double distance);
t_normal		orient_normal(t_scene *scene, t_normal normal,
					t_vector light_dir);
t_normal		get_normal(t_obj_list *nearest, t_vector ray, double distance);

/*	light_calculations.c	*/
t_vector		get_light_dir(t_light *light, t_normal normal);
int				light_intersect(t_scene *scene, t_vector light_dir,
					t_normal normal, t_vector ray);
int				get_diffuse_color(t_scene *scene, t_vector ray, t_normal normal,
					t_obj_list *nearest);
int				get_specular_color(t_scene *scene, t_vector ray,
					t_normal normal, t_obj_list *nearest);

/*	specular_bonus.c	*/
int				get_specular_color(t_scene *scene, t_vector ray,
					t_normal normal, t_obj_list *nearest);

/*	light_rgb_bonus.c	*/
void			increment_color(int *rgb, int color, double ratio, double ks);
int				clamp_rgb(int *rgb);
int				*init_rgb_tab(void);

/*	keypress_handle.c	*/
void			handle_keypress(mlx_key_data_t keydata, void *ptr);

/*	move_obj.c	*/
void			mouse_handle(mouse_key_t button, action_t action,
					modifier_key_t mods, void *param);
void			move_one(t_obj_list *nearest, double x, double y, double z);

/*	shadow.c	*/

double			get_shadow_distance(t_obj_list *cursor, t_normal normal,
					t_vector light_dir);

/*	triangle_shadows.c */
double			triangle_shadow(t_triangle *triangle, t_normal normal,
					t_vector light_dir);

/*	cylinder_calculations.c 	*/
double			*caps_hit(t_vector ray, t_vector rayo, t_cylinder *cylinder);
double			*body_hit(t_vector ray, t_vector rayo, t_cylinder *cylinder);
double			*between_caps(double *root, t_vector light_o,
					t_vector light_dir, t_cylinder *cylinder);
double			cylinder_hit(t_cylinder *cylinder, t_vector ray);

/*	cylinder_calculations2.c	*/
void			free_cyl_roots(double *root, double *caps);
double			min_cyl(double t_1, double t_2, double t_3, double t_4);

/* triangle_calculations_bonus.c */
bool			is_in_front_of_edge_bf(t_vector a, t_vector b,
					t_vector intersect, t_vector normal);
bool			is_in_front_of_edge_ff(t_vector a, t_vector b,
					t_vector intersect, t_vector normal);
double			distance_to_plane(t_triangle *triangle, t_vector ray);
double			triangle_hit(t_triangle *triangle, t_vector ray);

/*	cylinder_ellipsoid.c 	*/

double			ellipsoid_distance(t_ellipsoid *ellipsoid,
					t_cyl_calc data, t_vector ray);
double			ellipsoid_hit(t_ellipsoid *hell, t_vector ray);
double			ellipsoid_shadow(t_ellipsoid *ellipsoid, t_normal normal,
					t_vector light_dir);

/*	ray.c	*/
t_vector		calculate_ray_direction(unsigned int x, unsigned int y,
					t_camera *camera);
t_vector		ray_direction(unsigned int x, unsigned int y, t_camera camera);
void			free_rays(t_rays *ray_list);
int				init_rays(t_scene *scene);

/*	normal_color.c	*/

int				get_normal_color(t_obj_list *nearest, t_vector ray,
					t_normal normal);

/*	ray_transforms.c	*/
t_vector		transform_rayo(t_vector ray, t_cylinder *cylinder);
t_vector		transform_ray(t_vector ray, t_cylinder *cylinder);
t_vector		revert_transform(t_vector vec, t_cylinder *cylinder);

/*	cylinder_shadow.c	*/
t_normal		get_cylinder_normal(t_cylinder *cylinder, t_vector ray,
					double distance);

/*	light_list_bonus.c	*/
void			free_light_list(t_light_list *light_list);
void			add_light(t_light_list **light_list, char *line);
t_light_list	*init_light_list(char *line);

/*	checkerboard	*/

int				get_checkerboard(t_obj_list *nearest, t_normal normal);

/*	textures	*/

int				get_texture(t_obj_list *near, t_normal normal);
int				texture_triangle(t_vector vec, t_triangle *triangle,
					mlx_texture_t *tex);
int				checkerboard_triangle(t_vector vec, t_triangle *triangle);
t_normal		bump_triangle(t_triangle *triangle, t_vector vec,
					t_normal normal, mlx_texture_t *tex);
t_normal		bump_cylinder(t_cylinder *cylinder, t_vector vec,
					t_normal normal, mlx_texture_t *tex);
t_vector		normal_perturbation(t_vector normal_dir, int x, int y,
					mlx_texture_t *tex);

/*	quaternions.c	*/

void			rotate_around_axis(t_vector *vec, t_vector axis, double angle);

/*	direction_init.c	*/

t_vector		*get_up(t_vector *direction);
t_vector		*up_default(void);
t_vector		*direction_default(void);
t_frame			*frame_init(t_vector *dir);

/*	bump_map	*/

t_normal		get_bump(t_obj_list *near, t_normal normal);

/*	coordinate_frame_transform.c	*/

t_vector		camera_to_object_space(t_vector vec, t_vector obj_dir,
					t_vector obj_up);
t_vector		camera_to_object_space_sym(t_vector vec, t_vector obj_dir);

#endif
