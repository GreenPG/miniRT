/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:15:50 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/27 13:54:43 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

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
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\0')
		return (0);
	if (check_bonus_var(&str[i]) == 1)
		return (1);
	return (0);
}

static void	null_all_plane(t_plane *plane_ptr)
{
	plane_ptr->origin = NULL;
	plane_ptr->direction = NULL;
	plane_ptr->up = NULL;
}

static int	check_plane_direction(t_vector *direction)
{
	if (!direction
		|| direction->x < -1.0 || direction->x > 1.0
		|| direction->y < -1.0 || direction->y > 1.0
		|| direction->z < -1.0 || direction->z > 1.0
		|| (direction->x == 0 && direction->y == 0 && direction->z == 0))
	{
		ft_error("Error\nDirection values must be between -1 and 1\n");
		return (1);
	}
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
		ft_error("Error\nWrong color\n");
		free(rgb);
		free_plane(&plane);
		return (NULL);
	}
	plane->colors = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	free(rgb);
	plane->up = get_up(plane->direction);
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
	null_all_plane(plane);
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
