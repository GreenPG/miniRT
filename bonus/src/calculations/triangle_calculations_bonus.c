/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_calculations_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:39:22 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/12 17:04:14 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static bool	is_in_front_of_edge(t_vector a, t_vector b, t_vector intersect, t_vector normal)
{
	t_vector	edge;
	t_vector	vertice_to_intersect;
	t_vector	cross_vector;

	edge.x = b.x - a.x;
	edge.y = b.y - a.y;
	edge.z = b.z - a.z;
	vertice_to_intersect.x = intersect.x - a.x;
	vertice_to_intersect.y = intersect.y - a.y;
	vertice_to_intersect.z = intersect.z - a.z;
	cross_vector = vector_cross(edge, vertice_to_intersect);
	if (dot_product(normal, cross_vector) < -1e-6)
		return (false);
	return (true);
}

static bool	is_inside_triangle(t_triangle *triangle, t_vector ray, double distance)
{
	t_vector	intersect;

	intersect.x = distance * ray.x;
	intersect.y = distance * ray.y;
	intersect.z = distance * ray.z;
	if (is_in_front_of_edge(*triangle->a, *triangle->b, intersect, *triangle->normal) == false 
		|| is_in_front_of_edge(*triangle->a, *triangle->c, intersect, *triangle->normal) == false)
		return (false);
	return (true);
}

static double	distance_to_plane(t_triangle *triangle, t_vector ray)
{
	double		normal_ray_dot_product;
	double		distance;
	double		origin_to_plane;
	t_vector	origin;

	origin.x = 0;
	origin.y = 0;
	origin.z = 0;
	normal_ray_dot_product = fabs(dot_product(*triangle->normal, ray));
	if (normal_ray_dot_product < 1e-6 && normal_ray_dot_product > -1e-6)
		return (INFINITY);
	origin_to_plane = -dot_product(*triangle->normal, *triangle->a);
	distance = -(dot_product(origin, *triangle->normal) + origin_to_plane) / normal_ray_dot_product;
	if (distance < 1e-6)
		return (INFINITY);
	return (distance);
}

double	triangle_hit(t_triangle *triangle, t_vector ray)
{
	double	distance;

	if (!triangle)
		return (INFINITY);
	distance = distance_to_plane(triangle, ray);
	if (distance == INFINITY)
		return (INFINITY);
	if (is_inside_triangle(triangle, ray, distance) == false)
		return (INFINITY);
	return (distance);
}
