/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:42:16 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/23 11:54:21 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	free_tex(t_obj_list *obj)
{
	if (obj->tex)
		mlx_delete_texture(obj->tex);
	if (obj->bump_map)
		mlx_delete_texture(obj->bump_map);
}

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
		if ((*list)->type == ellipsoid)
			free_ellipsoid(&(*list)->ellipsoid);
		if ((*list)->type == triangle)
			free_triangle(&(*list)->triangle);
		if ((*list)->tex)
			free_tex(*list);
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
		tmp = NULL;
	}
	return ;
}

void	free_camera(t_camera **camera)
{
	if (!camera || !*camera)
		return ;
	if ((*camera)->origin)
		free((*camera)->origin);
	if ((*camera)->direction)
		free((*camera)->direction);
	if ((*camera)->rays)
		free_rays((*camera)->rays);
	free(*camera);
	*camera = (NULL);
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
	if ((*scene)->light_list)
		free_light_list((*scene)->light_list);
	if ((*scene)->obj_list)
		free_obj_list(&(*scene)->obj_list);
	if ((*scene)->up)
		free((*scene)->up);
	if ((*scene)->direction)
		free((*scene)->direction);
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
