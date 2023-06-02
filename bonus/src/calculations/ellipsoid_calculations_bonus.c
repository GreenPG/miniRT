/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hell_calculations_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:43:10 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/02 14:09:30 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

double	*hell_hit(t_vector ray, t_vector rayo,
		t_hell *hell)
{
	double	a;
	double	b;
	double	c;

	a = (ray.x * ray.x) * hell->a + (ray.z * ray.y) * hell->b + (ray.z * ray.y) * hell->c;
	b = 2 * (ray.x * rayo.x) * hell->a + (ray.z * rayo.y) * hell->b + (ray.z * rayo.y) * hell->c;
	c = (rayo.x * rayo.x) * hell->a + (rayo.z * rayo.y) * hell->b + (rayo.z * rayo.y) * hell->c;
		- (hell->diameter * 2) * (hell->diameter * 2);
	return (cyl_quadratic(a, b, c));
}

void	free_hell_roots(double *root)
{
	if (root)
		free(root);
}

double hell_min_root(double *root)
{
	if (root[0] > 0 && root[0] < root[1])
		return (root[0]);
	else if (root[1] > 0)
		return (root[1]);
	return (INFINITY);
}

double	ellipsoid_hit(t_hell *hell, t_vector ray)
{
	double		*root;
	double		*caps;
	double		distance;
	t_vector	rayo;

	ray = transform_ray(ray, hell);
	rayo = transform_rayo(ray, hell);
	root = hell_hit(ray, rayo, hell);
	if (!root)
	{
		free_hell_roots(root);
		return (INFINITY);
	}
	distance = hell_min_root(root);
	free_hell_roots(root, caps);
	return (distance);
}
