/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:16:59 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/16 08:04:11 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static int	checkerboard_sphere(t_vector vec, t_sphere *sphere)
{
	double alpha;
	double beta;

	t_vector	tmp;

	tmp.x = sphere->up->x;
	tmp.y = sphere->up->y;
	tmp.z = sphere->up->z;
	t_cyl_calc	data;

	data.front.x = 0.0000001;
	data.front.y = 1;
	data.front.z = 0.0000001;
	data.cross = vector_cross(*sphere->direction, data.front);
	vector_norm(&data.cross);
	data.angle = acos(dot_product(*sphere->direction, data.front)
			/ (sqrt(dot_product(*sphere->direction, *sphere->direction))
				* sqrt(dot_product (data.front, data.front))));
	rotate_around_axis(&vec, data.cross, -data.angle);
	rotate_around_axis(&tmp, data.cross, -data.angle);
	data.front.x = 0.0000001;
	data.front.y = 0.0000001;
	data.front.z = 1;
	if (dot_product(tmp, data.front) > -1 + 1e-6)
	{
		data.cross = vector_cross(tmp, data.front);
		vector_norm(&data.cross);
		data.angle = acos(dot_product(tmp, data.front)
				/ (sqrt(dot_product(tmp, tmp))
					* sqrt(dot_product (data.front, data.front))));
		rotate_around_axis(&vec, data.cross, data.angle);
	}
	alpha = atan2(vec.x, vec.y);
	beta = acos(vec.z);
	if ((int)(floor(alpha * M_PI) + floor(beta * M_PI)) % 2 == 0)
		return (get_rgba(255,255,255,0));
	return (0);
}

int	checkerboard_plane(t_vector vec, t_obj_list *nearest, t_camera *camera)
{
	t_plane *plane;

	plane = nearest->plane;
	t_vector	tmp;

	tmp.x = plane->up->x;
	tmp.y = plane->up->y;
	tmp.z = plane->up->z;
	t_cyl_calc	data;

	data.front.x = 0.0000001;
	data.front.y = 1;
	data.front.z = 0.0000001;
	data.cross = vector_cross(*plane->direction, data.front);
	vector_norm(&data.cross);
	data.angle = acos(dot_product(*plane->direction, data.front)
			/ (sqrt(dot_product(*plane->direction, *plane->direction))
				* sqrt(dot_product (data.front, data.front))));
	rotate_around_axis(&vec, data.cross, -data.angle);
	rotate_around_axis(&tmp, data.cross, -data.angle);
	data.front.x = 0.0000001;
	data.front.y = 0.0000001;
	data.front.z = 1;
	if (dot_product(tmp, data.front) > -1 + 1e-6)
	{
		data.cross = vector_cross(tmp, data.front);
		vector_norm(&data.cross);
		data.angle = acos(dot_product(tmp, data.front)
				/ (sqrt(dot_product(tmp, tmp))
					* sqrt(dot_product (data.front, data.front))));
		rotate_around_axis(&vec, data.cross, data.angle);
	}
	if ((int)(floor(vec.x) + floor(vec.z)) % 2 == 0)
		return (get_rgba(255,255,255,0));
	return (0);
	(void)camera;
}

