/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:37:52 by gtouzali          #+#    #+#             */
/*   Updated: 2023/04/15 15:03:25 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vector	calculate_ray_direction(t_camera camera, unsigned int x, unsigned int y)
{
	t_vector ray;

	ray.x_o = camera.pos.x_o;
	ray.y_o = camera.pos.y_o;
	ray.z_o = camera.pos.z_o;
	ray.x_d = camera.pos.x_o -2. +  4. * (x / ((double)WIDTH - 1));
	ray.y_d = camera.pos.y_o + 1. - 2. * (y / ((double)HEIGHT - 1));
	ray.z_d = 1.;

	return (ray);
}

int	get_pixel_color(t_vector ray)
{
	double t;

	t = (ray.y_d + 1) * 0.5;
	if (t < 0)
		t = -t;
	return(get_rgba((255 * (1 - t) + t * 125),	(255 * (1 - t) + t * 175), (255 * (1 - t) + t * 255), 255));
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
