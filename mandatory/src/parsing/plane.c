/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:15:50 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/30 09:02:41 by gpasquet         ###   ########.fr       */
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
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i])
		return (1);
	return (0);
}

static int	check_plane_direction(t_vector *direction)
{
	if (!direction
		|| direction->x < -1.0 || direction->x > 1.0
		|| direction->y < -1.0 || direction->y > 1.0
		|| direction->z < -1.0 || direction->z > 1.0
		|| (direction->x == 0 && direction->y == 0 && direction->z == 0))
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
		ft_error("Error\nWrong color");
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
		ft_error("Error\nMalloc error\n");
		return (NULL);
	}
	i = 2;
	while (ft_isspace(str[i]))
		i++;
	plane->origin = init_vector(str + i);
	pass_to_next_element(str, &i);
	plane->direction = init_vector(str + i);
	if (check_plane_direction(plane->direction) == 1 || !plane->origin)
	{
		free_plane(&plane);
		return (NULL);
	}
	plane = init_plane_part2(plane, str, i);
	return (plane);
}
