/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:37:52 by gtouzali          #+#    #+#             */
/*   Updated: 2023/04/14 15:11:55 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vector	calculate_ray_direction(void)
{
	t_vector ray;

	return (ray);
}

int	ray_launcher(mlx_t *mlx, mlx_image_t *img, t_camera camera)
{
	int	x;
	int	y;
	t_vector ray;

	x = 0;
	while(x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			ray = calculate_ray_direction();
			get_pixel_color(ray);
			y++;
		}
		x++;
	}
	return (1);
}
