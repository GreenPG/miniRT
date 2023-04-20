/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:42:16 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/20 15:56:45 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	free_obj_list(t_obj_list **list)
{
	t_obj_list	*tmp;

	if (!list || !*list)
		return ;
	while ((*list)->next)
	{
		if ((*list)->type == sphere)
			free_sphere((*list)->obj);
		if ((*list)->type == plane)
			free_plane((*list)->obj);
		if ((*list)->type == cylinder)
			free_cylinder((*list)->obj);
		tmp = *list;
		*list = (*list)->next;
		tmp = NULL;
	}
	return ;
}

void	free_scene(t_scene **scene)
{
	if (!scene || !*scene)
		return ;
	if ((*scene)->ambiant_l) 
	{
		free((*scene)->ambiant_l);
		(*scene)->ambiant_l = NULL;
	}
	if ((*scene)->camera)
		free_camera(&(*scene)->camera);
	if ((*scene)->light)
		free_light(&(*scene)->light);
	if ((*scene)->obj_list)
		free_obj_list(&(*scene)->obj_list);
	free(*scene);
	*scene = NULL;
	return ;
}
