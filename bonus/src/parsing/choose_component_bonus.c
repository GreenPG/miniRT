/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_component_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:01:02 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/02 16:59:54 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	choose_component_part3(t_scene **scene, char *line)
{
	if (ft_strncmp(line, "sp ", 2) == 0)
	{	
		if (init_obj(line, &(*scene)->obj_list, sphere) == 1)
		{
			add_obj_error(scene);
			return ;
		}
	}
	else if (ft_strncmp(line, "pl ", 2) == 0)
	{
		if (init_obj(line, &(*scene)->obj_list, plane) == 1)
		{
			add_obj_error(scene);
			return ;
		}
	}
	else if (ft_strncmp(line, "cy ", 2) == 0)
	{	
		if (init_obj(line, &(*scene)->obj_list, cylinder) == 1)
		{
			add_obj_error(scene);
			return ;
		}
	}
	return ;
}

static void	choose_component_part2(t_scene **scene, char *line)
{
	if (ft_strncmp(line, "C ", 2) == 0)
	{	
		if ((*scene)->camera)
		{
			ft_error("Scene must have only one camera\n");
			*scene = NULL;
			return ;
		}
		(*scene)->camera = init_camera(line);
	}
	else if (ft_strncmp(line, "L ", 2) == 0)
	{
		if (!(*scene)->light_list)
			(*scene)->light_list = init_light_list(line);
		else
				add_light(&(*scene)->light_list, line);
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
	if (ft_strncmp(line + i, "A ", 2) == 0)
	{
		if ((*scene)->ambiant_l)
		{
			ft_error("Scene must have only one ambiant light\n");
			*scene = NULL;
			return ;
		}
		(*scene)->ambiant_l = init_ambiant_l(line + i);
	}
	else
		choose_component_part2(scene, line + i);
	return ;
}
