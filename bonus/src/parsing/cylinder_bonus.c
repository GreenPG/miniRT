/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:35:45 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/16 10:27:02 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static	t_cylinder	*init_cylinder_part3(t_cylinder *cylinder)
{
	cylinder->hit_body = false;
	cylinder->up = malloc(sizeof(t_vector));
	cylinder->up->x = 0;
	cylinder->up->y = 0;
	cylinder->up->z = 1;
	cylinder->direction = malloc(sizeof(t_vector));
	cylinder->direction->x = 0;
	cylinder->direction->y = 1;
	cylinder->direction->z = 0;
	return (cylinder);
}

static t_cylinder	*init_cylinder_part2(t_cylinder *cylinder, char *str, int i)
{
	int			*rgb;

	pass_to_next_element(str, &i);
	cylinder->diameter = ft_atof(str + i);
	pass_to_next_element(str, &i);
	cylinder->height = ft_atof(str + i);
	if (cylinder->height <= 0 || cylinder->diameter <= 0)
	{
		ft_error("Cylinder diameter and height must be superior to 0\n");
		free_cylinder(&cylinder);
		return (NULL);
	}
	pass_to_next_element(str, &i);
	rgb = get_color_values(str + i);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[2] < 0
		|| rgb[2] > 255)
	{
		free(rgb);
		free_cylinder(&cylinder);
		return (NULL);
	}
	cylinder->color = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	free(rgb);
	cylinder = init_cylinder_part3(cylinder);
	return (cylinder);
}

t_cylinder	*init_cylinder(char *str)
{
	t_cylinder	*cylinder;
	int			i;

	if (!str || check_cylinder(str) == 1)
		return (NULL);
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	i = 2;
	while (ft_isspace(str[i]))
		i++;
	cylinder->origin = init_vector(str + i);
	pass_to_next_element(str, &i);
	cylinder->direction = init_vector(str + i);
	vector_norm(cylinder->direction);
	if (!cylinder->origin || cylinder->direction->x < -1.0
		|| cylinder->direction->x > 1.0 || cylinder->direction->y
		< -1.0 || cylinder->direction->y > 1.0 || cylinder->direction->z
		< -1.0 || cylinder->direction->z > 1.0 || !cylinder->origin)
	{
		free_cylinder(&cylinder);
		return (NULL);
	}
	cylinder = init_cylinder_part2(cylinder, str, i);
	return (cylinder);
}
