/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid_calculations_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:43:10 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/19 11:34:59 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

double	*hell_hit(t_vector ray, t_vector rayo, t_ellipsoid *hell)
{
	double	a;
	double	b;
	double	c;

	a = (ray.x * ray.x) * hell->a + (ray.y * ray.y) * hell->b
		+ (ray.z * ray.z) * hell->c;
	b = ((ray.x * rayo.x) * hell->a + (ray.y * rayo.y) * hell->b
			+ (ray.z * rayo.z) * hell->c);
	c = (rayo.x * rayo.x) * hell->a + (rayo.y * rayo.y) * hell->b
		+ (rayo.z * rayo.z) * hell->c - 1;
	return (cyl_quadratic(a, b, c));
}

void	free_hell_roots(double *root)
{
	if (root)
		free(root);
}

double	hell_min_root(double *root)
{
	if (root[0] > 0 && root[0] < root[1])
		return (root[0]);
	else if (root[1] > 0)
		return (root[1]);
	return (INFINITY);
}

double	ellipsoid_distance(t_ellipsoid *ellipsoid, t_cyl_calc data,
		t_vector ray)
{
	t_vector	tmp;
	double		*root;
	double		distance;

	tmp.x = ellipsoid->up->x;
	tmp.y = ellipsoid->up->y;
	tmp.z = ellipsoid->up->z;
	get_angle(data, ellipsoid, 0);
	rotate_around_axis(&ray, data.cross, -data.angle);
	rotate_around_axis(&data.rayo, data.cross, -data.angle);
	rotate_around_axis(&tmp, data.cross, -data.angle);
	data.front.x = 0.0000001;
	data.front.y = 0.0000001;
	data.front.z = 1;
	if (dot_product(tmp, data.front) > -1 + 1e-6)
	{
		get_angle(data, ellipsoid, 1);
		rotate_around_axis(&ray, data.cross, data.angle);
		rotate_around_axis(&data.rayo, data.cross, data.angle);
	}
	root = hell_hit(ray, data.rayo, ellipsoid);
	if (!root)
	{
		free_hell_roots(root);
		return (INFINITY);
	}
	distance = hell_min_root(root);
	free_hell_roots(root);
	return (distance);
}

double	ellipsoid_hit(t_ellipsoid *ellipsoid, t_vector ray)
{
	double		distance;
	t_cyl_calc	data;

	data.rayo.x = -ellipsoid->origin->x;
	data.rayo.y = -ellipsoid->origin->y;
	data.rayo.z = -ellipsoid->origin->z;
	distance = ellipsoid_distance(ellipsoid, data, ray);
	return (distance);
}
