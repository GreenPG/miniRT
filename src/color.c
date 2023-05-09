/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:10:29 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/09 17:19:14 by gpasquet         ###   ########.fr       */
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

static int	normalized_sphere_color(t_sphere *sphere, t_vector normal)
{
	return (get_rgba(fabs(normal.x_d * get_r(sphere->color)), fabs(normal.y_d * get_g(sphere->color)), fabs(normal.z_d * get_b(sphere->color)), 255));
}

static t_vector	get_sphere_normal(t_sphere *sphere, t_vector ray, double distance)
{
	t_vector	normal;
	double		vector_len;

	distance += 0.001;
	normal.x_o = distance * ray.x_d;
	normal.y_o = distance * ray.y_d;
	normal.z_o = distance * ray.z_d;
	normal.x_d = normal.x_o - sphere->pos->x;
	normal.y_d = normal.y_o - sphere->pos->y;
	normal.z_d = normal.z_o - sphere->pos->z;
	vector_len = sqrt(pow(normal.x_d, 2) + pow(normal.y_d, 2) + pow(normal.z_d, 2));
	normal.x_d /= vector_len;
	normal.y_d /= vector_len;
	normal.z_d /= vector_len;
	if (dot_product(ray, normal) > 0.0)
	{
		normal.x_d *= -1;
		normal.y_d *= -1;
		normal.z_d *= -1;
	}
	return (normal);
}

int	get_obj_color(t_obj_list *nearest, t_vector ray, t_scene *scene, double distance)
{
	double		t;
	int			color;
	t_vector	normal;

	if (nearest)
	{
		if (nearest->type == sphere)
		{
			normal = get_sphere_normal(nearest->sphere, ray, distance);
			color = normalized_sphere_color(nearest->sphere, normal);
//			color = add_ambient(color, scene->ambiant_l);
			return (color);
		}
		if (nearest->type == plane)
			return (add_ambient(nearest->plane->colors, scene->ambiant_l));
		if (nearest->type == cylinder)
			return (add_ambient(nearest->cylinder->color, scene->ambiant_l));
	}
	t = (ray.z_d); //bon c style mais prend pas en compte la position orig
	if (t > 0)
		return(get_rgba((255 * (1 - t) + t * 160),	(255 * (1 - t) + t * 150), (255 * (1 - t) + t * 240), 255));
	t = -t;
	return(get_rgba((255 * (1 - t) + t * 229),	(255 * (1 - t) + t * 190), (255 * (1 - t) + t * 236), 255));
}
