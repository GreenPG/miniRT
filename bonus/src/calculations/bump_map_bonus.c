/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:16:59 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/17 13:46:43 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>



static	t_normal	bump_plane(t_plane *plane, t_vector vec, t_normal normal, mlx_texture_t *tex)
{
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
	vec.z = fmodf(vec.z, 1);
	if (vec.z < 0)
		vec.z += 1;
	vec.x = fmodf(vec.x, 1);
	if (vec.x < 0)
		vec.x += 1;
	x = vec.z * tex->width;
	y = vec.x * tex->height;
	uint32_t pixel_index = (y * tex->width + x) * tex->bytes_per_pixel;
	double derivative_u;
	double derivative_v;
	double ratio;

    derivative_u = (double)tex->pixels[pixel_index] / 16.;
	derivative_v = (double)tex->pixels[pixel_index] / 16.;
	pixel_index = (((y + 1) % tex->height)  * tex->width + x) * tex->bytes_per_pixel;
	derivative_u = (double)tex->pixels[pixel_index] / 16. - derivative_u; 
	pixel_index = (y * tex->width + (x + 1) % tex->width) * tex->bytes_per_pixel;
	derivative_v = (double)tex->pixels[pixel_index] / 16. - derivative_v;
	ratio = 1. / sqrt(derivative_u * derivative_u + derivative_v * derivative_v + 1);
	normal.dir.x += -derivative_u * ratio;
    normal.dir.y += -derivative_v * ratio;
	normal.dir.z += ratio - 1;
    return (normal);
}

// int	texture_cylinder(t_vector vec, t_cylinder *cylinder, mlx_texture_t *tex)
// {	
// 	double alpha;
// 	double beta;
// 	int		r;
// 	int		g;
// 	int		b;
	
// 	t_vector	tmp;

// 	tmp.x = cylinder->up->x;
// 	tmp.y = cylinder->up->y;
// 	tmp.z = cylinder->up->z;
// 	t_cyl_calc	data;

// 	data.front.x = 0.0000001;
// 	data.front.y = 1;
// 	data.front.z = 0.0000001;
// 	vec.x -= cylinder->origin->x;
// 	vec.y -= cylinder->origin->y;
// 	vec.z -= cylinder->origin->z;
// 	data.cross = vector_cross(*cylinder->direction, data.front);
// 	vector_norm(&data.cross);
// 	data.angle = acos(dot_product(*cylinder->direction, data.front)
// 			/ (sqrt(dot_product(*cylinder->direction, *cylinder->direction))
// 				* sqrt(dot_product (data.front, data.front))));
// 	rotate_around_axis(&vec, data.cross, -data.angle);
// 	rotate_around_axis(&tmp, data.cross, -data.angle);
// 	data.front.x = 0.0000001;
// 	data.front.y = 0.0000001;
// 	data.front.z = 1;
// 	if (dot_product(tmp, data.front) > -1 + 1e-6)
// 	{
// 		data.cross = vector_cross(tmp, data.front);
// 		vector_norm(&data.cross);
// 		data.angle = acos(dot_product(tmp, data.front)
// 				/ (sqrt(dot_product(tmp, tmp))
// 					* sqrt(dot_product (data.front, data.front))));
// 		rotate_around_axis(&vec, data.cross, data.angle);
// 		alpha = atan2(vec.z, vec.x);
// 		beta = acos(vec.y);
// 	}
// 	else
// 	{
// 		alpha = atan2(-vec.z, -vec.x);
// 		beta = acos(vec.y);
// 	}
// 	int x;
// 	int	y;
// 	x = (beta) / M_PI * tex->width;
// 	y = (alpha + M_PI) / (M_PI * 2.) * tex->height;
// 	uint32_t pixel_index = (y * tex->width + x) * tex->bytes_per_pixel;

//     r = tex->pixels[pixel_index];
//     g = tex->pixels[pixel_index + 1];
//     b = tex->pixels[pixel_index + 2];
    
//     return get_rgba(r,g,b,255);
// }

static t_normal	bump_ellipsoid(t_ellipsoid *ellipsoid, t_vector vec, t_normal normal, mlx_texture_t *tex)
{	
	double alpha;
	double beta;
	
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
		alpha = atan2(vec.y, -vec.x);
		beta = acos(-vec.z);
	}
	int x;
	int	y;
	x = (alpha + M_PI) / (M_PI * 2.)* tex->width;
	y = (beta) / M_PI * tex->height;
	uint32_t pixel_index = (y * tex->width + x) * tex->bytes_per_pixel;
	double derivative_u;
	double derivative_v;
	double ratio;

    derivative_u = (double)tex->pixels[pixel_index] / 16.;
	derivative_v = (double)tex->pixels[pixel_index] / 16.;
	pixel_index = (((y + 1) % tex->height)  * tex->width + x) * tex->bytes_per_pixel;
	derivative_u = (double)tex->pixels[pixel_index] / 16. - derivative_u; 
	pixel_index = (y * tex->width + (x + 1) % tex->width) * tex->bytes_per_pixel;
	derivative_v = (double)tex->pixels[pixel_index] / 16. - derivative_v;
	ratio = 1. / sqrt(derivative_u * derivative_u + derivative_v * derivative_v + 1);
	normal.dir.x += -derivative_u * ratio;
    normal.dir.y += -derivative_v * ratio;
	normal.dir.z += ratio - 1;
    return (normal);
}

static t_normal	bump_sphere(t_sphere *sphere, t_vector vec, t_normal normal, mlx_texture_t	*tex)
{
	double alpha;
	double beta;

	
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
	x = (alpha + M_PI) / (M_PI * 2.) * tex->width;
	y = (beta) / M_PI * tex->height;

	uint32_t pixel_index = (y * tex->width + x) * tex->bytes_per_pixel;
	double derivative_u;
	double derivative_v;
	double ratio;

    derivative_u = (double)tex->pixels[pixel_index] / 16.;
	derivative_v = (double)tex->pixels[pixel_index] / 16.;
	pixel_index = (((y + 1) % tex->height)  * tex->width + x) * tex->bytes_per_pixel;
	derivative_u = (double)tex->pixels[pixel_index] / 16. - derivative_u; 
	pixel_index = (y * tex->width + (x + 1) % tex->width) * tex->bytes_per_pixel;
	derivative_v = (double)tex->pixels[pixel_index] / 16. - derivative_v;
	ratio = 1. / sqrt(derivative_u * derivative_u + derivative_v * derivative_v + 1);
	normal.dir.x += -derivative_u * ratio;
    normal.dir.y += -derivative_v * ratio;
	normal.dir.z += ratio - 1;
    return (normal);
	(void)sphere;
}

t_normal	get_bump(t_obj_list *nearest, t_vector ray, double distance, t_normal normal)
{
	if (nearest->type == sphere && nearest->tex)
		normal = bump_sphere(nearest->sphere, normal.dir, normal, nearest->tex);
	if (nearest->type == plane)
	 	normal = bump_plane(nearest->plane, normal.origin, normal, nearest->tex);
	// if (nearest->type == cylinder)
	//  	color = texture_cylinder(normal.origin, nearest->cylinder, nearest->tex);
	if (nearest->type == ellipsoid)
	 	normal = bump_ellipsoid(nearest->ellipsoid, normal.origin, normal, nearest->tex);
	(void)ray;
	(void)distance;
	return (normal);
}
