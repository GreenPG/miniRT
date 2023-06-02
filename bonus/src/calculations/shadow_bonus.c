/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:24:35 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/02 10:20:23 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

double	sphere_shadow(t_sphere *sphere, t_normal normal,
			t_vector light_dir)
{
	t_vector	oc;
	double		a;
	double		b;
	double		c;
	double		d;

	oc.x = normal.origin.x - sphere->origin->x;
	oc.y = normal.origin.y - sphere->origin->y;
	oc.z = normal.origin.z - sphere->origin->z;
	a = dot_product(light_dir, light_dir);
	b = dot_product(oc, light_dir);
	c = dot_product(oc, oc) - ((sphere->diameter / 2) * (sphere->diameter / 2));
	d = (b * b) - (a * c);
	if (d > 0)
		return (get_root(a, b, d));
	return (INFINITY);
}

double	plane_shadow(t_plane *plane, t_vector light_dir,
		t_normal normal)
{
	double	is_hitted;
	double	t;

	is_hitted = dot_product(*plane->direction, light_dir);
	if (is_hitted > 1e-6 || is_hitted < -1e-6)
	{
		light_dir.x = plane->origin->x - normal.origin.x;
		light_dir.y = plane->origin->y - normal.origin.y;
		light_dir.z = plane->origin->z - normal.origin.z;
		t = dot_product(light_dir, *plane->direction);
		t = t / is_hitted;
		if (t != 0)
			return (t);
	}
	return (INFINITY);
}

static t_vector	transform_lighto(t_vector light_dir, t_vector light_origin,
		t_cylinder *cylinder)
{
	double		alpha;
	double		beta;
	double		tmpx;
	double		tmpy;

	alpha = cylinder->alpha;
	beta = cylinder->beta;
	light_dir.x = light_origin.x - cylinder->origin->x;
	light_dir.y = light_origin.y - cylinder->origin->y;
	light_dir.z = light_origin.z - cylinder->origin->z;
	tmpx = light_dir.x;
	tmpy = light_dir.y;
	light_dir.x = light_dir.x * cos(cylinder->alpha) - light_dir.y
		* sin(cylinder->alpha) * cos(cylinder->beta) + light_dir.z
		* sin(cylinder->alpha) * sin(cylinder->beta);
	light_dir.y = tmpx * sin(cylinder->alpha) + light_dir.y
		* cos(cylinder->beta) * cos(cylinder->alpha) - light_dir.z
		* cos(cylinder->alpha) * sin (cylinder->beta);
	light_dir.z = tmpy * sin(cylinder->beta) + light_dir.z
		* cos(cylinder->beta);
	return (light_dir);
}

double	cylinder_shadow(t_cylinder *cylinder, t_normal normal,
		t_vector light_dir)
{
	double		*root;
	double		*caps;
	double		distance;
	t_vector	light_o;

	light_dir = transform_ray(light_dir, cylinder);
	light_o = transform_lighto(light_dir, normal.origin, cylinder);
	root = body_hit(light_dir, light_o, cylinder);
	caps = caps_hit(light_dir, light_o, cylinder);
	if (!root || !caps)
	{
		free_cyl_roots(root, caps);
		return (INFINITY);
	}
	root = between_caps(root, light_o, light_dir, cylinder);
	if (min_cyl(root[0], root[1], caps[0], caps[1]) != INFINITY
		&& (min_cyl(root[0], root[1], caps[0], caps[1]) == root[0]
			|| min_cyl(root[0], root[1], caps[0], caps[1]) == root[1]))
		cylinder->hit_body = true;
	distance = min_cyl(root[0], root[1], caps[0], caps[1]);
	free_cyl_roots(root, caps);
	return (distance);
}

double	get_shadow_distance(t_obj_list *cursor, t_normal normal,
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
