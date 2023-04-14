/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:37:52 by gtouzali          #+#    #+#             */
/*   Updated: 2023/04/14 13:35:25 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	ray_launcher(mlx_t *mlx, t_camera *camera)
{
	int	x;
	int	y;
	t_vector ray;

	x = 0;
	ray = NULL
	while(x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			ray = calculate_ray_direction()
			y++;
		}
		x++;
	}
}
