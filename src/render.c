/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:36:19 by gtouzali          #+#    #+#             */
/*   Updated: 2023/04/21 09:01:27 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

double	hit_sphere1(t_vector r)
{
	t_vector oc;
	oc.z_d = 0;
	oc.y_d = -1;
	oc.x_d = 0;


    double a = dot_product(r, r);
    double b = 2.0 * dot_product(oc, r);
    double c = dot_product(oc, oc) - 0.15;
    double discriminant = b*b - 4*a*c;
    if (discriminant > 0)
		return (-b - sqrt(discriminant) ) / (2.0*a);
	return -1;

}

t_vector	ray_direction(t_vector ray, unsigned int x, unsigned int y, t_camera camera)
{
	double alpha;
	double beta;

	alpha = (camera.fov / 2.) - x * (camera.fov / (WIDTH - 1));
	beta = (camera.fov / 2.) * (9. / 16.) - y * ((camera.fov * (9. / 16.)) / (HEIGHT - 1));
	ray.x_o = 0;
	ray.y_o = 0;
	ray.z_o = 0;
	ray.x_d = -sin(alpha) * cos(beta);
	ray.y_d = cos(alpha) * cos(beta);
	ray.z_d = sin(beta);
	return (ray);
}

int	get_background_color(t_vector ray)
{

	double t;

	t = (hit_sphere1(ray));
	if (t > 0)
		return(get_rgba(205 * ((t*ray.x_d/2) + 1), 205 * ((t*ray.y_d/2) + 1), 205 * (((t*ray.z_d )/2) + 1), 255));
	if (ray.y_d > 0.8)
		return(get_rgba(255, 0, 0, 255));
	if (ray.z_d > 0.8)
		return(get_rgba(0, 0, 255, 255));
	if (ray.x_d > 0.8)
		return(get_rgba(0, 255, 0, 255));
	t = (ray.z_d); //bon c style mais prend pas en compte la position orig
	if (t > 0)
		return(get_rgba((255 * (1 - t) + t * 160),	(255 * (1 - t) + t * 150), (255 * (1 - t) + t * 240), 255));
	t = -t;
	return(get_rgba((255 * (1 - t) + t * 229),	(255 * (1 - t) + t * 190), (255 * (1 - t) + t * 236), 255));
}

int	render(mlx_image_t *img, t_camera camera)
{
	unsigned int	x;
	unsigned int	y;
	t_vector		ray;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			ray = ray_direction(ray, x , y, camera);
			mlx_put_pixel(img, x, y, get_background_color(ray));
			y++;
		}
		x++;
	}
	return (1);
}