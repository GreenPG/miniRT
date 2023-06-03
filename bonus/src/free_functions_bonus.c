/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:42:16 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/02 15:00:09 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	free_obj_list(t_obj_list **list)
{
	t_obj_list	*tmp;

	if (!list || !*list)
		return ;
	while (*list)
	{
		if ((*list)->type == sphere)
			free_sphere(&(*list)->sphere);
		if ((*list)->type == plane)
			free_plane(&(*list)->plane);
		if ((*list)->type == cylinder)
			free_cylinder(&(*list)->cylinder);
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
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

void	free_all(t_data *data, t_scene *scene)
{
	if (data)
		free(data);
	if (scene)
		free_scene(&scene);
}
