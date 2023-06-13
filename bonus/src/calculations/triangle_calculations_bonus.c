/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_calculations_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:39:22 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/13 17:06:51 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

bool	is_in_front_of_edge_bf(t_vector a, t_vector b, t_vector intersect, t_vector normal)
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

bool	is_in_front_of_edge_ff(t_vector a, t_vector b, t_vector intersect, t_vector normal)
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
	if (dot_product(normal, cross_vector) > -1e-6)
		return (false);
	return (true);
}

static bool	is_inside_triangle(t_triangle *triangle, t_vector ray, double distance)
{
	t_vector	intersect;

	intersect.x = distance * ray.x;
	intersect.y = distance * ray.y;
	intersect.z = distance * ray.z;
	if (dot_product(*triangle->normal, ray) > 0)
	{
		if (is_in_front_of_edge_bf(*triangle->a, *triangle->b, intersect, *triangle->normal) == false
			|| is_in_front_of_edge_bf(*triangle->b, *triangle->c, intersect, *triangle->normal) == false
			|| is_in_front_of_edge_bf(*triangle->c, *triangle->a, intersect, *triangle->normal) == false)
			return (false);
	}
	else
	{
		if (is_in_front_of_edge_ff(*triangle->a, *triangle->b, intersect, *triangle->normal) == false
			|| is_in_front_of_edge_ff(*triangle->b, *triangle->c, intersect, *triangle->normal) == false
			|| is_in_front_of_edge_ff(*triangle->c, *triangle->a, intersect, *triangle->normal) == false)
			return (false);
	}
	return (true);
}

double	distance_to_plane(t_triangle *triangle, t_vector ray)
{
	double		normal_ray_dot_product;
	double		distance;

	normal_ray_dot_product = dot_product(*triangle->normal, ray);
	if (normal_ray_dot_product > 1e-6 || normal_ray_dot_product < -1e-6)
	{
		distance = dot_product(*triangle->a, *triangle->normal);
		distance /= normal_ray_dot_product;
		if (distance >= 0)
			return (distance);
		else
			return (INFINITY);
	}
	return (INFINITY);
}

double	triangle_hit(t_triangle *triangle, t_vector ray)
{
	double		distance;

	if (!triangle)
		return (INFINITY);
	distance = distance_to_plane(triangle, ray);
	if (distance == INFINITY)
		return (INFINITY);
	if (is_inside_triangle(triangle, ray, distance) == false)
		return (INFINITY);
	return (distance);
}
