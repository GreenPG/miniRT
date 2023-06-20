/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid_normal_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:48:32 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/20 15:54:09 by gtouzali         ###   ########.fr       */
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

static t_cyl_calc	to_object(t_ellipsoid *ellipsoid,
	t_vector *tmp, t_normal *normal)
{
	t_cyl_calc	data;

	data.front.x = 0.0000001;
	data.front.y = 1;
	data.front.z = 0.0000001;
	data.cross = vector_cross(*ellipsoid->direction, data.front);
	data.cross = vector_norm(data.cross);
	data.angle = acos(dot_product(*ellipsoid->direction, data.front)
			/ (sqrt(dot_product(*ellipsoid->direction, *ellipsoid->direction))
				* sqrt(dot_product (data.front, data.front))));
	rotate_around_axis(&normal->dir, data.cross, -data.angle);
	rotate_around_axis(tmp, data.cross, -data.angle);
	data.front.x = 0.0000001;
	data.front.y = 0.0000001;
	data.front.z = 1;
	if (dot_product(*tmp, data.front) > -1 + 1e-6)
	{
		data.cross = vector_cross(*tmp, data.front);
		data.cross = vector_norm(data.cross);
		data.angle = acos(dot_product(*tmp, data.front)
				/ (sqrt(dot_product(*tmp, *tmp))
					* sqrt(dot_product (data.front, data.front))));
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
