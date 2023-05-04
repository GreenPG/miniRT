/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:10:29 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/04 15:38:45 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_r(int rgba)
{
	return ((rgba >> 24) & 0xFF);
}

int	get_g(int rgba)
{
	return ((rgba >> 16) & 0xFF);
}

int	get_b(int rgba)
{
	return ((rgba >> 8) & 0xFF);
}

int	get_a(int rgba)
{
	return (rgba & 0xFF);
}
int	add_ambient(int color, t_ambiant_l *ambiant)
{
	int	r;
	int	g;
	int	b;

	r = (get_r(color) * get_r(ambiant->colors) / 255) * ambiant->light_ratio;
	g = (get_g(color) * get_g(ambiant->colors) / 255) * ambiant->light_ratio;
	b = (get_b(color) * get_b(ambiant->colors) / 255) * ambiant->light_ratio;
	return (get_rgba(r, g, b, 255));
}

int	get_obj_color(t_obj_list *nearest, t_vector ray, t_ambiant_l *ambiant)
{
	double t;
	if (nearest)
	{
		if (nearest->type == sphere)
			return (add_ambient(nearest->sphere->color, ambiant));
		if (nearest->type == plane)
			return (add_ambient(nearest->plane->colors, ambiant));
		if (nearest->type == cylinder)
			return (add_ambient(nearest->cylinder->color, ambiant));
	}
	t = (ray.z_d); //bon c style mais prend pas en compte la position orig
	if (t > 0)
		return(get_rgba((255 * (1 - t) + t * 160),	(255 * (1 - t) + t * 150), (255 * (1 - t) + t * 240), 255));
	t = -t;
	return(get_rgba((255 * (1 - t) + t * 229),	(255 * (1 - t) + t * 190), (255 * (1 - t) + t * 236), 255));
}