int	checkerboard_cylinder(t_vector vec, t_cylinder *cylinder, t_camera *camera)
{	
	t_vector	tmp;

	tmp.x = cylinder->up->x;
	tmp.y = cylinder->up->y;
	tmp.z = cylinder->up->z;
	t_cyl_calc	data;

	data.front.x = 0.0000001;
	data.front.y = 1;
	data.front.z = 0.0000001;
	vec.x -= cylinder->origin->x;
	vec.y -= cylinder->origin->y;
	vec.z -= cylinder->origin->z;
	data.cross = vector_cross(*cylinder->direction, data.front);
	vector_norm(&data.cross);
	data.angle = acos(dot_product(*cylinder->direction, data.front)
			/ (sqrt(dot_product(*cylinder->direction, *cylinder->direction))
				* sqrt(dot_product (data.front, data.front))));
	rotate_around_axis(&vec, data.cross, -data.angle);
	rotate_around_axis(&tmp, data.cross, -data.angle);
	data.front.x = 0.0000001;
	data.front.y = 0.0000001;
	data.front.z = 1;
	if (dot_product(tmp, data.front) > -1 + 1e-6)
	{
		data.cross = vector_cross(tmp, data.front);
		vector_norm(&data.cross);
		data.angle = acos(dot_product(tmp, data.front)
				/ (sqrt(dot_product(tmp, tmp))
					* sqrt(dot_product (data.front, data.front))));
		rotate_around_axis(&vec, data.cross, data.angle);
	}
	if ((int)floor(vec.z) % 2 == 0)
	{
		if ((int)(floor(vec.x) + floor(vec.y)) % 2 == 0)
			return (get_rgba(255,255,255,0));
		return (0);
	}
	else
	{
		if ((int)(floor(vec.x) + floor(vec.y)) % 2 == 0)
			return (0);
		return (get_rgba(255,255,255,0));
	}
	(void)camera;
}

int	checkerboard_ellipsoid(t_vector vec, t_ellipsoid *ellipsoid, t_camera *camera)
{
	t_vector	tmp;

	tmp.x = ellipsoid->up->x;
	tmp.y = ellipsoid->up->y;
	tmp.z = ellipsoid->up->z;
	t_cyl_calc	data;

	data.front.x = 0.0000001;
	data.front.y = 1;
	data.front.z = 0.0000001;
	vec.x -= ellipsoid->origin->x;	if (dot_product(tmp, data.front) > -1 + 1e-6)
	vec.y -= ellipsoid->origin->y;
	vec.z -= ellipsoid->origin->z;
	data.cross = vector_cross(*ellipsoid->direction, data.front);
	vector_norm(&data.cross);
	data.angle = acos(dot_product(*ellipsoid->direction, data.front)
			/ (sqrt(dot_product(*ellipsoid->direction, *ellipsoid->direction))
				* sqrt(dot_product (data.front, data.front))));
	rotate_around_axis(&vec, data.cross, -data.angle);
	rotate_around_axis(&tmp, data.cross, -data.angle);
	data.front.x = 0.0000001;
	data.front.y = 0.0000001;
	data.front.z = 1;
	if (dot_product(tmp, data.front) > -1 + 1e-6)
	{
		data.cross = vector_cross(tmp, data.front);
		vector_norm(&data.cross);
		data.angle = acos(dot_product(tmp, data.front)
				/ (sqrt(dot_product(tmp, tmp))
					* sqrt(dot_product (data.front, data.front))));
		rotate_around_axis(&vec, data.cross, data.angle);
	}
	if ((int)floor(vec.z) % 2 == 0)
	{
		if ((int)(floor(vec.x) + floor(vec.y)) % 2 == 0)
			return (get_rgba(255,255,255,0));
		return (0);
	}
	else
	{
		if ((int)(floor(vec.x) + floor(vec.y)) % 2 == 0)
			return (0);
		return (get_rgba(255,255,255,0));
	}
	(void)camera;
}

int	get_checkerboard(t_obj_list *nearest, t_vector ray, t_normal normal, t_camera *camera)
{
	int			color;

	color = 0;
	if (nearest->type == sphere)
		color = checkerboard_sphere(normal.dir, nearest->sphere);
	if (nearest->type == plane)
		color = checkerboard_plane(normal.origin, nearest, camera);
	if (nearest->type == cylinder)
	 	color = checkerboard_cylinder(normal.origin, nearest->cylinder, camera);
	if (nearest->type == ellipsoid)
	 	color = checkerboard_ellipsoid(normal.origin, nearest->ellipsoid, camera);
	(void)ray;
	(void)nearest;
	return (color);
}