/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:16:59 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/03 16:43:10 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static int	checkerboard_sphere(t_vector vec, t_camera *camera)
{
	double alpha;
	double beta;

	alpha = atan2(vec.x, vec.y) * (42 / M_PI) + camera->alpha;
	beta = acos(vec.z) * (42 / M_PI) + camera->beta;
	if ((int)(floor(alpha) + floor(beta)) % 2 == 0)
		return (get_rgba(255,255,255,0));
	return (0);
}

int	checkerboard_plane(t_vector vec, t_obj_list *nearest, t_camera *camera)
{
	t_plane *plane;

	plane = nearest->plane;
	vec.x -= plane->origin->x + 0.00001;
	vec.y -= plane->origin->y + 0.00001;
	vec.z -= plane->origin->z + 0.00001;
	vector_rot_y(&vec, camera->beta * (M_PI / 180));
	vector_rot_x(&vec, -camera->alpha * (M_PI / 180));
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
	return (0);
}

int	checkerboard_cylinder(t_vector vec, t_cylinder *cyl, t_camera *camera)
{	
	vec.x = vec.x - cyl->origin->x;
	vec.y = vec.y - cyl->origin->y;
	vec.z = vec.z - cyl->origin->z;
	vector_rot_y(&vec, camera->beta * (M_PI / 180));
	vector_rot_x(&vec, -camera->alpha * (M_PI / 180));
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

int	checkerboard_ellipsoid(t_vector vec, t_ellipsoid *ell, t_camera *camera)
{	
	vec.x = vec.x - ell->origin->x;
	vec.y = vec.y - ell->origin->y;
	vec.z = vec.z - ell->origin->z;
	vector_rot_y(&vec, camera->beta * (M_PI / 180));
	vector_rot_x(&vec, -camera->alpha * (M_PI / 180));
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
		color = checkerboard_sphere(normal.dir, camera);
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