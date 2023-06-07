/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_transforms_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:38:52 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/07 13:41:05 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_vector	revert_transform(t_vector vec, t_cylinder *cylinder)
{
	double		tmpx;
	double		tmpy;
	double		alpha;
	double		beta;
		alpha = atan2(cylinder->direction->x, cylinder->direction->y);
	beta = acos(-cylinder->direction->z);
	tmpx = vec.x;
	tmpy = vec.y;
	vec.x = vec.x * cos(-alpha) - vec.y
		* sin(-alpha) * cos(-beta) + vec.z
		* sin(-alpha) * sin(-beta);
	vec.y = tmpx * sin(-alpha) + vec.y
		* cos(-beta) * cos(-alpha) - vec.z
		* cos(-alpha) * sin (-beta);
	vec.z = tmpy * sin(-beta) + vec.z
		* cos(-beta);
	return (vec);
}

t_vector	transform_rayo(t_vector ray, t_cylinder *cylinder)
{
	double		tmpx;
	double		tmpy;
		double		alpha;
	double		beta;

	ray.x = -cylinder->origin->x;
	ray.y = -cylinder->origin->y;
	ray.z = -cylinder->origin->z;
	alpha = atan2(cylinder->direction->x, cylinder->direction->y);
	beta = acos(-cylinder->direction->z);
	tmpx = ray.x;
	tmpy = ray.y;
	ray.x = ray.x * cos(alpha) - ray.y * sin(alpha)
		* cos(beta) + ray.z * sin(alpha)
		* sin(beta);
	ray.y = tmpx * sin(alpha) + ray.y * cos(beta)
		* cos(alpha) - ray.z * cos(alpha)
		* sin (beta);
	ray.z = tmpy * sin(beta) + ray.z * cos(beta);
	return (ray);
}

t_vector	transform_ray(t_vector ray, t_cylinder *cylinder)
{
	double		tmpx;
	double		tmpy;
	double		alpha;
	double		beta;

	alpha = atan2(cylinder->direction->x, cylinder->direction->y);
	beta = acos(-cylinder->direction->z);
	tmpx = ray.x;
	tmpy = ray.y;
	ray.x = ray.x * cos(alpha) - ray.y * sin(alpha)
		* cos(beta) + ray.z * sin(alpha)
		* sin(beta);
	ray.y = tmpx * sin(alpha) + ray.y * cos(beta)
		* cos(alpha) - ray.z * cos(alpha)
		* sin (beta);
	ray.z = tmpy * sin(beta) + ray.z * cos(beta);
	return (ray);
}
