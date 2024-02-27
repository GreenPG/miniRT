/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:36:19 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/14 16:54:51 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static double	get_distance(t_obj_list *cursor, t_vector ray)
{
	double	current_distance;

	current_distance = INFINITY;
	if (cursor->type == sphere)
		current_distance = sphere_hit(cursor->sphere, ray);
	else if (cursor->type == cylinder)
		current_distance = cylinder_hit(cursor->cylinder, ray);
	else if (cursor->type == plane)
		current_distance = plane_hit(cursor->plane, ray);
	else if (cursor->type == ellipsoid)
		current_distance = ellipsoid_hit(cursor->ellipsoid, ray);
	else if (cursor->type == triangle)
		current_distance = triangle_hit(cursor->triangle, ray);
	return (current_distance);
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
		current_distance = get_distance(cursor, ray);
		if (current_distance < nearest_distance)
		{
			if (nearest && nearest->type == cylinder)
				nearest->cylinder->hit_body = false;
			nearest = cursor;
			nearest_distance = current_distance;
		}
		cursor = cursor->next;
	}
	if (nearest)
		nearest->hitted = 1;
	return (get_obj_color(nearest, ray, scene, nearest_distance));
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
			color = get_background_color(scene->camera->rays->rays[x][y],
					scene);
			mlx_put_pixel(img, x, y, color);
			y++;
		}
		x++;
	}
	return (1);
}
