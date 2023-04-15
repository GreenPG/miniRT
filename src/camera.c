/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:37:52 by gtouzali          #+#    #+#             */
/*   Updated: 2023/04/15 10:24:34 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vector	calculate_ray_direction(void)
{
	t_vector ray;

	ray.x_d = 0;
	return (ray);
}

void	get_pixel_color(t_vector ray)
{
	(void)ray;
}
#include <stdio.h>
int	ray_launcher(mlx_t *mlx, mlx_image_t *img, t_camera camera)
{
	unsigned int	x;
	unsigned int	y;
	t_vector ray;

	x = 0;
	while(x < img->width)
	{
		y = 0;
		while (y < img->height)
		{
			ray = calculate_ray_direction();
			get_pixel_color(ray);
			mlx_put_pixel(img, x, y, get_rgba(x, y, x * y, 255));
			(void)mlx;
			(void)camera;
			y++;
		}
		x++;
	}
	return (1);
}
