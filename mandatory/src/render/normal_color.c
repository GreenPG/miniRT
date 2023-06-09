/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:31:43 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/01 14:33:22 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static int	normalized_color(int color, t_vector normal, t_vector ray)
{
	double	ratio;
	double	ray_len;

	ray_len = sqrt(dot_product(ray, ray));
	ray.x /= ray_len;
	ray.y /= ray_len;
	ray.z /= ray_len;
	ratio = dot_product(normal, ray);
	return (get_rgba(fabs(ratio * get_r(color)), fabs(ratio * get_g(color)),
			fabs(ratio * get_b(color)), 255));
}

int	get_normal_color(t_obj_list *nearest, t_vector ray, t_normal normal)
{
	int			color;

	if (nearest->type == sphere)
		color = normalized_color(nearest->sphere->color, normal.dir, ray);
	if (nearest->type == plane)
		color = normalized_color(nearest->plane->colors, normal.dir, ray);
	if (nearest->type == cylinder)
		color = normalized_color(nearest->cylinder->color, normal.dir, ray);
	return (color);
}
