/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:59:12 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/15 15:05:40 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	add_obj(t_obj_list **list_ptr, t_obj_list *obj)
{
	t_obj_list	*tmp;
	t_obj_list	*prev;

	if (*list_ptr)
	{
		tmp = *list_ptr;
		while (tmp)
		{	
			prev = tmp;
			tmp = tmp->next;
		}
		tmp = obj;
		prev->next = obj;
	}
	else
		*list_ptr = obj;
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
	if (type == sphere)
	{
		obj->plane = NULL;
		obj->cylinder = NULL;
		obj->sphere = init_sphere(line);
		if (!obj->sphere)
		{
			free(obj);
			return (1);
		}
	}
	else if (type == plane)
	{
		obj->sphere = NULL;
		obj->cylinder = NULL;
		obj->plane = init_plane(line);
		if (!obj->plane)
		{
			free(obj);
			return (1);
		}
	}
	else if (type == cylinder)
	{
		obj->plane = NULL;
		obj->sphere = NULL;
		obj->cylinder = init_cylinder(line);
		if (!obj->cylinder)
		{
			free(obj);
			return (1);
		}
	}
	obj->hitted = 0;
	obj->next = NULL;
	add_obj(list_ptr, obj);
	return (0);
}		

void	add_obj_error(t_scene **scene)
{
	ft_error("Error when adding an object\n");
	free_scene(scene);
	return ;
}
