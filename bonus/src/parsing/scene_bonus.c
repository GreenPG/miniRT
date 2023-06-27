/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:00:15 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/27 08:59:40 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_scene	*init_scene2(t_scene *scene)
{
	scene->camera = NULL;
	scene->ambiant_l = NULL;
	scene->light_list = NULL;
	scene->obj_list = NULL;
	scene->up->x = 0;
	scene->up->y = 0;
	scene->up->z = 1;
	scene->direction->x = 0;
	scene->direction->y = 1;
	scene->direction->z = 0;
	return (scene);
}

t_scene	*init_scene(void)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
	{
		ft_error("Error\nMalloc error\n");
		return (NULL);
	}
	scene->up = malloc(sizeof(t_vector));
	scene->direction = malloc(sizeof(t_vector));
	if (!scene->up || !scene->direction)
	{
		ft_error("Error\nMalloc error\n");
		return (NULL);
	}
	return (init_scene2(scene));
}
