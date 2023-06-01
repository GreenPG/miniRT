/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_calculations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:43:10 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/01 11:11:00 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vector	transform_rayo(t_vector ray, t_cylinder *cylinder)
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

t_vector	transform_ray(t_vector ray, t_cylinder *cylinder)
{
	double		alpha;
	double		beta;
	double		tmpx;
	double		tmpy;

	alpha = cylinder->alpha;
	beta = cylinder->beta;
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

double	min_cyl(double t_1, double t_2, double t_3, double t_4)
{
	double	min;

	min = INFINITY;
	if (t_1 > 0 && t_1 < min)
		min = t_1;
	if (t_2 > 0 && t_2 < min)
		min = t_2;
	if (t_3 > 0 && t_3 < min)
		min = t_3;
	if (t_4 > 0 && t_4 < min)
		min = t_4;
	return (min);
}

double	*caps_hit(t_vector ray, t_vector rayo, t_cylinder *cylinder)
{
	double	*r;

	r = malloc(sizeof(double) * 2);
	if (!r)
	{
		ft_error("Error\n");
		return (NULL);
	}
	r[0] = INFINITY;
	r[1] = INFINITY;
	r[0] = (-cylinder->height / 2 - rayo.y) / ray.y;
	if ((rayo.x + r[0] * ray.x) * (rayo.x + r[0] * ray.x)
		+ (rayo.z + r[0] * ray.z) * (rayo.z + r[0] * ray.z)
		> (cylinder->diameter / 2) * (cylinder->diameter / 2))
		r[0] = INFINITY;
	r[1] = (cylinder->height / 2 - rayo.y) / ray.y;
	if ((rayo.x + r[1] * ray.x) * (rayo.x + r[1] * ray.x)
		+ (rayo.z + r[1] * ray.z) * (rayo.z + r[1] * ray.z)
		> (cylinder->diameter / 2) * (cylinder->diameter / 2))
		r[1] = INFINITY;
	return (r);
}

double	*body_hit(t_vector ray, t_vector rayo,
		t_cylinder *cylinder)
{
	double	a;
	double	b;
	double	c;

	a = ray.x * ray.x + ray.z * ray.z;
	b = 2 * (rayo.x * ray.x + rayo.z * ray.z);
	c = rayo.x * rayo.x + rayo.z * rayo.z
		- (cylinder->diameter / 2) * (cylinder->diameter / 2);
	return (cyl_quadratic(a, b, c));
}

double	cylinder_hit(t_cylinder *cylinder, t_vector ray)
{
	double		*root;
	double		*caps;
	t_vector	rayo;

	ray = transform_ray(ray, cylinder);
	rayo = transform_rayo(ray, cylinder);
	root = body_hit(ray, rayo, cylinder);
	caps = caps_hit(ray, rayo, cylinder);
	if (!root || !caps)
		return (INFINITY);
	if (!(root[0] > 0 && rayo.y + root[0] * ray.y
			> -cylinder->height / 2 && rayo.y + root[0] * ray.y
			< cylinder->height / 2))
		root[0] = INFINITY;
	if (!(root[1] > 0 && rayo.y + root[1] * ray.y
			> -cylinder->height / 2 && rayo.y + root[1] * ray.y
			< cylinder->height / 2))
		root[1] = INFINITY;
	if (min_cyl(root[0], root[1], caps[0], caps[1]) != INFINITY
		&& (min_cyl(root[0], root[1], caps[0], caps[1]) == root[0]
			|| min_cyl(root[0], root[1], caps[0], caps[1]) == root[1]))
		cylinder->hit_body = true;
	return (min_cyl(root[0], root[1], caps[0], caps[1]));
}
