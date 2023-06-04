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

#include <minirt_bonus.h>

double	*hell_hit(t_vector ray, t_vector rayo, t_ellipsoid *hell)
{
	double	a;
	double	b;
	double	c;

	a = (ray.x * ray.x) * hell->a + (ray.y * ray.y) * hell->b + (ray.z * ray.z) * hell->c;
	b = ((ray.x * rayo.x) * hell->a + (ray.y * rayo.y) * hell->b + (ray.z * rayo.z) * hell->c);
	c = (rayo.x * rayo.x) * hell->a + (rayo.y * rayo.y) * hell->b + (rayo.z * rayo.z) * hell->c - 1;
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

t_vector	etransform_rayo(t_vector ray, t_ellipsoid *ellipsoid)
{
	double		alpha;
	double		beta;
	double		tmpx;
	double		tmpy;

	alpha = ellipsoid->alpha;
	beta = ellipsoid->beta;
	ray.x = -ellipsoid->origin->x;
	ray.y = -ellipsoid->origin->y;
	ray.z = -ellipsoid->origin->z;
	tmpx = ray.x;
	tmpy = ray.y;
	ray.x = ray.x * cos(ellipsoid->alpha) - ray.y * sin(ellipsoid->alpha)
		* cos(ellipsoid->beta) + ray.z * sin(ellipsoid->alpha)
		* sin(ellipsoid->beta);
	ray.y = tmpx * sin(ellipsoid->alpha) + ray.y * cos(ellipsoid->beta)
		* cos(ellipsoid->alpha) - ray.z * cos(ellipsoid->alpha)
		* sin (ellipsoid->beta);
	ray.z = tmpy * sin(ellipsoid->beta) + ray.z * cos(ellipsoid->beta);
	return (ray);
}

t_vector	etransform_ray(t_vector ray, t_ellipsoid *ellipsoid)
{
	double		alpha;
	double		beta;
	double		tmpx;
	double		tmpy;

	alpha = ellipsoid->alpha;
	beta = ellipsoid->beta;
	tmpx = ray.x;
	tmpy = ray.y;
	ray.x = ray.x * cos(ellipsoid->alpha) - ray.y * sin(ellipsoid->alpha)
		* cos(ellipsoid->beta) + ray.z * sin(ellipsoid->alpha)
		* sin(ellipsoid->beta);
	ray.y = tmpx * sin(ellipsoid->alpha) + ray.y * cos(ellipsoid->beta)
		* cos(ellipsoid->alpha) - ray.z * cos(ellipsoid->alpha)
		* sin (ellipsoid->beta);
	ray.z = tmpy * sin(ellipsoid->beta) + ray.z * cos(ellipsoid->beta);
	return (ray);
}

double	ellipsoid_hit(t_ellipsoid *hell, t_vector ray)
{
	double		*root;
	double		distance;
	t_vector	rayo;

	ray = etransform_ray(ray, hell);
	rayo = etransform_rayo(ray, hell);
	root = hell_hit(ray, rayo, hell);
	if (!root)
	{
		free_hell_roots(root);
		return (INFINITY);
	}
	distance = hell_min_root(root);
	free_hell_roots(root);
	return (distance);
}

static t_vector	etransform_lighto(t_vector light_dir, t_vector light_origin,
		t_ellipsoid *ellipsoid)
{
	double		alpha;
	double		beta;
	double		tmpx;
	double		tmpy;

	alpha = ellipsoid->alpha;
	beta = ellipsoid->beta;
	light_dir.x = light_origin.x - ellipsoid->origin->x;
	light_dir.y = light_origin.y - ellipsoid->origin->y;
	light_dir.z = light_origin.z - ellipsoid->origin->z;
	tmpx = light_dir.x;
	tmpy = light_dir.y;
	light_dir.x = light_dir.x * cos(ellipsoid->alpha) - light_dir.y
		* sin(ellipsoid->alpha) * cos(ellipsoid->beta) + light_dir.z
		* sin(ellipsoid->alpha) * sin(ellipsoid->beta);
	light_dir.y = tmpx * sin(ellipsoid->alpha) + light_dir.y
		* cos(ellipsoid->beta) * cos(ellipsoid->alpha) - light_dir.z
		* cos(ellipsoid->alpha) * sin (ellipsoid->beta);
	light_dir.z = tmpy * sin(ellipsoid->beta) + light_dir.z
		* cos(ellipsoid->beta);
	return (light_dir);
}

double	ellipsoid_shadow(t_ellipsoid *ellipsoid, t_normal normal,
		t_vector light_dir)
{
	double		*root;
	double		distance;
	t_vector	light_o;

	light_dir = etransform_ray(light_dir, ellipsoid);
	light_o = etransform_lighto(light_dir, normal.origin, ellipsoid);
	root = hell_hit(light_dir, light_o, ellipsoid);
	if (!root)
	{
		free_hell_roots(root);
		return (INFINITY);
	}
	distance = hell_min_root(root);
	free_hell_roots(root);
	return (distance);
}
