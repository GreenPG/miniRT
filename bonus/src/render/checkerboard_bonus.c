/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:16:59 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/23 11:18:36 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static int	checkerboard_sphere(t_vector vec, t_sphere *sphere)
{
	double		alpha;
	double		beta;

	vec = camera_to_object_space(vec, *sphere->direction, *sphere->up);
	alpha = atan2(vec.x, vec.y);
	beta = acos(vec.z);
	if ((int)(floor(alpha * M_PI) + floor(beta * M_PI)) % 2 == 0)
		return (get_rgba(255, 255, 255, 0));
	return (0);
}

static int	checkerboard_plane(t_vector vec, t_plane *plane)
{
	vec.x -= plane->origin->x;
	vec.y -= plane->origin->y;
	vec.z -= plane->origin->z;
	vec = camera_to_object_space(vec, *plane->direction, *plane->up);
	if ((int)(floor(vec.x) + floor(vec.z)) % 2 == 0)
		return (get_rgba(255, 255, 255, 0));
	return (0);
}

static int	checkerboard_cylinder(t_vector vec, t_cylinder *cylinder)
{
	vec.x -= cylinder->origin->x;
	vec.y -= cylinder->origin->y;
	vec.z -= cylinder->origin->z;
	vec = camera_to_object_space(vec, *cylinder->direction, *cylinder->up);
	if ((int)floor(vec.z) % 2 == 0)
	{
		if ((int)(floor(vec.x) + floor(vec.y)) % 2 == 0)
			return (get_rgba(255, 255, 255, 0));
		return (0);
	}
	else
	{
		if ((int)(floor(vec.x) + floor(vec.y)) % 2 == 0)
			return (0);
		return (get_rgba(255, 255, 255, 0));
	}
}

static int	checkerboard_ellipsoid(t_vector vec, t_ellipsoid *ellipsoid)
{
	vec.x -= ellipsoid->origin->x;
	vec.y -= ellipsoid->origin->y;
	vec.z -= ellipsoid->origin->z;
	vec = camera_to_object_space(vec, *ellipsoid->direction, *ellipsoid->up);
	if ((int)floor(vec.z) % 2 == 0)
	{
		if ((int)(floor(vec.x) + floor(vec.y)) % 2 == 0)
			return (get_rgba(255, 255, 255, 0));
		return (0);
	}
	else
	{
		if ((int)(floor(vec.x) + floor(vec.y)) % 2 == 0)
			return (0);
		return (get_rgba(255, 255, 255, 0));
	}
}

int	get_checkerboard(t_obj_list *nearest, t_normal normal)
{
	int			color;

	color = 0;
	if (nearest->type == sphere)
		color = checkerboard_sphere(normal.dir, nearest->sphere);
	if (nearest->type == plane)
		color = checkerboard_plane(normal.origin, nearest->plane);
	if (nearest->type == cylinder)
		color = checkerboard_cylinder(normal.origin, nearest->cylinder);
	if (nearest->type == ellipsoid)
		color = checkerboard_ellipsoid(normal.origin, nearest->ellipsoid);
	if (nearest->type == triangle)
		color = checkerboard_triangle(normal.origin, nearest->triangle);
	return (color);
}
