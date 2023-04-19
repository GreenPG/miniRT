/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:37:52 by gtouzali          #+#    #+#             */
/*   Updated: 2023/04/19 11:41:23 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vector	calculate_ray_direction(t_camera camera, unsigned int x, unsigned int y)
{
	t_vector ray;

	ray.x_o = camera.pos.x_o;
	ray.y_o = camera.pos.y_o;
	ray.z_o = camera.pos.z_o;
	ray.x_d = - 2. + (4. * (double)x)/ (double)(WIDTH - 1);
	ray.z_d = 1;
	ray.y_d = 1. - (2. * (double)y )/ (double)(HEIGHT - 1);
	y++;
	return (ray);
} 

double	hit_sphere1(t_vector r)
{
	t_vector oc;
	oc.z_d = -1;
	oc.y_d = 0;
	oc.x_d = 0;


    double a = dot_product(r, r);
    double b = 2.0 * dot_product(oc, r);
    double c = dot_product(oc, oc) - 0.25;
    double discriminant = b*b - 4*a*c;
    if (discriminant > 0)
		return (-b - sqrt(discriminant) ) / (2.0*a);
	return -1;
	
}

double	hit_sphere2(t_vector r)
{
	t_vector oc;
	oc.z_d = -0.7;
	oc.y_d = 0;
	oc.x_d = 0.6;


    double a = dot_product(r, r);
    double b = 2.0 * dot_product(oc, r);
    double c = dot_product(oc, oc) - 0.05;
    double discriminant = b*b - 4*a*c;
    if (discriminant > 0)
		return (-b - sqrt(discriminant) ) / (2.0*a);
	return -1;
	
}

int	get_pixel_color(t_vector ray)
{
	double t;
	t = (hit_sphere1(ray));
	if (t > 0)
		return(get_rgba(205 * ((t*ray.x_d/2) + 1), 205 * ((t*ray.y_d/2) + 1), 255 * (((t*ray.z_d - 1)/2) + 1), 255));
	t = (hit_sphere2(ray));
	if (t > 0)
		return(get_rgba(205 * ((t*ray.x_d/2) + 1), 205 * ((t*ray.y_d/2) + 1), 255 * (((t*ray.z_d - 1)/2) + 1), 255));
	t = -t;
	return(get_rgba((255 * (1 - t) + t * 229),	(255 * (1 - t) + t * 190), (255 * (1 - t) + t * 236), 255));
}
#include <stdio.h>
int	ray_launcher(mlx_t *mlx, mlx_image_t *img, t_camera camera)
{
	unsigned int	x;
	unsigned int	y;
	t_vector ray;

	(void)mlx;

	x = 0;
	while(x < img->width)
	{
		y = 0;
		while (y < img->height)
		{
			ray = calculate_ray_direction(camera, x, y);
			mlx_put_pixel(img, x, y, get_pixel_color(ray));
			y++;
		}
		
		x++;
	}
	printf("%f %f %f\n", camera.pos.x_o, camera.pos.y_o, camera.pos.z_o);
	return (1);
}
