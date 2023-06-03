/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_transforms_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:38:52 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/02 15:00:09 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_vector	revert_transform(t_vector vec, t_cylinder *cylinder)
{
	double		tmpx;
	double		tmpy;

	tmpx = vec.x;
	tmpy = vec.y;
	vec.x = vec.x * cos(-cylinder->alpha) - vec.y
		* sin(-cylinder->alpha) * cos(-cylinder->beta) + vec.z
		* sin(-cylinder->alpha) * sin(-cylinder->beta);
	vec.y = tmpx * sin(-cylinder->alpha) + vec.y
		* cos(-cylinder->beta) * cos(-cylinder->alpha) - vec.z
		* cos(-cylinder->alpha) * sin (-cylinder->beta);
	vec.z = tmpy * sin(-cylinder->beta) + vec.z
		* cos(-cylinder->beta);
	return (vec);
}

t_vector	transform_rayo(t_vector ray, t_cylinder *cylinder)
{
	double		tmpx;
	double		tmpy;

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
	return (ray);
}
