/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:46:52 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/01 14:47:18 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

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

t_normal	get_normal(t_obj_list *nearest, t_vector ray, double distance)
{
	t_normal	normal;

	if (nearest->type == sphere)
		normal = get_sphere_normal(nearest->sphere, ray, distance);
	if (nearest->type == plane)
		normal = get_plane_normal(nearest->plane, ray, distance);
	if (nearest->type == cylinder)
		normal = get_cylinder_normal(nearest->cylinder, ray, distance);
	return (normal);
}
