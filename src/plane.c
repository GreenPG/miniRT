/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:15:50 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/15 10:48:21 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	free_plane(t_plane **plane)
{
	if (!plane || !*plane)
		return ;
	if ((*plane)->direction)
	{
		free((*plane)->direction);
		(*plane)->direction = NULL;
	}
	if ((*plane)->origin)
	{
		free((*plane)->origin);
		(*plane)->origin = NULL;
	}
	free(*plane);
	*plane = NULL;
	return ;
}
double	plane_hit(t_plane *obj, t_vector ray)
{
	double	is_hitted;
	double	t;
	
	is_hitted = dot_product(*obj->direction, ray);	
	if (is_hitted > 1e-6 || is_hitted < 1e-6)
	{
		//remplacer par dot product mais pour linstat jlai pas update donc voila
		t = obj->origin->x * obj->direction->x + obj->origin->y * obj->direction->y + obj->origin->z * obj->direction->z;
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
	rgb = get_color_values(str + i);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[2] < 0
		|| rgb[2] > 255)
	{
		free(rgb);
		free_plane(&plane);
		return (NULL);
	}
	plane->colors = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	free(rgb);
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
	plane->origin = init_vector(str + i);
	pass_to_next_element(str, &i);
	plane->direction = init_vector(str + i);
	if (!plane->direction || plane->direction->x < -1.0 || plane->direction->x > 1.0 || plane->direction->y < -1.0 || plane->direction->y > 1.0 ||  plane->direction->z < -1.0 || plane->direction->z > 1.0 || !plane->origin)
	{
		free_plane(&plane);
		return (NULL);
	}
	plane = init_plane_part2(plane, str, i);
	return (plane);
}
