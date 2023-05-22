/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calculations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:48:50 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/19 10:45:27 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static double	sphere_shadow(t_sphere *sphere, t_light *light, t_vector light_dir)
{
	t_vector	oc;
	double		a;
	double		b;
	double		c;
	double		d;

	oc.x = light->origin->x - sphere->origin->x;
	oc.y = light->origin->y - sphere->origin->y;
	oc.z = light->origin->z - sphere->origin->z;
	a = dot_product(light_dir, light_dir);
	b = dot_product(oc, light_dir);
	c = dot_product(oc, oc) - ((sphere->diameter / 2) * (sphere->diameter / 2));
	d = (b * b) - (a * c);
	if (d > 0)
		return (get_root(a, b, d));
	return (INFINITY);
}

static double	plane_shadow(t_plane *plane, t_vector light_dir)
{
	double	is_hitted;
	double	t;

	is_hitted = dot_product(*plane->direction, light_dir);
	if (is_hitted > 1e-6 || is_hitted < -1e-6)
	{
		t = dot_product(*plane->origin, *plane->direction);
		t = t / is_hitted;
		if (t >= 0)
			return (t);
	}
	return (INFINITY);
}

static int	light_intersect(t_scene *scene, t_vector light_dir)
{
	t_obj_list	*cursor;
	double		distance;
	double		obj_distance;
	double		nearest_distance;

	light_dir.x *= -1;
	light_dir.y *= -1;
	light_dir.z *= -1;
	cursor = scene->obj_list;
	distance = INFINITY;
	nearest_distance = INFINITY;
	obj_distance = -INFINITY;
	while (cursor)
	{
		if (cursor->type == sphere)
			distance = sphere_shadow(cursor->sphere, scene->light, light_dir);
		else if (cursor->type == plane)
			distance = plane_shadow(cursor->plane, light_dir);
		if (cursor->hitted == 1)
			obj_distance = distance;
		else
			nearest_distance = distance;
		if (nearest_distance < obj_distance)
			return (1);
		cursor = cursor->next;
	}
	return (0);
}

static t_vector	get_light_dir(t_light *light, t_normal normal)
{
	double		light_dir_len;
	t_vector	light_dir;

	light_dir.x = light->origin->x - normal.origin.x;
	light_dir.y = light->origin->y - normal.origin.y;
	light_dir.z = light->origin->z - normal.origin.z;
	light_dir_len = sqrt(dot_product(light_dir, light_dir));
	light_dir.x /= light_dir_len;
	light_dir.y /= light_dir_len;
	light_dir.z /= light_dir_len;
	return (light_dir);
}

int	get_diffuse_ratio(t_scene *scene, t_normal normal)
{
	double		diffuse_ratio;
	t_vector	light_dir;
	int			r;
	int			g;
	int			b;

	light_dir = get_light_dir(scene->light, normal);
	if (light_intersect(scene, light_dir) == 1)
		return (0);
	diffuse_ratio = dot_product(normal.dir, light_dir);
	diffuse_ratio = fmax(0.0, diffuse_ratio);
	diffuse_ratio *= scene->light->brightness;
	r = get_r(scene->light->colors) * diffuse_ratio;
	g = get_g(scene->light->colors) * diffuse_ratio;
	b = get_b(scene->light->colors) * diffuse_ratio;
	return (get_rgba(r, g, b, 255));
}
