/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_shadow_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:01:55 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/16 11:03:57 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static bool	is_inside_triangle_shadow(t_triangle *triangle, t_vector light_dir,
		double distance, t_vector origin)
{
	t_vector	intersect;

	intersect.x = origin.x + distance * light_dir.x;
	intersect.y = origin.y + distance * light_dir.y;
	intersect.z = origin.z + distance * light_dir.z;
	if (is_in_front_of_edge_ff(*triangle->a, *triangle->b, intersect,
			*triangle->normal) == false && is_in_front_of_edge_ff(*triangle->b,
			*triangle->c, intersect, *triangle->normal) == false
		&& is_in_front_of_edge_ff(*triangle->c, *triangle->a,
			intersect, *triangle->normal) == false)
		return (true);
	if (is_in_front_of_edge_ff(*triangle->a, *triangle->b, intersect,
			*triangle->normal) == true && is_in_front_of_edge_ff(*triangle->b,
			*triangle->c, intersect, *triangle->normal) == true
		&& is_in_front_of_edge_ff(*triangle->c, *triangle->a, intersect,
			*triangle->normal) == true)
		return (true);
	return (false);
}

static double	distance_to_plane_shadow(t_triangle *triangle,
		t_vector light_dir, t_normal normal)
{
	double		normal_ray_dot_product;
	double		distance;
	t_vector	int_to_tr;

	normal_ray_dot_product = dot_product(*triangle->normal, light_dir);
	if (normal_ray_dot_product > 1e-6 || normal_ray_dot_product < -1e-6)
	{
		int_to_tr.x = triangle->a->x - normal.origin.x;
		int_to_tr.y = triangle->a->y - normal.origin.y;
		int_to_tr.z = triangle->a->z - normal.origin.z;
		distance = dot_product(int_to_tr, *triangle->normal);
		distance /= normal_ray_dot_product;
		if (distance >= 0)
			return (distance);
		else
			return (INFINITY);
	}
	return (INFINITY);
}

double	triangle_shadow(t_triangle *triangle, t_normal normal,
		t_vector light_dir)
{
	double		distance;

	distance = distance_to_plane_shadow(triangle, light_dir, normal);
	if (distance == INFINITY)
		return (distance);
	if (is_inside_triangle_shadow(triangle, light_dir, distance,
			normal.origin) == false)
		return (INFINITY);
	return (distance);
}
