/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid_calculations_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:43:10 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/20 10:17:53 by gtouzali         ###   ########.fr       */
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

double	ellipsoid_hit(t_ellipsoid *ellipsoid, t_vector ray)
{
	double		*root;
	double		distance;
	t_vector	rayo;

	rayo.x = -ellipsoid->origin->x;
	rayo.y = -ellipsoid->origin->y;
	rayo.z = -ellipsoid->origin->z;
	ray = camera_to_object_space(ray, *ellipsoid->direction, *ellipsoid->up);
	rayo = camera_to_object_space(rayo, *ellipsoid->direction, *ellipsoid->up);
	root = hell_hit(ray, rayo, ellipsoid);
	if (!root)
	{
		free_hell_roots(root);
		return (INFINITY);
	}
	distance = hell_min_root(root);
	free_hell_roots(root);
	return (distance);
}

double	ellipsoid_shadow(t_ellipsoid *ellipsoid, t_normal normal,
		t_vector ray)
{
	double		*root;
	double		distance;
	t_vector	rayo;

	rayo.x = normal.origin.x - ellipsoid->origin->x;
	rayo.y = normal.origin.y - ellipsoid->origin->y;
	rayo.z = normal.origin.z - ellipsoid->origin->z;
	ray = camera_to_object_space(ray, *ellipsoid->direction, *ellipsoid->up);
	rayo = camera_to_object_space(rayo, *ellipsoid->direction, *ellipsoid->up);
	root = hell_hit(ray, rayo, ellipsoid);
	if (!root)
	{
		free_hell_roots(root);
		return (INFINITY);
	}
	distance = hell_min_root(root);
	free_hell_roots(root);
	return (distance);
}
