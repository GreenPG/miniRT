/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calculations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:48:50 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/01 10:46:53 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static double	get_light_distance(t_light *light, t_normal normal)
{
	double		light_distance;
	t_vector	hit_to_light;

	hit_to_light.x = light->origin->x - normal.origin.x;
	hit_to_light.y = light->origin->y - normal.origin.y;
	hit_to_light.z = light->origin->z - normal.origin.z;
	light_distance = sqrt(dot_product(hit_to_light, hit_to_light));
	return (light_distance);
}

static int	wich_side(t_vector ray, t_vector light_dir,	t_normal normal)
{
	double	a;
	double	b;

	light_dir.x *= -1;
	light_dir.y *= -1;
	light_dir.z *= -1;
	a = dot_product(normal.dir, ray);
	b = dot_product(normal.dir, light_dir);
	if ((a < 0 && b < 0) || (a > 0 && b > 0))
		return (1);
	return (0);
}

static double	get_shadow_distance(t_obj_list *cursor, t_normal normal,
		t_vector light_dir)
{
	double	distance;

	if (cursor->type == sphere)
		distance = sphere_shadow(cursor->sphere, normal, light_dir);
	if (cursor->type == plane)
		distance = plane_shadow(cursor->plane, light_dir, normal);
	if (cursor->type == cylinder)
		distance = cylinder_shadow(cursor->cylinder, normal, light_dir);
	return (distance);
}

static int	light_intersect(t_scene *scene, t_vector light_dir, t_normal normal,
		t_vector ray)
{
	t_obj_list	*cursor;
	double		distance;
	double		light_source_d;

	light_source_d = get_light_distance(scene->light, normal);
	cursor = scene->obj_list;
	distance = 0;
	while (cursor)
	{
		if (cursor->hitted == 0)
			distance = get_shadow_distance(cursor, normal, light_dir);
		if (cursor->hitted == 1)
			if (wich_side(ray, light_dir, normal) == 0)
				return (1);
		if (distance > 0 && distance < light_source_d)
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

int	get_diffuse_ratio(t_scene *scene, t_normal normal, t_vector ray)
{
	double		diffuse_ratio;
	t_vector	light_dir;
	int			r;
	int			g;
	int			b;

	light_dir = get_light_dir(scene->light, normal);
	if (light_intersect(scene, light_dir, normal, ray) == 1)
		return (0);
	diffuse_ratio = fabs(dot_product(normal.dir, light_dir));
	diffuse_ratio = fmax(0.0, diffuse_ratio);
	diffuse_ratio *= scene->light->brightness;
	r = get_r(scene->light->colors) * diffuse_ratio;
	g = get_g(scene->light->colors) * diffuse_ratio;
	b = get_b(scene->light->colors) * diffuse_ratio;
	return (get_rgba(r, g, b, 255));
}
