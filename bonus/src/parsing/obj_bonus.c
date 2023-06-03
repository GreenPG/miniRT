/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:59:12 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/03 16:43:18 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static int	sphere_obj(t_obj_list *obj, char *line)
{
	obj->plane = NULL;
	obj->cylinder = NULL;
	obj->sphere = init_sphere(line);
	obj->ellipsoid = NULL;
	obj->pattern = obj->sphere->pattern;
	if (!obj->sphere)
	{
		free(obj);
		return (1);
	}
	return (0);
}

static int	plane_obj(t_obj_list *obj, char *line)
{
	obj->sphere = NULL;
	obj->cylinder = NULL;
	obj->plane = init_plane(line);
	obj->ellipsoid = NULL;
	obj->pattern = obj->plane->pattern;
	if (!obj->plane)
	{
		free(obj);
		return (1);
	}
	return (0);
}

static int	cylinder_obj(t_obj_list *obj, char *line)
{
	obj->plane = NULL;
	obj->sphere = NULL;
	obj->cylinder = init_cylinder(line);
	obj->ellipsoid = NULL;
	obj->pattern = obj->cylinder->pattern;
	if (!obj->cylinder)
	{
		free(obj);
		return (1);
	}
	return (0);
}

static int	ellipsoid_obj(t_obj_list *obj, char *line)
{
	obj->plane = NULL;
	obj->sphere = NULL;
	obj->cylinder = NULL;
	obj->ellipsoid = init_ellipsoid(line);
	obj->pattern = obj->ellipsoid->pattern;
	if (!obj->ellipsoid)
	{
		free(obj);
		return (1);
	}
	return (0);
}

static int	init_obj2(t_obj_list *obj, char *line, t_type type,
		t_obj_list **list_ptr)
{
	if (type == cylinder)
	{
		if (cylinder_obj(obj, line) == 1)
			return (1);
	}
	if (type == ellipsoid)
	{
		if (ellipsoid_obj(obj, line) == 1)
			return (1);
	}
	obj->next = NULL;
	add_obj(list_ptr, obj);
	return (0);
}

int	init_obj(char *line, t_obj_list **list_ptr, t_type type)
{
	t_obj_list	*obj;

	if (!line)
		return (1);
	obj = malloc(sizeof(t_obj_list));
	if (!obj)
	{
		*list_ptr = NULL;
		return (1);
	}
	obj->type = type;
	obj->hitted = 0;
	if (type == sphere)
	{
		if (sphere_obj(obj, line) == 1)
			return (1);
	}
	if (type == plane)
	{
		if (plane_obj(obj, line) == 1)
			return (1);
	}
	return (init_obj2(obj, line, type, list_ptr));
}		
