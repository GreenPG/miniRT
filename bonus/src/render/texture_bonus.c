/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:16:59 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/15 17:09:40 by gtouzali         ###   ########.fr       */
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
	
	t_vector	tmp;

	tmp.x = sphere->up->x;
	tmp.y = sphere->up->y;
	tmp.z = sphere->up->z;
	t_cyl_calc	data;

	data.front.x = 0.0000001;
	data.front.y = 1;
	data.front.z = 0.0000001;
	data.cross = vector_cross(*sphere->direction, data.front);
	vector_norm(&data.cross);
	data.angle = acos(dot_product(*sphere->direction, data.front)
			/ (sqrt(dot_product(*sphere->direction, *sphere->direction))
				* sqrt(dot_product (data.front, data.front))));
	rotate_around_axis(&vec, data.cross, -data.angle);
	rotate_around_axis(&tmp, data.cross, -data.angle);
	data.front.x = 0.0000001;
	data.front.y = 0.0000001;
	data.front.z = 1;
	if (dot_product(tmp, data.front) > -1 + 1e-6)
	{
		data.cross = vector_cross(tmp, data.front);
		vector_norm(&data.cross);
		data.angle = acos(dot_product(tmp, data.front)
				/ (sqrt(dot_product(tmp, tmp))
					* sqrt(dot_product (data.front, data.front))));
		rotate_around_axis(&vec, data.cross, data.angle);
		alpha = atan2(vec.y, vec.x);
		beta = acos(vec.z);
	}
	else
	{
		alpha = atan2(vec.y, -vec.x);
		beta = acos(-vec.z);
	}
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
	int	r;
	int	g;
	int	b;	
	t_vector	tmp;

	tmp.x = plane->up->x;
	tmp.y = plane->up->y;
	tmp.z = plane->up->z;
	t_cyl_calc	data;

	data.front.x = 0.0000001;
	data.front.y = 1;
	data.front.z = 0.0000001;
	data.cross = vector_cross(*plane->direction, data.front);
	vector_norm(&data.cross);
	data.angle = acos(dot_product(*plane->direction, data.front)
			/ (sqrt(dot_product(*plane->direction, *plane->direction))
				* sqrt(dot_product (data.front, data.front))));
	rotate_around_axis(&vec, data.cross, -data.angle);
	rotate_around_axis(&tmp, data.cross, -data.angle);
	data.front.x = 0.0000001;
	data.front.y = 0.0000001;
	data.front.z = 1;
	if (dot_product(tmp, data.front) > -1 + 1e-6)
	{
		data.cross = vector_cross(tmp, data.front);
		vector_norm(&data.cross);
		data.angle = acos(dot_product(tmp, data.front)
				/ (sqrt(dot_product(tmp, tmp))
					* sqrt(dot_product (data.front, data.front))));
		rotate_around_axis(&vec, data.cross, data.angle);
	}
	else
	{
		vec.x = -vec.x;
		vec.z = -vec.z;
	}
	int x;
	int	y;
	vec.y = fmodf(vec.y, 1);
	if (vec.y < 0)
		vec.y += 1;
	vec.x = fmodf(vec.x, 1);
	if (vec.x < 0)
		vec.x += 1;
	x =  vec.y * plane->tex->width;
	y =  fmodf(fabs(vec.x), 1) * plane->tex->height;
	uint32_t pixel_index = (y * plane->tex->width + x) * plane->tex->bytes_per_pixel;

    r = plane->tex->pixels[pixel_index];
    g = plane->tex->pixels[pixel_index + 1];
    b = plane->tex->pixels[pixel_index + 2];
    
    return get_rgba(r,g,b,255);
	(void)camera;
}

