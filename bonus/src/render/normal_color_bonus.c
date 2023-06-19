/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_color_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:31:43 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/19 10:43:09 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

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

	if (nearest->pattern == checkerboard)
	{
		color = get_checkerboard(nearest, normal);
		return (normalized_color(color, normal.dir, ray));
	}
	if (nearest->pattern == texture)
	{
		color = get_texture(nearest, normal);
		return (normalized_color(color, normal.dir, ray));
	}
	(void)camera;
	if (nearest->type == sphere)
		color = normalized_color(nearest->sphere->color, normal.dir, ray);
	if (nearest->type == plane)
		color = normalized_color(nearest->plane->colors, normal.dir, ray);
	if (nearest->type == cylinder)
		color = normalized_color(nearest->cylinder->color, normal.dir, ray);
	if (nearest->type == ellipsoid)
		color = normalized_color(nearest->ellipsoid->color, normal.dir, ray);
	if (nearest->type == triangle)
		color = normalized_color(nearest->triangle->color, normal.dir, ray);
	return (color);
}
