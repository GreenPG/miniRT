/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:35:45 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/30 09:55:18 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_ellipsoid	*init_ellipsoid_part4(t_ellipsoid *ellipsoid,
		char *str, int i)
{
	int			*rgb;

	rgb = get_color_values(str + i);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[2] < 0
		|| rgb[2] > 255)
	{
		ft_error("Error\nWrong color\n");
		free(rgb);
		free_ellipsoid(&ellipsoid);
		return (NULL);
	}
	ellipsoid->color = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	free(rgb);
	ellipsoid->up = get_up(ellipsoid->direction);
	return (ellipsoid);
}

static t_ellipsoid	*init_ellipsoid_part3(t_ellipsoid *ellipsoid,
		char *str, int i)
{
	float		a;
	float		b;
	float		c;

	a = ft_atof(str + i);
	pass_to_next_element(str, &i);
	b = ft_atof(str + i);
	pass_to_next_element(str, &i);
	c = ft_atof(str + i);
	if (calcul_el_ratio(ellipsoid, a, b, c) == 1)
	{
		free_ellipsoid(&ellipsoid);
		return (NULL);
	}
	pass_to_next_element(str, &i);
	ellipsoid = init_ellipsoid_part4(ellipsoid, str, i);
	return (ellipsoid);
}

static t_ellipsoid	*init_ellipsoid_part2(t_ellipsoid *ellipsoid,
		char *str, int i)
{
	if (!ellipsoid->origin || ellipsoid->direction->x < -1.0
		|| ellipsoid->direction->x > 1.0 || ellipsoid->direction->y
		< -1.0 || ellipsoid->direction->y > 1.0 || ellipsoid->direction->z
		< -1.0 || ellipsoid->direction->z > 1.0 || !ellipsoid->origin)
	{
		ft_error("Error\nDirection values must be between -1 and 1\n");
		free_ellipsoid(&ellipsoid);
		return (NULL);
	}
	pass_to_next_element(str, &i);
	ellipsoid = init_ellipsoid_part3(ellipsoid, str, i);
	return (ellipsoid);
}

t_ellipsoid	*init_ellipsoid(char *str)
{
	t_ellipsoid	*ellipsoid;
	int			i;

	if (!str || check_ellipsoid(str) == 1)
		return (NULL);
	ellipsoid = malloc(sizeof(t_ellipsoid));
	if (!ellipsoid)
	{
		ft_error("Error\nMalloc error\n");
		return (NULL);
	}
	null_all_el(ellipsoid);
	i = 2;
	while (ft_isspace(str[i]))
		i++;
	ellipsoid->origin = init_vector(str + i);
	pass_to_next_element(str, &i);
	ellipsoid->direction = init_vector(str + i);
	*ellipsoid->direction = vector_norm(*ellipsoid->direction);
	ellipsoid = init_ellipsoid_part2(ellipsoid, str, i);
	return (ellipsoid);
}
