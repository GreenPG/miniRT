/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid_normal_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:48:32 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/23 10:44:03 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_normal	ellipsoid_normal_init(t_ellipsoid *ellipsoid, t_vector ray,
			double distance)
{
	t_normal	normal;

	normal.origin.x = distance * ray.x;
	normal.origin.y = distance * ray.y;
	normal.origin.z = distance * ray.z;
	normal.dir.x = (normal.origin.x - ellipsoid->origin->x);
	normal.dir.y = (normal.origin.y - ellipsoid->origin->y);
	normal.dir.z = (normal.origin.z - ellipsoid->origin->z);
	return (normal);
}

static double	get_el_angle(t_vector u, t_vector v)
{
	double	angle;

	angle = acos(fminf(dot_product(u, v)
				/ (sqrt(dot_product(u, u))
					* sqrt(dot_product(v, v))), 1.));
	return (angle);
}

static t_cyl_calc	to_object(t_ellipsoid *ellipsoid,
	t_vector *tmp, t_normal *normal)
{
	t_cyl_calc	data;

	data.front.x = 0.0000001;
	data.front.y = 1;
	data.front.z = 0.0000001;
	data.cross = vector_cross(*ellipsoid->direction, data.front);
	data.cross = vector_norm(data.cross);
	data.angle = get_el_angle(*ellipsoid->direction, data.front);
	rotate_around_axis(&normal->dir, data.cross, -data.angle);
	rotate_around_axis(tmp, data.cross, -data.angle);
	data.front.x = 1e-6;
	data.front.y = 1e-6;
	data.front.z = 1;
	if (dot_product(*tmp, data.front) > -1 + 1e-6)
	{
		data.cross = vector_cross(*tmp, data.front);
		data.cross = vector_norm(data.cross);
		data.angle = get_el_angle(*tmp, data.front);
		rotate_around_axis(&normal->dir, data.cross, data.angle);
	}
	return (data);
}

t_normal	get_ellipsoid_normal(t_ellipsoid *ellipsoid, t_vector ray,
			double distance)
{
	t_normal	normal;
	t_cyl_calc	data;
	t_vector	tmp;

	normal = ellipsoid_normal_init(ellipsoid, ray, distance);
	tmp.x = ellipsoid->up->x;
	tmp.y = ellipsoid->up->y;
	tmp.z = ellipsoid->up->z;
	data = to_object(ellipsoid, &tmp, &normal);
	normal.dir.x *= ellipsoid->a;
	normal.dir.y *= ellipsoid->b;
	normal.dir.z *= ellipsoid->c;
	if (dot_product(tmp, data.front) > -1 + 1e-6)
		rotate_around_axis(&normal.dir, data.cross, -data.angle);
	data.front.x = 1e-6;
	data.front.y = 1;
	data.front.z = 1e-6;
	data.cross = vector_cross(*ellipsoid->direction, data.front);
	data.cross = vector_norm(data.cross);
	data.angle = get_el_angle(*ellipsoid->direction, data.front);
	rotate_around_axis(&normal.dir, data.cross, data.angle);
	normal.dir = vector_norm(normal.dir);
	return (normal);
}
