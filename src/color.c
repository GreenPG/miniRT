/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:10:29 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/16 13:42:14 by gpasquet         ###   ########.fr       */
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

static int	normalized_color(int color, t_vector normal, t_vector ray)
{
	double	ratio;
	double	ray_len;

	ray_len = sqrt(dot_product(ray, ray));
	ray.x /= ray_len;
	ray.y /= ray_len;
	ray.z /= ray_len;
	ratio = dot_product(normal, ray);
	return (get_rgba(fabs(ratio * get_r(color)), fabs(ratio * get_g(color)), fabs(ratio * get_b(color)), 255));
}

static t_normal get_sphere_normal(t_sphere *sphere, t_vector ray, double distance)
{
	t_normal normal;
	double		vector_len;

	normal.origin.x = distance * ray.x;
	normal.origin.y = distance * ray.y;
	normal.origin.z = distance * ray.z;
	normal.dir.x = normal.origin.x - sphere->origin->x;
	normal.dir.y = normal.origin.y - sphere->origin->y;
	normal.dir.z = normal.origin.z - sphere->origin->z;
	vector_len = sqrt(dot_product(normal.dir, normal.dir));
	normal.dir.x /= vector_len;
	normal.dir.y /= vector_len;
	normal.dir.z /= vector_len;
	return (normal);
}

static t_normal	get_plane_normal(t_plane *plane, t_vector ray, double distance)
{
	t_normal	normal;
	double		vector_len;

	(void)plane;
	normal.origin.x = distance * ray.x;
	normal.origin.y = distance * ray.y;
	normal.origin.z = distance * ray.z;
	normal.dir.x = -plane->direction->x;
	normal.dir.y = -plane->direction->y;
	normal.dir.z = -plane->direction->z;
	vector_len = sqrt(dot_product(normal.dir, normal.dir));
	normal.dir.x /= vector_len;
	normal.dir.y /= vector_len;
	normal.dir.z /= vector_len;
	return (normal);
}

static int	get_final_color(int color, int diffuse_color, t_scene *scene)
{
	int	r;
	int	g;
	int	b;

	r = get_r(color) * (scene->ambiant_l->light_ratio * get_r(scene->ambiant_l->colors) + get_r(diffuse_color)) / 255;
	if (r > 255)
		r = 255;
	g = get_g(color) * (scene->ambiant_l->light_ratio * get_g(scene->ambiant_l->colors) + get_r(diffuse_color)) / 255;
	if (g > 255)
		g = 255;
	b = get_b(color) * (scene->ambiant_l->light_ratio * get_b(scene->ambiant_l->colors) + get_r(diffuse_color)) / 255;
	if (b > 255)
		b = 255;
	return (get_rgba(r, g, b, 255));
}

int	get_obj_color(t_obj_list *nearest, t_vector ray, t_scene *scene, double distance)
{
	double		t;
	int			diffuse_color;
	int			color;
	t_normal	normal;

	if (nearest)
	{
		if (nearest->type == sphere)
		{
			normal = get_sphere_normal(nearest->sphere, ray, distance);
			color = normalized_color(nearest->sphere->color, normal.dir, ray);
		}
		if (nearest->type == plane)
		{
			normal = get_plane_normal(nearest->plane, ray, distance);
			color = normalized_color(nearest->plane->colors, normal.dir, ray);
		}
		if (nearest->type == cylinder)
			return (add_ambient(nearest->cylinder->color, scene->ambiant_l));
		diffuse_color = get_diffuse_ratio(scene, normal);
		color = get_final_color(color, diffuse_color, scene);
		nearest->hitted = 0;
		return (color);
	}
	t = sin((ray.z) + scene->camera->beta * (M_PI / 180)); //bon c style mais prend pas en compte la position orig
	if (t > 0)
		return(get_rgba((255 * (1 - t) + t * 156),	(255 * (1 - t) + t * 156), (255 * (1 - t) + t * 245), 255));
	t = -t;
	return(get_rgba((255 * (1 - t) + t * 231),	(255 * (1 - t) + t * 109), (255 * (1 - t) + t * 245), 255));
}
