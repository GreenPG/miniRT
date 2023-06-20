/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:12:36 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/20 16:16:04 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

int	texture_triangle(t_vector vec, t_triangle *triangle,
	mlx_texture_t *tex)
{
	int	x;
	int	y;
	int	pixel_index;

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
	y = fmodf(fabs(vec.x), 1) * tex->height;
	pixel_index = (y * tex->width + x) * tex->bytes_per_pixel;
	return (get_rgba(tex->pixels[pixel_index],
			tex->pixels[pixel_index + 1],
			tex->pixels[pixel_index + 2], 255));
}
