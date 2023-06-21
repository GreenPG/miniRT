/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:46:52 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/21 08:31:20 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_normal	get_plane_normal(t_plane *plane, t_vector ray, double distance)
{
	t_normal	normal;
	double		vector_len;

	normal.origin.x = distance * ray.x;
	normal.origin.y = distance * ray.y;
	normal.origin.z = distance * ray.z;
	normal.dir.x = plane->direction->x;
	normal.dir.y = plane->direction->y;
	normal.dir.z = plane->direction->z;
	vector_len = sqrt(dot_product(normal.dir, normal.dir));
	normal.dir.x /= vector_len;
	normal.dir.y /= vector_len;
	normal.dir.z /= vector_len;
	return (normal);
}

static t_normal	get_triangle_normal(t_triangle *triangle, t_vector ray,
		double distance)
{
	t_normal	normal;
	double		vector_len;

	normal.origin.x = distance * ray.x;
	normal.origin.y = distance * ray.y;
	normal.origin.z = distance * ray.z;
	normal.dir.x = triangle->normal->x;
	normal.dir.y = triangle->normal->y;
	normal.dir.z = triangle->normal->z;
	vector_len = sqrt(dot_product(normal.dir, normal.dir));
	normal.dir.x /= vector_len;
	normal.dir.y /= vector_len;
	normal.dir.z /= vector_len;
	return (normal);
}

t_normal	get_normal(t_obj_list *nearest, t_vector ray, double distance)
{
	t_normal	normal;
	if (nearest->type == sphere)
		normal = get_sphere_normal(nearest->sphere, ray, distance);
	if (nearest->type == plane)
		normal = get_plane_normal(nearest->plane, ray, distance);
	if (nearest->type == cylinder)
		normal = get_cylinder_normal(nearest->cylinder, ray, distance);
	if (nearest->type == ellipsoid)
		normal = get_ellipsoid_normal(nearest->ellipsoid, ray, distance);
	if (nearest->type == triangle)
		normal = get_triangle_normal(nearest->triangle, ray, distance);
	return (normal);
}
