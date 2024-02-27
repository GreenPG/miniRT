/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 09:05:27 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/27 14:01:02 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	sphere_obj(t_obj_list *obj, char *line)
{
	obj->plane = NULL;
	obj->cylinder = NULL;
	obj->sphere = init_sphere(line);
	obj->ellipsoid = NULL;
	obj->triangle = NULL;
	obj->tex = NULL;
	obj->bump_map = NULL;
	if (!obj->sphere)
		return (1);
	return (0);
}

int	plane_obj(t_obj_list *obj, char *line)
{
	obj->sphere = NULL;
	obj->cylinder = NULL;
	obj->triangle = NULL;
	obj->plane = init_plane(line);
	obj->ellipsoid = NULL;
	obj->tex = NULL;
	obj->bump_map = NULL;
	if (!obj->plane)
		return (1);
	return (0);
}

int	cylinder_obj(t_obj_list *obj, char *line)
{
	obj->plane = NULL;
	obj->sphere = NULL;
	obj->ellipsoid = NULL;
	obj->triangle = NULL;
	obj->cylinder = init_cylinder(line);
	obj->tex = NULL;
	obj->bump_map = NULL;
	if (!obj->cylinder)
		return (1);
	return (0);
}

int	ellipsoid_obj(t_obj_list *obj, char *line)
{
	obj->plane = NULL;
	obj->sphere = NULL;
	obj->cylinder = NULL;
	obj->triangle = NULL;
	obj->ellipsoid = init_ellipsoid(line);
	obj->tex = NULL;
	obj->bump_map = NULL;
	if (!obj->ellipsoid)
		return (1);
	return (0);
}

int	triangle_obj(t_obj_list *obj, char *line)
{
	obj->plane = NULL;
	obj->sphere = NULL;
	obj->cylinder = NULL;
	obj->ellipsoid = NULL;
	obj->triangle = init_triangle(line);
	obj->tex = NULL;
	obj->bump_map = NULL;
	if (!obj->triangle)
		return (1);
	return (0);
}
