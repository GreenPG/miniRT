/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:18:50 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/21 15:05:35 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_normal	bump_triangle(t_triangle *triangle, t_vector vec,
	t_normal normal, mlx_texture_t *tex)
{
	int	x;
	int	y;

	vec.x -= triangle->a->x;
	vec.y -= triangle->a->y;
	vec.z -= triangle->a->z;
	vec = camera_to_object_space(vec, *triangle->normal, *triangle->up);
	vec.z = fmodf(vec.z, 1);
	if (vec.z < 0)
		vec.z += 1;
	vec.x = fmodf(vec.x, 1);
	if (vec.x < 0)
		vec.x += 1;
	x = vec.z * tex->width;
	y = vec.x * tex->height;
	normal.dir = normal_perturbation(normal.dir, x, y, tex);
	return (normal);
}

t_normal	bump_cylinder(t_cylinder *cylinder, t_vector vec,
	t_normal normal, mlx_texture_t *tex)
{	
	double	alpha;
	double	beta;
	int		x;
	int		y;

	vec.x -= cylinder->origin->x;
	vec.y -= cylinder->origin->y;
	vec.z -= cylinder->origin->z;
	vec = camera_to_object_space(vec, *cylinder->direction, *cylinder->up);
	alpha = atan2(vec.z, vec.x);
	beta = 0;
	x = (beta) / M_PI * tex->width;
	y = (alpha + M_PI) / (M_PI * 2.) * tex->height;
	normal.dir = normal_perturbation(normal.dir, x, y, tex);
	return (normal);
}

t_vector	normal_perturbation(t_vector normal_dir, int x, int y,
	mlx_texture_t *tex)
{
	double	slope_u;
	double	slope_v;
	double	ratio;
	int		index;

	index = (y * tex->width + x) * tex->bytes_per_pixel;
	slope_u = (double)tex->pixels[index] / 64.;
	slope_v = (double)tex->pixels[index] / 64.;
	index = (((y + 1) % tex->height) * tex->width + x) * tex->bytes_per_pixel;
	slope_u = (double)tex->pixels[index] / 64. - slope_u;
	index = (y * tex->width + (x + 1) % tex->width) * tex->bytes_per_pixel;
	slope_v = (double)tex->pixels[index] / 64. - slope_v;
	ratio = 1. / sqrt(slope_u * slope_u + slope_v * slope_v + 1);
	normal_dir.x += -slope_u * ratio;
	normal_dir.y += -slope_v * ratio;
	normal_dir.z += ratio - 1;
	return (normal_dir);
}
