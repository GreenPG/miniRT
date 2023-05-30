/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:24:35 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/30 09:25:00 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

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
