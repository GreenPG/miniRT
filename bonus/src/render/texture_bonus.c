/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:16:59 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/27 08:53:27 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static int	texture_sphere(t_vector vec, t_sphere *sphere, mlx_texture_t *tex)
{
	int				x;
	int				y;
	unsigned int	pixel_index;

	vec = camera_to_object_space(vec, *sphere->direction, *sphere->up);
	x = (atan2(vec.y, vec.x) + M_PI) / (M_PI * 2.) * tex->width;
	y = acos(vec.z) / M_PI * tex->height;
	pixel_index = (y * tex->width + x) * tex->bytes_per_pixel;
	if (pixel_index > tex->width * tex->height * tex->bytes_per_pixel)
		pixel_index = (tex->width * tex->height - 1) * tex->bytes_per_pixel;
	return (get_rgba(tex->pixels[pixel_index],
			tex->pixels[pixel_index + 1],
			tex->pixels[pixel_index + 2], 255));
}

static int	texture_plane(t_vector vec, t_plane *plane, mlx_texture_t *tex)
{
	int				x;
	int				y;
	unsigned int	pixel_index;

	vec.x -= plane->origin->x;
	vec.y -= plane->origin->y;
	vec.z -= plane->origin->z;
	vec = camera_to_object_space(vec, *plane->direction, *plane->up);
	vec.z = fmodf(vec.z, 1);
	if (vec.z < 0)
		vec.z += 1;
	vec.x = fmodf(vec.x, 1);
	if (vec.x < 0)
		vec.x += 1;
	x = vec.z * tex->width;
	y = vec.x * tex->height;
	pixel_index = (y * tex->width + x) * tex->bytes_per_pixel;
	if (pixel_index > tex->width * tex->height * tex->bytes_per_pixel)
		pixel_index = (tex->width * tex->height - 1) * tex->bytes_per_pixel;
	return (get_rgba(tex->pixels[pixel_index],
			tex->pixels[pixel_index + 1],
			tex->pixels[pixel_index + 2], 255));
}

static int	texture_cylinder(t_vector vec, t_cylinder *cylinder,
	mlx_texture_t *tex)
{
	int				x;
	int				y;
	unsigned int	pixel_index;

	vec.x -= cylinder->origin->x;
	vec.y -= cylinder->origin->y;
	vec.z -= cylinder->origin->z;
	vec = camera_to_object_space(vec, *cylinder->direction, *cylinder->up);
	x = ((vec.y + cylinder->height / 2) / cylinder->height) * tex->width;
	y = (atan2(vec.z, vec.x) + M_PI) / (M_PI * 2.) * tex->height;
	pixel_index = (y * tex->width + x) * tex->bytes_per_pixel;
	if (pixel_index > tex->width * tex->height * tex->bytes_per_pixel)
		pixel_index = (tex->width * tex->height - 1) * tex->bytes_per_pixel;
	return (get_rgba(tex->pixels[pixel_index],
			tex->pixels[pixel_index + 1],
			tex->pixels[pixel_index + 2], 255));
}

static int	texture_ellipsoid(t_vector vec, t_ellipsoid *ellipsoid,
	mlx_texture_t *tex)
{		
	int				x;
	int				y;
	unsigned int	pixel_index;

	vec.x -= ellipsoid->origin->x;
	vec.y -= ellipsoid->origin->y;
	vec.z -= ellipsoid->origin->z;
	vec = camera_to_object_space(vec, *ellipsoid->direction, *ellipsoid->up);
	x = (atan2(vec.y, -vec.x) + M_PI) / (M_PI * 2.) * tex->width;
	y = (1 - ((vec.z + (1. / ellipsoid->c)) / ((1. / ellipsoid->c) * 2)))
		* tex->height;
	if (ellipsoid->c > 1)
		y = (1 - acos(vec.z) / M_PI) * tex->height;
	pixel_index = (y * tex->width + x) * tex->bytes_per_pixel;
	if (pixel_index > tex->width * tex->height * tex->bytes_per_pixel)
		pixel_index = (tex->width * tex->height - 1) * tex->bytes_per_pixel;
	return (get_rgba(tex->pixels[pixel_index],
			tex->pixels[pixel_index + 1],
			tex->pixels[pixel_index + 2], 255));
}

int	get_texture(t_obj_list *near, t_normal normal)
{
	int			color;

	color = 0;
	if (near->type == sphere)
		color = texture_sphere(normal.dir, near->sphere, near->tex);
	if (near->type == plane)
		color = texture_plane(normal.origin, near->plane, near->tex);
	if (near->type == cylinder)
		color = texture_cylinder(normal.origin, near->cylinder, near->tex);
	if (near->type == ellipsoid)
		color = texture_ellipsoid(normal.origin, near->ellipsoid, near->tex);
	if (near->type == triangle)
		color = texture_triangle(normal.origin, near->triangle, near->tex);
	return (color);
}
