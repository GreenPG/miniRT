/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 09:05:27 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/16 09:06:13 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

int	sphere_obj(t_obj_list *obj, char *line)
{
	obj->plane = NULL;
	obj->cylinder = NULL;
	obj->sphere = init_sphere(line);
	obj->ellipsoid = NULL;
	obj->triangle = NULL;
	if (!obj->sphere)
	{
		free(obj);
		return (1);
	}
	return (0);
}

int	plane_obj(t_obj_list *obj, char *line)
{
	obj->sphere = NULL;
	obj->cylinder = NULL;
	obj->triangle = NULL;
	obj->plane = init_plane(line);
	obj->ellipsoid = NULL;
	if (!obj->plane)
	{
		free(obj);
		return (1);
	}
	return (0);
}

int	cylinder_obj(t_obj_list *obj, char *line)
{
	obj->plane = NULL;
	obj->sphere = NULL;
	obj->ellipsoid = NULL;
	obj->triangle = NULL;
	obj->cylinder = init_cylinder(line);
	if (!obj->cylinder)
	{
		free(obj);
		return (1);
	}
	return (0);
}

int	ellipsoid_obj(t_obj_list *obj, char *line)
{
	obj->plane = NULL;
	obj->sphere = NULL;
	obj->cylinder = NULL;
	obj->triangle = NULL;
	obj->ellipsoid = init_ellipsoid(line);
	if (!obj->ellipsoid)
	{
		free(obj);
		return (1);
	}
	return (0);
}

int	triangle_obj(t_obj_list *obj, char *line)
{
	obj->plane = NULL;
	obj->sphere = NULL;
	obj->cylinder = NULL;
	obj->ellipsoid = NULL;
	obj->triangle = init_triangle(line);
	if (!obj->triangle)
	{
		free(obj);
		return (1);
	}
	return (0);
}