int	texture_cylinder(t_vector vec, t_cylinder *cylinder)
{	
	double alpha;
	double beta;
	int		r;
	int		g;
	int		b;
	
	t_vector	tmp;

	tmp.x = cylinder->up->x;
	tmp.y = cylinder->up->y;
	tmp.z = cylinder->up->z;
	t_cyl_calc	data;

	data.front.x = 0.0000001;
	data.front.y = 1;
	data.front.z = 0.0000001;
	vec.x -= cylinder->origin->x;
	vec.y -= cylinder->origin->y;
	vec.z -= cylinder->origin->z;
	data.cross = vector_cross(*cylinder->direction, data.front);
	vector_norm(&data.cross);
	data.angle = acos(dot_product(*cylinder->direction, data.front)
			/ (sqrt(dot_product(*cylinder->direction, *cylinder->direction))
				* sqrt(dot_product (data.front, data.front))));
	rotate_around_axis(&vec, data.cross, -data.angle);
	rotate_around_axis(&tmp, data.cross, -data.angle);
	data.front.x = 0.0000001;
	data.front.y = 0.0000001;
	data.front.z = 1;
	if (dot_product(tmp, data.front) > -1 + 1e-6)
	{
		data.cross = vector_cross(tmp, data.front);
		vector_norm(&data.cross);
		data.angle = acos(dot_product(tmp, data.front)
				/ (sqrt(dot_product(tmp, tmp))
					* sqrt(dot_product (data.front, data.front))));
		rotate_around_axis(&vec, data.cross, data.angle);
		alpha = atan2(vec.z, vec.x);
		beta = acos(vec.y);
	}
	else
	{
		alpha = atan2(-vec.z, -vec.x);
		beta = acos(vec.y);
	}
	int x;
	int	y;
	x = (beta) / M_PI * cylinder->tex->width;
	y = (alpha + M_PI) / (M_PI * 2.) * cylinder->tex->height;
	uint32_t pixel_index = (y * cylinder->tex->width + x) * cylinder->tex->bytes_per_pixel;

    r = cylinder->tex->pixels[pixel_index];
    g = cylinder->tex->pixels[pixel_index + 1];
    b = cylinder->tex->pixels[pixel_index + 2];
    
    return get_rgba(r,g,b,255);
}

int	texture_ellipsoid(t_vector vec, t_ellipsoid *ellipsoid)
{	
	double alpha;
	double beta;
	int		r;
	int		g;
	int		b;
	
	t_vector	tmp;

	tmp.x = ellipsoid->up->x;
	tmp.y = ellipsoid->up->y;
	tmp.z = ellipsoid->up->z;
	t_cyl_calc	data;

	data.front.x = 0.0000001;
	data.front.y = 1;
	data.front.z = 0.0000001;
	vec.x -= ellipsoid->origin->x;
	vec.y -= ellipsoid->origin->y;
	vec.z -= ellipsoid->origin->z;
	data.cross = vector_cross(*ellipsoid->direction, data.front);
	vector_norm(&data.cross);
	data.angle = acos(dot_product(*ellipsoid->direction, data.front)
			/ (sqrt(dot_product(*ellipsoid->direction, *ellipsoid->direction))
				* sqrt(dot_product (data.front, data.front))));
	rotate_around_axis(&vec, data.cross, -data.angle);
	rotate_around_axis(&tmp, data.cross, -data.angle);
	data.front.x = 0.0000001;
	data.front.y = 0.0000001;
	data.front.z = 1;
	if (dot_product(tmp, data.front) > -1 + 1e-6)
	{
		data.cross = vector_cross(tmp, data.front);
		vector_norm(&data.cross);
		data.angle = acos(dot_product(tmp, data.front)
				/ (sqrt(dot_product(tmp, tmp))
					* sqrt(dot_product (data.front, data.front))));
		rotate_around_axis(&vec, data.cross, data.angle);
		alpha = atan2(vec.y, vec.x);
		beta = acos(vec.z);
	}
	else
	{
		alpha = atan2(vec.y, vec.x);
		beta = acos(-vec.z);
	}
	int x;
	int	y;
	x = (alpha + M_PI) / (M_PI * 2.)* ellipsoid->tex->width;
	y = (beta) / M_PI * ellipsoid->tex->height;
	uint32_t pixel_index = (y * ellipsoid->tex->width + x) * ellipsoid->tex->bytes_per_pixel;

    r = ellipsoid->tex->pixels[pixel_index];
    g = ellipsoid->tex->pixels[pixel_index + 1];
    b = ellipsoid->tex->pixels[pixel_index + 2];
    
    return get_rgba(r,g,b,255);
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
	 	color = texture_cylinder(normal.origin, nearest->cylinder);
	if (nearest->type == ellipsoid)
	 	color = texture_ellipsoid(normal.origin, nearest->ellipsoid);
	(void)ray;
	(void)nearest;
	return (color);
}