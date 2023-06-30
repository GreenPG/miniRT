/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_component.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:01:02 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/30 11:35:30 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	choose_component_part4(t_scene **scene, char *line)
{
	if (ft_strncmp(line, "cy", 2) == 0 && (!line[2]
			|| ft_isspace(line[2]) == 1))
	{	
		if (init_obj(line, &(*scene)->obj_list, cylinder) == 1)
		{
			add_obj_error(scene);
			return ;
		}
	}
	return ;
}

static void	choose_component_part3(t_scene **scene, char *line)
{
	if (ft_strncmp(line, "sp", 2) == 0 && (!line[2]
			|| ft_isspace(line[2]) == 1))
	{	
		if (init_obj(line, &(*scene)->obj_list, sphere) == 1)
		{
			add_obj_error(scene);
			return ;
		}
	}
	else if (ft_strncmp(line, "pl", 2) == 0 && (!line[2]
			|| ft_isspace(line[2]) == 1))
	{
		if (init_obj(line, &(*scene)->obj_list, plane) == 1)
		{
			add_obj_error(scene);
			return ;
		}
	}
	else
		choose_component_part4(scene, line);
	return ;
}

static void	choose_component_part2(t_scene **scene, char *line)
{
	if (ft_strncmp(line, "C", 1) == 0 && (!line[1]
			|| ft_isspace(line[1]) == 1))
	{	
		if ((*scene)->camera)
		{
			ft_error("Error\nScene must have only one camera\n");
			free_scene(scene);
			return ;
		}
		(*scene)->camera = init_camera(line);
	}
	else if (ft_strncmp(line, "L", 1) == 0 && (!line[1]
			|| ft_isspace(line[1]) == 1))
	{
		if ((*scene)->light)
		{
			ft_error("Error\nScene must have only one light\n");
			free_scene(scene);
			return ;
		}
		(*scene)->light = init_light(line);
	}
	else
		choose_component_part3(scene, line);
	return ;
}

void	choose_component(char *line, t_scene **scene)
{
	int	i;

	if (!line || !*scene)
		return ;
	i = 0;
	while (line[i] && ft_isspace(line[i]) == 1)
		i++;
	if (ft_strncmp(line + i, "A", 1) == 0 && (!line[i + 1]
			|| ft_isspace(line[i + 1]) == 1))
	{
		if ((*scene)->ambiant_l)
		{
			ft_error("Error\nScene must have only one ambiant light\n");
			free_scene(scene);
			return ;
		}
		(*scene)->ambiant_l = init_ambiant_l(line + i);
	}
	else
		choose_component_part2(scene, line + i);
	return ;
}
