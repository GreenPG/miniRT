/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:36:19 by gtouzali          #+#    #+#             */
/*   Updated: 2023/05/01 11:08:22 by gtouzali         ###   ########.fr       */
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
	int				color;
	
	x = 0;

	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			color = get_background_color(scene->camera->rays->rays[x][y], scene);
			mlx_put_pixel(img, x, y, color);
			y++;
		}
		x++;
	}
	return (1);
}

int init_rays(t_scene *scene)
{
	unsigned int	x;
	unsigned int	y;
	t_rays	*ray_list;

	ray_list = malloc(sizeof(t_rays));
	x = 0;
	ray_list->rays = malloc(WIDTH * sizeof(t_vector *));
	while (x < WIDTH)
	{
		y = 0;
		ray_list->rays[x] = malloc(HEIGHT * sizeof(t_vector));
		while (y < HEIGHT)
		{
			ray_list->rays[x][y] = ray_direction(x , y, *scene->camera);
			y++;
		}
		x++;
	}
	scene->camera->rays = ray_list;
	return (1);

}