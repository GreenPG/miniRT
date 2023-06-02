/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_shadow.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:44:29 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/01 14:47:16 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_vector	get_normal_dir(t_cylinder *cylinder, t_vector normal_o)
{
	t_vector	axis;
	t_vector	normal_dir;
	double		quotient;
	double		vector_len;	

	axis.x = 0;
	axis.y = cylinder->height / 2;
	axis.z = 0;
	quotient = dot_product(normal_o, axis) / dot_product(axis, axis);
	normal_dir.x = normal_o.x - quotient * (axis.x);
	normal_dir.y = normal_o.y - quotient * (axis.y);
	normal_dir.z = normal_o.z - quotient * (axis.z);
	vector_len = sqrt(dot_product(normal_dir, normal_dir));
	normal_dir.x /= vector_len;
	normal_dir.y /= vector_len;
	normal_dir.z /= vector_len;
	return (normal_dir);
}

static t_normal	normal_body(t_cylinder *cylinder, t_vector ray, double distance)
{
	t_normal	normal;
	t_vector	rayo;

	ray = transform_ray(ray, cylinder);
	rayo = transform_rayo(ray, cylinder);
	normal.origin.x = distance * ray.x + rayo.x;
	normal.origin.y = distance * ray.y + rayo.y;
	normal.origin.z = distance * ray.z + rayo.z;
	normal.dir = get_normal_dir(cylinder, normal.origin);
	normal.origin = revert_transform(normal.origin, cylinder);
	normal.origin.x += cylinder->origin->x;
	normal.origin.y += cylinder->origin->y;
	normal.origin.z += cylinder->origin->z;
	normal.dir = revert_transform(normal.dir, cylinder);
	return (normal);
}

static t_normal	normal_caps(t_cylinder *cylinder, t_vector ray, double distance)
{
	t_normal	normal;

	normal.origin.x = ray.x * distance;
	normal.origin.y = ray.y * distance;
	normal.origin.z = ray.z * distance;
	if (dot_product(ray, *cylinder->direction) > 0)
	{
		normal.dir.x = -cylinder->direction->x;
		normal.dir.y = -cylinder->direction->y;
		normal.dir.z = -cylinder->direction->z;
	}
	else
	{
		normal.dir.x = cylinder->direction->x;
		normal.dir.y = cylinder->direction->y;
		normal.dir.z = cylinder->direction->z;
	}
	return (normal);
}

t_normal	get_cylinder_normal(t_cylinder *cylinder, t_vector ray,
		double distance)
{
	t_normal	normal;

	if (cylinder->hit_body == true)
		normal = normal_body(cylinder, ray, distance);
	else
		normal = normal_caps(cylinder, ray, distance);
	cylinder->hit_body = false;
	return (normal);
}
