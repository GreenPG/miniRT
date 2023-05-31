/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:46:52 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/31 10:39:31 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_normal	get_sphere_normal(t_sphere *sphere, t_vector ray,
		double distance)
{
	t_normal	normal;
	double		vector_len;

	normal.origin.x = distance * ray.x;
	normal.origin.y = distance * ray.y;
	normal.origin.z = distance * ray.z;
	normal.dir.x = normal.origin.x - sphere->origin->x;
	normal.dir.y = normal.origin.y - sphere->origin->y;
	normal.dir.z = normal.origin.z - sphere->origin->z;
	vector_len = sqrt(dot_product(normal.dir, normal.dir));
	normal.dir.x /= vector_len;
	normal.dir.y /= vector_len;
	normal.dir.z /= vector_len;
	return (normal);
}

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

static t_normal	normal_body(t_cylinder *cylinder, t_vector ray, double distance)
{
	t_normal	normal;
	double		quotient;
	t_vector	rayo;
	t_vector	axis;
	double		tmpx;
	double		tmpy;
	double		vector_len;	

	axis.x = 0;
	axis.y = 1 * cylinder->height / 2;
	axis.z = 0;
	tmpx = ray.x;
	tmpy = ray.y;
	ray.x = ray.x * cos(cylinder->alpha) - ray.y * sin(cylinder->alpha)
		* cos(cylinder->beta) + ray.z * sin(cylinder->alpha)
		* sin(cylinder->beta);
	ray.y = tmpx * sin(cylinder->alpha) + ray.y * cos(cylinder->beta)
		* cos(cylinder->alpha) - ray.z * cos(cylinder->alpha)
		* sin (cylinder->beta);
	ray.z = tmpy * sin(cylinder->beta) + ray.z * cos(cylinder->beta);
	rayo = transform_ray(ray, cylinder);
	normal.origin.x = distance * ray.x + rayo.x;
	normal.origin.y = distance * ray.y + rayo.y;
	normal.origin.z = distance * ray.z + rayo.z;
	quotient = dot_product(normal.origin, axis) / dot_product(axis, axis);
	normal.dir.x = normal.origin.x - quotient * (axis.x);
	normal.dir.y = normal.origin.y - quotient * (axis.y);
	normal.dir.z = normal.origin.z - quotient * (axis.z);
	vector_len = sqrt(dot_product(normal.dir, normal.dir));
	normal.dir.x /= vector_len;
	normal.dir.y /= vector_len;
	normal.dir.z /= vector_len;
	tmpx = normal.origin.x;
	tmpy = normal.origin.y;
	normal.origin.x = normal.origin.x * cos(-cylinder->alpha) - normal.origin.y * sin(-cylinder->alpha)
		* cos(-cylinder->beta) + normal.origin.z * sin(-cylinder->alpha)
		* sin(-cylinder->beta);
	normal.origin.y = tmpx * sin(-cylinder->alpha) + normal.origin.y * cos(-cylinder->beta)
		* cos(-cylinder->alpha) - normal.origin.z * cos(-cylinder->alpha)
		* sin (-cylinder->beta);
	normal.origin.z = tmpy * sin(-cylinder->beta) + normal.origin.z * cos(-cylinder->beta);
	normal.origin.x += cylinder->origin->x;
	normal.origin.y += cylinder->origin->y;
	normal.origin.z += cylinder->origin->z;
	tmpx = normal.dir.x;
	tmpy = normal.dir.y;
	normal.dir.x = normal.dir.x * cos(-cylinder->alpha) - normal.dir.y * sin(-cylinder->alpha)
		* cos(-cylinder->beta) + normal.dir.z * sin(-cylinder->alpha)
		* sin(-cylinder->beta);
	normal.dir.y = tmpx * sin(-cylinder->alpha) + normal.dir.y * cos(-cylinder->beta)
		* cos(-cylinder->alpha) - normal.dir.z * cos(-cylinder->alpha)
		* sin (-cylinder->beta);
	normal.dir.z = tmpy * sin(-cylinder->beta) + normal.dir.z * cos(-cylinder->beta);
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

t_normal	orient_normal(t_scene *scene, t_normal normal, t_vector light_dir)
{
	t_obj_list	*cursor;

	cursor = scene->obj_list;
	while (cursor->hitted == 0)
		cursor = cursor->next;
	if (cursor->type == plane)
	{
		if (dot_product(normal.dir, light_dir) < 0)
		{
			normal.dir.x *= -1;
			normal.dir.y *= -1;
			normal.dir.z *= -1;
		}
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

int	normalized_color(int color, t_vector normal, t_vector ray)
{
	double	ratio;
	double	ray_len;

	ray_len = sqrt(dot_product(ray, ray));
	ray.x /= ray_len;
	ray.y /= ray_len;
	ray.z /= ray_len;
	ratio = dot_product(normal, ray);
	return (get_rgba(fabs(ratio * get_r(color)), fabs(ratio * get_g(color)),
				fabs(ratio * get_b(color)), 255));
}
