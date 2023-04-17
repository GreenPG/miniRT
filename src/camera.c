/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:37:52 by gtouzali          #+#    #+#             */
/*   Updated: 2023/04/17 17:16:16 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vector	calculate_ray_direction(t_camera camera, unsigned int x, unsigned int y)
{
	t_vector ray;
	double	alpha; //width [-fov/2, fov/2]
	double	beta; //height [-const/2, const/2]
	double	height_fov;

	height_fov = camera.fov * (9. / 16.);
	alpha = (-camera.fov / 2) + (double)x * (camera.fov / (double)(WIDTH - 1)) - asin(camera.pos.x_d / cos(asin(-camera.pos.y_d)));
	beta = (height_fov / 2) - (double)y * (height_fov / (double)(HEIGHT - 1)) - asin(-camera.pos.y_d);
	ray.x_o = camera.pos.x_o;
	ray.y_o = camera.pos.y_o;
	ray.z_o = camera.pos.z_o;
	ray.x_d = camera.pos.x_o + sin(alpha) * cos(beta);
	ray.y_d = camera.pos.y_o - sin(beta);
	ray.z_d = camera.pos.z_o + cos(alpha) * cos(beta);

	return (ray);
} 

int	get_pixel_color(t_vector ray)
{
	double t;

	t = (ray.y_d); //bon c style mais prend pas en compte la position orig + la rotation ca marche mais pas trop quoi
	if (t > 0)
		return(get_rgba((255 * (1 - t) + t * 160),	(255 * (1 - t) + t * 150), (255 * (1 - t) + t * 240), 255));
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
