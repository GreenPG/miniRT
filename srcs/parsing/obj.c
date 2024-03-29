/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:59:12 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/30 08:43:29 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	null_all_obj(t_obj_list *obj, t_type type)
{
	obj->type = type;
	obj->next = NULL;
	obj->has_bump = 0;
	obj->pattern = plain;
	obj->ks = 0;
	obj->sp_e = 0;
	obj->hitted = 0;
}

static int	init_obj3(t_obj_list *obj, char *line, t_type type,
		t_obj_list **list_ptr)
{
	if (type == triangle)
	{
		if (triangle_obj(obj, line) == 1)
			return (1);
	}
	obj->bump_map = NULL;
	obj->tex = NULL;
	if (get_data(&obj, line) == 1)
	{
		if (obj->tex)
			mlx_delete_texture(obj->tex);
		if (obj->bump_map)
			mlx_delete_texture(obj->bump_map);
		return (1);
	}
	add_obj(list_ptr, obj);
	return (0);
}

static int	init_obj2(t_obj_list *obj, char *line, t_type type,
		t_obj_list **list_ptr)
{
	if (type == plane)
	{
		if (plane_obj(obj, line) == 1)
			return (1);
	}
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
	return (init_obj3(obj, line, type, list_ptr));
}

int	init_obj(char *line, t_obj_list **list_ptr, t_type type)
{
	t_obj_list	*obj;

	if (!line)
		return (1);
	obj = malloc(sizeof(t_obj_list));
	if (!obj)
	{
		ft_error("Error\nMalloc error\n");
		return (1);
	}
	null_all_obj(obj, type);
	if (type == sphere)
	{
		if (sphere_obj(obj, line) == 1)
		{
			free_obj_list(&obj);
			return (1);
		}
	}
	if (init_obj2(obj, line, type, list_ptr) == 1)
	{
		free_obj_list(&obj);
		return (1);
	}
	return (0);
}		
