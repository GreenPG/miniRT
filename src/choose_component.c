/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_component.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:01:02 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/20 14:01:46 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	choose_component_part3(t_scene *scene, char *line)
{
	if (ft_strncmp(line, "sp ", 2) == 0)
	{	
		init_obj(line, &scene->obj_list, sphere);
		if (!scene->obj_list)
			add_obj_error(scene);
	}
	else if (ft_strncmp(line, "pl ", 2) == 0)
	{	
		init_obj(line, &scene->obj_list, plane);
		if (!scene->obj_list)
			add_obj_error(scene);
	}
	else if (ft_strncmp(line, "cy ", 2) == 0)
	{	
		init_obj(line, &scene->obj_list, cylinder);
		if (!scene->obj_list)
			add_obj_error(scene);
	}
	return ;
}

static void	choose_component_part2(t_scene *scene, char *line)
{
	if (ft_strncmp(line, "C ", 2) == 0)
	{	
		if (scene->camera)
		{
			ft_error("Scene must have only one camera\n");
			scene = NULL;
			return ;
		}
		scene->camera = init_camera(line);
	}
	else if (ft_strncmp(line, "L ", 2) == 0)
	{
		if (scene->light)
		{
			ft_error("Scene must have only one light\n");
			scene = NULL;
			return ;
		}
		scene->light = init_light(line);
	}
	else
		choose_component_part3(scene, line);
	return ;
}

void	choose_component(char *line, t_scene *scene)
{
	int	i;

	if (!line || !scene)
		return ;
	i = 0;
	while (line[i] && ft_isspace(line[i]) == 1)
		i++;
	if (ft_strncmp(line + i, "A ", 2) == 0)
	{
		if (scene->ambiant_l)
		{
			ft_error("Scene must have only one ambiant light\n");
			scene = NULL;
			return ;
		}
		scene->ambiant_l = init_ambiant_l(line + i);
	}
	else
		choose_component_part2(scene, line + i);
	return ;
}