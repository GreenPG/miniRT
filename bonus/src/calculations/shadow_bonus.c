/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:24:35 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/13 16:57:55 by gpasquet         ###   ########.fr       */
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

static double	cylinder_distance_shad(t_cylinder *cylinder, t_vector ray,
		t_cyl_calc	data)
{
	double		*root;
	double		*caps;
	double		distance;

	root = body_hit(ray, data.rayo, cylinder);
	caps = caps_hit(ray, data.rayo, cylinder);
	if (!root || !caps)
	{
		free_cyl_roots(root, caps);
		return (INFINITY);
	}
	root = between_caps(root, data.rayo, ray, cylinder);
	if (min_cyl(root[0], root[1], caps[0], caps[1]) != INFINITY
			&& (min_cyl(root[0], root[1], caps[0], caps[1]) == root[0]
				|| min_cyl(root[0], root[1], caps[0], caps[1]) == root[1]))
		cylinder->hit_body = true;
	distance = min_cyl(root[0], root[1], caps[0], caps[1]);
	free_cyl_roots(root, caps);
	return (distance);
}

double	cylinder_shadow(t_cylinder *cylinder, t_normal normal,
		t_vector light_dir)
{
	t_cyl_calc	data;

	data.front.x = 0;
	data.front.y = 1;
	data.front.z = 0;
	data.cross = vector_cross(*cylinder->direction, data.front);
	vector_norm(&data.cross);
	data.angle = acos(dot_product(*cylinder->direction, data.front)
			/ (sqrt(dot_product(*cylinder->direction, *cylinder->direction))
				* sqrt(dot_product (data.front, data.front))));
	rotate_around_axis(&light_dir, data.cross, -data.angle);
	data.rayo.x = normal.origin.x - cylinder->origin->x;
	data.rayo.y = normal.origin.y - cylinder->origin->y;
	data.rayo.z = normal.origin.z - cylinder->origin->z;
	rotate_around_axis(&data.rayo, data.cross, -data.angle);
	return (cylinder_distance_shad(cylinder, light_dir, data));
}

static bool is_inside_triangle_shadow(t_triangle *triangle, t_vector light_dir, double distance, t_vector origin)
{
	t_vector	intersect;

	intersect.x = origin.x + distance * light_dir.x;
	intersect.y = origin.y + distance * light_dir.y;
	intersect.z = origin.z + distance * light_dir.z;
	if (dot_product(*triangle->normal, light_dir) > 0)
	{
		if (is_in_front_of_edge_ff(*triangle->a, *triangle->b, intersect, *triangle->normal) == false
				|| is_in_front_of_edge_ff(*triangle->b, *triangle->c, intersect, *triangle->normal) == false
				|| is_in_front_of_edge_ff(*triangle->c, *triangle->a, intersect, *triangle->normal) == false)
			return (false);
	}
	else
	{
		if (is_in_front_of_edge_bf(*triangle->a, *triangle->b, intersect, *triangle->normal) == false
				|| is_in_front_of_edge_bf(*triangle->b, *triangle->c, intersect, *triangle->normal) == false
				|| is_in_front_of_edge_bf(*triangle->c, *triangle->a, intersect, *triangle->normal) == false)
			return (false);
	}
	return (true);
}

double triangle_shadow(t_triangle *triangle, t_normal normal, t_vector light_dir)
{
	double		distance;

	if (dot_product(light_dir, *triangle->normal) > 0)
		*triangle->normal = invert_vector(*triangle->normal);
	distance = distance_to_plane(triangle, light_dir);
	if (distance == INFINITY)
		return (distance);
	if (is_inside_triangle_shadow(triangle, light_dir, distance, normal.origin))
		return (INFINITY);
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
	if (cursor->type == ellipsoid)
		distance = ellipsoid_shadow(cursor->ellipsoid, normal, light_dir);
	if (cursor->type == triangle)
		distance = triangle_shadow(cursor->triangle, normal, light_dir);
	return (distance);
}
