/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:32:35 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/14 15:14:28 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_coords	*init_coords(float x, float y, float z)
{
	t_coords	*coords;

	coords = malloc(sizeof(t_coords));
	if (!coords)
	{
		ft_error("Error: fatal\n");
		return (NULL);
	}
	coords->x = x;
	coords->y = y;
	coords->z = z;
	return (coords);
}

t_vector	*init_vector(float x, float y, float z)
{
	t_vector	*vector;

	if (x < -1.0 || x > 1.0 || y < -1.0 || y > 1.0 || z < -1.0 || z > 1.0)
	{
		ft_error("Vector components should be within the range of \
				-1.0 to 1.0\n");
		return (NULL);
	}
	vector = malloc(sizeof(t_vector));
	if (!vector)
	{
		ft_error("Error: fatal\n");
		return (NULL);
	}
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (vector);
}

t_color	*init_color(int r, int g, int b)
{
	t_color	*color;

	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_error("Color values must within the range of 0 and 255\n");
		return (NULL);
	}
	color = malloc(sizeof(t_color));
	if (!color)
	{
		ft_error("Error: fatal\n");
		return (NULL);
	}
	color->r = r;
	color->g = g;
	color->b = b;
	return (color);
}
