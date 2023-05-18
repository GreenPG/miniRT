/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_calculations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:43:10 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/18 10:48:38 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vector	transform_ray(t_vector ray, t_cylinder *cylinder)
{
	double		alpha;
	double		beta;
	double		tmpx;
	double		tmpy;

	alpha = cylinder->alpha;
	beta = cylinder->beta;
	ray.x = -cylinder->origin->x;
	ray.y = -cylinder->origin->y;
	ray.z = -cylinder->origin->z;
	tmpx = ray.x;
	tmpy = ray.y;
	ray.x = ray.x * cos(cylinder->alpha) - ray.y * sin(cylinder->alpha)
		* cos(cylinder->beta) + ray.z * sin(cylinder->alpha)
		* sin(cylinder->beta);
	ray.y = tmpx * sin(cylinder->alpha) + ray.y * cos(cylinder->beta)
		* cos(cylinder->alpha) - ray.z * cos(cylinder->alpha)
		* sin (cylinder->beta);
	ray.z = tmpy * sin(cylinder->beta) + ray.z * cos(cylinder->beta);
	return (ray);
}

double	cylinder_hit(t_cylinder *cylinder, t_vector ray)
{
	double		a;
	double		b;
	double		c;
	double		*root;
	t_vector	rayo;
	double		tmpx;
	double		tmpy;

	tmpx = ray.x;
	tmpy = ray.y;
	ray.x = ray.x * cos(cylinder->alpha) - ray.y * sin(cylinder->alpha)
		* cos(cylinder->beta) + ray.z * sin(cylinder->alpha)
		* sin(cylinder->beta);
	ray.y = tmpx * sin(cylinder->alpha) + ray.y * cos(cylinder->beta)
		* cos(cylinder->alpha) - ray.z * cos(cylinder->alpha)
		* sin (cylinder->beta);
	ray.z = tmpy * sin(cylinder->beta) + ray.z * cos(cylinder->beta);
	rayo = transform_ray(ray, cylinder);
	a = ray.x * ray.x + ray.z * ray.z;
	b = 2 * (rayo.x * ray.x + rayo.z * ray.z);
	c = rayo.x * rayo.x + rayo.z * rayo.z - (cylinder->diameter / 2);
	root = cyl_quadratic(a, b, c);
	if (!root)
		return (INFINITY);
	if (root[0] > 0 && root[0] < root[1] && rayo.y + root[0] * ray.y
		> -cylinder->height / 2 && rayo.y + root[0] * ray.y
		< cylinder->height / 2)
		return (root[0]);
	else if (root[1] > 0 && rayo.y + root[1] * ray.y
		> -cylinder->height / 2 && rayo.y + root[1] * ray.y
		< cylinder->height / 2)
		return (root[1]);
	return (INFINITY);
}
