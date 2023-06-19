/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:46:52 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/19 11:33:41 by gpasquet         ###   ########.fr       */
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

static t_normal	get_ellipsoid_normal(t_ellipsoid *ellipsoid, t_vector ray,
			double distance)
{
	t_normal	normal;

	normal.origin.x = distance * ray.x;
	normal.origin.y = distance * ray.y;
	normal.origin.z = distance * ray.z;
	normal.dir.x = (normal.origin.x - ellipsoid->origin->x);
	normal.dir.y = (normal.origin.y - ellipsoid->origin->y);
	normal.dir.z = (normal.origin.z - ellipsoid->origin->z);

	t_cyl_calc	data;
	t_vector	tmp;

	tmp.x = ellipsoid->up->x;
	tmp.y = ellipsoid->up->y;
	tmp.z = ellipsoid->up->z;
	data.front.x = 0.0000001;
	data.front.y = 1;
	data.front.z = 0.0000001;
	data.cross = vector_cross(*ellipsoid->direction, data.front);
	data.cross = vector_norm(data.cross);
	data.angle = acos(dot_product(*ellipsoid->direction, data.front)
			/ (sqrt(dot_product(*ellipsoid->direction, *ellipsoid->direction))
				* sqrt(dot_product (data.front, data.front))));
	rotate_around_axis(&normal.dir, data.cross, -data.angle);
	rotate_around_axis(&tmp, data.cross, -data.angle);
	data.front.x = 0.0000001;
	data.front.y = 0.0000001;
	data.front.z = 1;
	if (dot_product(tmp, data.front) > -1 + 1e-6)
	{
		data.cross = vector_cross(tmp, data.front);
		data.cross = vector_norm(data.cross);
		data.angle = acos(dot_product(tmp, data.front)
				/ (sqrt(dot_product(tmp, tmp))
					* sqrt(dot_product (data.front, data.front))));
		rotate_around_axis(&normal.dir, data.cross, data.angle);
	}
	normal.dir.x *= ellipsoid->a;
	normal.dir.y *= ellipsoid->b;
	normal.dir.z *= ellipsoid->c;
	if (dot_product(tmp, data.front) > -1 + 1e-6)
		rotate_around_axis(&normal.dir, data.cross, -data.angle);
	data.front.x = 0.0000001;
	data.front.y = 1;
	data.front.z = 0.0000001;
	data.cross = vector_cross(*ellipsoid->direction, data.front);
	data.cross = vector_norm(data.cross);
	data.angle = acos(dot_product(*ellipsoid->direction, data.front)
			/ (sqrt(dot_product(*ellipsoid->direction, *ellipsoid->direction))
				* sqrt(dot_product (data.front, data.front))));
	rotate_around_axis(&normal.dir, data.cross, data.angle);
	normal.dir = vector_norm(normal.dir);
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
