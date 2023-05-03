/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:15:50 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/02 13:03:12 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

double	plane_hit(void *plane, t_vector ray)
{
	t_plane	*obj;
	double	is_hitted;
	double	t;
	
	obj = plane;
	is_hitted = dot_product(*obj->vector, ray);	
	if (is_hitted > 1e-50)
	{
		t = obj->vector->x_o * obj->vector->x_d + obj->vector->y_o * obj->vector->y_d + obj->vector->z_o * obj->vector->z_d;
		t = t / is_hitted;
		if (t >= 0)// peut etre t < view_distance
			return (t);
		else 
			return (INFINITY);
	}
	return (INFINITY);
}

static int	check_plane(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 2;
	while (ft_isspace(str[i]))
		i++;
	if (check_triple_float(str, &i) == 1)
		return (1);
	pass_to_next_element(str, &i);
	if (check_triple_float(str, &i) == 1)
		return (1);
	pass_to_next_element(str, &i);
	if (check_triple_int(str, &i) == 1)
		return (1);
	return (0);
}

t_plane	*init_plane_part2(t_plane *plane, char *str, int i)
{
	int		*rgb;

	pass_to_next_element(str, &i);
	pass_to_next_element(str, &i);
	rgb = get_color_values(str + i);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[2] < 0
		|| rgb[2] > 255)
	{
		free(rgb);
		free(plane);
		return (NULL);
	}
	plane->colors = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	return (plane);
}

t_plane	*init_plane(char *str)
{
	t_plane	*plane;
	int		i;

	if (!str || check_plane(str) == 1)
		return (NULL);
	plane = malloc(sizeof(t_plane));
	if (!plane)
	{
		ft_error("Error: fatal\n");
		return (NULL);
	}
	i = 2;
	while (ft_isspace(str[i]))
		i++;
	plane->vector = init_vector(str + i);
	if (!plane->vector)
	{
		free(plane);
		return (NULL);
	}
	plane = init_plane_part2(plane, str, i);
	return (plane);
}
