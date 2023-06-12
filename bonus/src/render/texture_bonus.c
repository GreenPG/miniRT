/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:16:59 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/12 15:41:41 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static int	texture_sphere(t_vector vec, t_camera *camera, t_sphere *sphere)
{
	double alpha;
	double beta;
	int		r;
	int		g;
	int		b;
	
	alpha = atan2(vec.y, vec.x);
	beta = acos(vec.z);
	int x;
	int	y;
	x = (alpha + M_PI) / (M_PI * 2.)* sphere->tex->width;
	y = (beta) / M_PI * sphere->tex->height;
	uint32_t pixel_index = (y * sphere->tex->width + x) * sphere->tex->bytes_per_pixel;

    r = sphere->tex->pixels[pixel_index];
    g = sphere->tex->pixels[pixel_index + 1];
    b = sphere->tex->pixels[pixel_index + 2];
    
    return get_rgba(r,g,b,255);
	(void)camera;
	return (0);
}

int	texture_plane(t_vector vec, t_plane *plane, t_camera *camera)
{
	double alpha;
	double beta;
	int		r;
	int		g;
	int		b;
	
	alpha = atan2(vec.y, vec.x);
	beta = acos(vec.z);
	int x;
	int	y;
	x = (alpha + M_PI) / (M_PI * 2.)* plane->tex->width;
	y = (beta) / M_PI * plane->tex->height;
	uint32_t pixel_index = (y * plane->tex->width + x) * plane->tex->bytes_per_pixel;

    r = plane->tex->pixels[pixel_index];
    g = plane->tex->pixels[pixel_index + 1];
    b = plane->tex->pixels[pixel_index + 2];
    
    return get_rgba(r,g,b,255);
	(void)camera;
	return (0);
}

int	texture_cylinder(t_vector vec, t_cylinder *cyl, t_camera *camera)
{	
	vec.x = vec.x - cyl->origin->x;
	vec.y = vec.y - cyl->origin->y;
	vec.z = vec.z - cyl->origin->z;
	vector_rot_y(&vec, camera->beta * (M_PI / 180));
	vector_rot_x(&vec, -camera->alpha * (M_PI / 180));
	if ((int)floor(vec.z) % 2 == 0)
	{
		if ((int)(floor(vec.x) + floor(vec.y)) % 2 == 0)
			return (get_rgba(255,255,255,0));
		return (0);
	}
	else
	{
		if ((int)(floor(vec.x) + floor(vec.y)) % 2 == 0)
			return (0);
		return (get_rgba(255,255,255,0));
	}
	(void)camera;
}

int	texture_ellipsoid(t_vector vec, t_ellipsoid *ellipsoid, t_camera *camera)
{	
	double alpha;
	double beta;
	int		r;
	int		g;
	int		b;
	
	alpha = atan2(vec.y, vec.x);
	beta = acos(vec.z);
	int x;
	int	y;
	x = (alpha + M_PI) / (M_PI * 2.)* ellipsoid->tex->width;
	y = (beta) / M_PI * ellipsoid->tex->height;
	uint32_t pixel_index = (y * ellipsoid->tex->width + x) * ellipsoid->tex->bytes_per_pixel;

    r = ellipsoid->tex->pixels[pixel_index];
    g = ellipsoid->tex->pixels[pixel_index + 1];
    b = ellipsoid->tex->pixels[pixel_index + 2];
    
    return get_rgba(r,g,b,255);
	(void)camera;
	return (0);
}

int	get_texture(t_obj_list *nearest, t_vector ray, t_normal normal, t_camera *camera)
{
	int			color;

	color = 0;
	if (nearest->type == sphere)
		color = texture_sphere(normal.dir, camera, nearest->sphere);
	if (nearest->type == plane)
		color = texture_plane(normal.origin, nearest->plane, camera);
	if (nearest->type == cylinder)
	 	color = texture_cylinder(normal.origin, nearest->cylinder, camera);
	if (nearest->type == ellipsoid)
	 	color = texture_ellipsoid(normal.dir, nearest->ellipsoid, camera);
	(void)ray;
	(void)nearest;
	return (color);
}