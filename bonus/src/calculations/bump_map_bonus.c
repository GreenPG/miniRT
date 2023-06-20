/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:16:59 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/20 16:20:59 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static	t_normal	bump_plane(t_plane *plane, t_vector vec, t_normal normal,
	mlx_texture_t *tex)
{
	int	x;
	int	y;

	vec.x -= plane->origin->x;
	vec.y -= plane->origin->y;
	vec.z -= plane->origin->z;
	vec = camera_to_object_space(vec, *plane->direction, *plane->up);
	vec.z = fmodf(vec.z, 1);
	if (vec.z < 0)
		vec.z += 1;
	vec.x = fmodf(vec.x, 1);
	if (vec.x < 0)
		vec.x += 1;
	x = vec.z * tex->width;
	y = vec.x * tex->height;
	normal.dir = normal_perturbation(normal.dir, x, y, tex);
	return (normal);
}

static t_normal	bump_ellipsoid(t_ellipsoid *ellipsoid, t_vector vec,
	t_normal normal, mlx_texture_t *tex)
{	
	int		x;
	int		y;
	double	alpha;
	double	beta;

	vec.x -= ellipsoid->origin->x;
	vec.y -= ellipsoid->origin->y;
	vec.z -= ellipsoid->origin->z;
	vec = camera_to_object_space(vec, *ellipsoid->direction, *ellipsoid->up);
	alpha = atan2(vec.y, vec.x);
	beta = acos(vec.z);
	x = (alpha + M_PI) / (M_PI * 2.) * tex->width;
	y = (beta) / M_PI * tex->height;
	normal.dir = normal_perturbation(normal.dir, x, y, tex);
	return (normal);
}

static t_normal	bump_sphere(t_sphere *sphere, t_vector vec, t_normal normal,
	mlx_texture_t	*tex)
{
	double	alpha;
	double	beta;
	int		x;
	int		y;

	vec = camera_to_object_space(vec, *sphere->direction, *sphere->up);
	alpha = atan2(vec.y, vec.x);
	beta = acos(vec.z);
	x = (alpha + M_PI) / (M_PI * 2.) * tex->width;
	y = (beta) / M_PI * tex->height;
	normal.dir = normal_perturbation(normal.dir, x, y, tex);
	return (normal);
}

t_normal	get_bump(t_obj_list *near, t_normal normal)
{
	if (near->type == sphere)
		normal = bump_sphere(near->sphere, normal.dir, normal,
				near->bump_map);
	if (near->type == plane)
		normal = bump_plane(near->plane, normal.origin, normal,
				near->bump_map);
	if (near->type == cylinder)
		normal = bump_cylinder(near->cylinder, normal.origin, normal,
				near->bump_map);
	if (near->type == ellipsoid)
		normal = bump_ellipsoid(near->ellipsoid, normal.origin, normal,
				near->bump_map);
	if (near->type == triangle)
		normal = bump_triangle(near->triangle, normal.origin, normal,
				near->bump_map);
	return (normal);
}
