/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:36:19 by gtouzali          #+#    #+#             */
/*   Updated: 2023/04/27 14:19:07 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vector	ray_direction(unsigned int x, unsigned int y, t_camera camera)
{
	double alpha;
	double beta;
	t_vector ray;

	alpha = (camera.fov / 2.) - x * (camera.fov / (WIDTH - 1));
	beta = (camera.fov / 2.) * (9. / 16.) - y * (camera.fov / (WIDTH - 1));
	//beta = (camera.fov / 2.) * (9. / 16.) - y * ((camera.fov * (9. / 16.)) / (HEIGHT - 1));
	ray.x_o = 0;
	ray.y_o = 0;
	ray.z_o = 0;
	ray.x_d = -sin(alpha) * cos(beta);
	ray.y_d = cos(alpha) * cos(beta);
	ray.z_d = sin(beta);
	return (ray);
}

int	get_background_color(t_vector ray, t_scene *scene)
{
	t_obj_list	*cursor;
	t_obj_list	*nearest;
	double		nearest_distance;
	double		current_distance;

	nearest = NULL;
	nearest_distance = INFINITY;
	cursor = scene->obj_list;
	while (cursor)
	{
		current_distance = INFINITY;
		if (cursor->type == sphere)
			current_distance = sphere_hit(cursor->obj, ray);
			// else if (cursor->type == cylinder)
			// 	current_distance = cylinder_hit(cursor->obj, ray);
			else if (cursor->type == plane)
				current_distance = plane_hit(cursor->obj, ray);
		if (current_distance < nearest_distance)
		{
			nearest = cursor;
			nearest_distance = current_distance;
		}
		cursor = cursor->next;
	}
	return (get_obj_color(nearest, ray));
}

int	render(mlx_image_t *img, t_scene *scene)
{
	unsigned int	x;
	unsigned int	y;
	t_vector		ray;
	int				color;
	
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			ray = ray_direction(x , y, *scene->camera);
			color = get_background_color(ray, scene);
			mlx_put_pixel(img, x, y, color);
			y++;
		}
		x++;
	}
	return (1);
}