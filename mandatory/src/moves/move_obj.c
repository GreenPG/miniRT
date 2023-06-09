/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 09:46:54 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/08 15:37:18 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	move_one(t_obj_list *nearest, double x, double y, double z)
{
	if (!nearest)
		return ;
	if (nearest->type == sphere)
		sphere_translate(nearest->sphere, x, y, z);
	else if (nearest->type == cylinder)
		cylinder_translate(nearest->cylinder, x, y, z);
	else if (nearest->type == plane)
		plane_translate(nearest->plane, x, y, z);
}

void	rotate_one(t_obj_list *nearest, int x, int y, int z)
{
	double	angle;

	if (!nearest)
		return ;
	if (x)
	{
		angle = 10 * (M_PI / 180) * x;
		if (nearest->type == cylinder)
			vector_rot_x(nearest->cylinder->direction, angle);
	}
	else if (y)
	{
		angle = 10 * (M_PI / 180) * y;
		if (nearest->type == cylinder)
			vector_rot_y(nearest->cylinder->direction, angle);
	}
	else if (z)
	{
		angle = 10 * (M_PI / 180) * z;
		if (nearest->type == cylinder)
			vector_rot_z(nearest->cylinder->direction, angle);
	}
}

static t_obj_list	*get_nearest_obj(t_obj_list *cursor,
		double nearest_distance, t_vector ray)
{
	t_obj_list	*nearest;
	double		current_distance;

	nearest = NULL;
	while (cursor)
	{
		current_distance = INFINITY;
		if (cursor->type == sphere)
			current_distance = sphere_hit(cursor->sphere, ray);
		else if (cursor->type == cylinder)
			current_distance = cylinder_hit(cursor->cylinder, ray);
		else if (cursor->type == plane)
			current_distance = plane_hit(cursor->plane, ray);
		if (current_distance < nearest_distance)
		{
			nearest = cursor;
			nearest_distance = current_distance;
		}
		cursor = cursor->next;
	}
	return (nearest);
}

static t_obj_list	*get_click_obj(t_vector ray, t_scene *scene)
{
	t_obj_list	*cursor;
	t_obj_list	*nearest;
	double		nearest_distance;

	nearest_distance = INFINITY;
	cursor = scene->obj_list;
	scene->obj_selected = NULL;
	nearest = get_nearest_obj(cursor, nearest_distance, ray);
	if (nearest == NULL)
		return (scene->obj_selected);
	return (nearest);
}

void	mouse_handle(mouse_key_t button, action_t action, modifier_key_t mods,
		void *param)
{
	int		x;
	int		y;
	t_data	*data;

	data = param;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
	{
		mlx_get_mouse_pos(data->mlx, &x, &y);
		x = x * ((double)WIDTH / (double)data->mlx->width);
		y = y * ((double)HEIGHT / (double)data->mlx->height);
		if (data && data->scene && data->scene->camera->rays->rays)
			data->scene->obj_selected
				= get_click_obj(data->scene->camera->rays->rays[x][y],
					data->scene);
	}
	(void)button;
	(void)action;
	(void)mods;
	(void)param;
}
