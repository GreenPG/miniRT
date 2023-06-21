/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:59:12 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/21 07:25:51 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

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
	if (type == triangle)
	{
		if (triangle_obj(obj, line) == 1)
			return (1);
	}
	obj->bump_map = NULL;
	obj->tex = NULL;
	if (get_bonus_data(&obj, line) == 1)
		return (1);
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
