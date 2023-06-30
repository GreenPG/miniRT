/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:35:45 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/30 09:10:39 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static int	check_cylinder_part_2(char *str)
{	
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i])
		return (1);
	return (0);
}

static int	check_cylinder(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 2;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (check_triple_float(str, &i) == 1)
		return (1);
	pass_to_next_element(str, &i);
	if (check_triple_float(str, &i) == 1)
		return (1);
	pass_to_next_element(str, &i);
	if (check_int(str, &i) == 1)
		return (1);
	pass_to_next_element(str, &i);
	if (check_int(str, &i) == 1)
		return (1);
	pass_to_next_element(str, &i);
	if (check_triple_int(str, &i) == 1)
		return (1);
	if (check_cylinder_part_2(&str[i]))
		return (1);
	return (0);
}

static	t_cylinder	*init_cylinder_part3(t_cylinder *cylinder, char *str)
{
	int			*rgb;

	rgb = get_color_values(str);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[2] < 0
		|| rgb[2] > 255)
	{
		ft_error("Error\nWrong color\n");
		free(rgb);
		free_cylinder(&cylinder);
		return (NULL);
	}
	cylinder->color = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	free(rgb);
	cylinder->hit_body = false;
	return (cylinder);
}

static t_cylinder	*init_cylinder_part2(t_cylinder *cylinder, char *str, int i)
{
	if (!cylinder->origin || cylinder->direction->x < -1.0
		|| cylinder->direction->x > 1.0 || cylinder->direction->y
		< -1.0 || cylinder->direction->y > 1.0 || cylinder->direction->z
		< -1.0 || cylinder->direction->z > 1.0 || !cylinder->origin)
	{
		ft_error("Error\nWrong cylinder parameters\n");
		free_cylinder(&cylinder);
		return (NULL);
	}
	pass_to_next_element(str, &i);
	cylinder->diameter = ft_atof(str + i);
	pass_to_next_element(str, &i);
	cylinder->height = ft_atof(str + i);
	if (cylinder->height <= 0 || cylinder->diameter <= 0)
	{
		ft_error("Error\nCylinder diameter and height must be superior to 0\n");
		free_cylinder(&cylinder);
		return (NULL);
	}
	pass_to_next_element(str, &i);
	cylinder = init_cylinder_part3(cylinder, &str[i]);
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
	{
		ft_error("Error\nMalloc error\n");
		return (NULL);
	}
	i = 2;
	while (ft_isspace(str[i]))
		i++;
	cylinder->origin = init_vector(str + i);
	pass_to_next_element(str, &i);
	cylinder->direction = init_vector(str + i);
	vector_norm(cylinder->direction);
	cylinder = init_cylinder_part2(cylinder, str, i);
	return (cylinder);
}
