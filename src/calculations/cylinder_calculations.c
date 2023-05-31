/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_calculations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:43:10 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/31 09:03:19 by gtouzali         ###   ########.fr       */
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

double min_cyl(double t_1, double t_2, double t_3, double t_4)
{
	double min;

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

void ft_swoop(double *a, double* b)
{
	double *swap;
	swap = a; 
	a = b;
	b = swap;
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
	c = rayo.x * rayo.x + rayo.z * rayo.z - (cylinder->diameter / 2) * (cylinder->diameter / 2);
	root = cyl_quadratic(a, b, c);
	if (!root)
		return (INFINITY);
	if (!(root[0] > 0 && rayo.y + root[0] * ray.y
		> -cylinder->height / 2 && rayo.y + root[0] * ray.y
		< cylinder->height / 2))
		root[0] = INFINITY;
	if (!(root[1] > 0 && rayo.y + root[1] * ray.y
		> -cylinder->height / 2 && rayo.y + root[1] * ray.y
		< cylinder->height / 2))
		root[1] = INFINITY;
	double t_3;
	double t_4;
	t_3 = INFINITY;
	t_4 = INFINITY;
	t_3 = (-cylinder->height / 2 - rayo.y) / ray.y;
	if ((rayo.x + t_3 * ray.x) * (rayo.x + t_3 * ray.x) + (rayo.z + t_3 * ray.z) * (rayo.z + t_3 * ray.z) > (cylinder->diameter / 2) * (cylinder->diameter / 2)) 
		t_3 = INFINITY;
	t_4 = (cylinder->height / 2 - rayo.y) / ray.y;
	if ((rayo.x + t_4 * ray.x) * (rayo.x + t_4 * ray.x) + (rayo.z + t_4 * ray.z) * (rayo.z + t_4 * ray.z) > (cylinder->diameter / 2) * (cylinder->diameter / 2)) 
		t_4 = INFINITY;
	return (min_cyl(root[0], root[1], t_3, t_4));
}
