/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_calculations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:57:34 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/01 14:26:10 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

double	get_root(double a, double b, double d)
{
	double	r0;
	double	r1;

	r0 = (-b - sqrt(d)) / (a);
	r1 = (-b + sqrt(d)) / (a);
	if (r0 > r1 && r1 >= 0)
		return (r1);
	else if (r1 >= r0 && r0 >= 0)
		return (r0);
	else if (r0 > 0)
		return (r0);
	else if (r1 > 0)
		return (r1);
	else
		return (INFINITY);
}

t_normal	get_sphere_normal(t_sphere *sphere, t_vector ray,
		double distance)
{
	t_normal	normal;
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

double	sphere_hit(t_sphere *sphere, t_vector ray)
{
	t_vector	oc;
	double		a;
	double		b;
	double		c;
	double		d;

	oc.x = -sphere->origin->x;
	oc.y = -sphere->origin->y;
	oc.z = -sphere->origin->z;
	a = dot_product(ray, ray);
	b = dot_product(oc, ray);
	c = dot_product(oc, oc) - ((sphere->diameter / 2) * (sphere->diameter / 2));
	d = (b * b) - (a * c);
	if (d > 0)
		return (get_root(a, b, d));
	return (INFINITY);
}
