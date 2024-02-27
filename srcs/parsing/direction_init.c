/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction_init.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:12:28 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/26 11:34:06 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vector	*direction_default(void)
{
	t_vector	*direction;

	direction = malloc(sizeof(t_vector));
	if (!direction)
	{
		ft_error("Error\nMalloc error\n");
		return (NULL);
	}
	direction->x = 0;
	direction->y = 1;
	direction->z = 0;
	return (direction);
}

t_vector	*up_default(void)
{
	t_vector	*up;

	up = malloc(sizeof(t_vector));
	if (!up)
	{
		ft_error("Error\nMalloc error\n");
		return (NULL);
	}
	up->x = 0;
	up->y = 0;
	up->z = 1;
	return (up);
}

t_vector	*get_up(t_vector *direction)
{
	t_cyl_calc	data;
	t_vector	*up;

	up = malloc(sizeof(t_vector));
	if (!up)
	{
		ft_error("Error\nMalloc error\n");
		return (NULL);
	}
	up->x = 0;
	up->y = 0;
	up->z = 1;
	data.front.x = 0;
	data.front.y = 1;
	data.front.z = 0;
	data.cross = vector_cross(*direction, data.front);
	if (sqrt(dot_product(data.cross, data.cross)) < 1e-6)
		return (up);
	data.cross = vector_norm(data.cross);
	up->x = direction->x;
	up->y = direction->y;
	up->z = direction->z;
	rotate_around_axis(up, data.cross, -90 * (M_PI / 180));
	*up = vector_norm(*up);
	return (up);
}
