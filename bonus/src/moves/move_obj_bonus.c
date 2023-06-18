/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_obj_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 09:46:54 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/18 09:52:36 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

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
	else if (nearest->type == ellipsoid)
		ellipsoid_translate(nearest->ellipsoid, x, y, z);
	else if (nearest->type == triangle)
		triangle_translate(nearest->triangle, x, y, z);
}

static void	triangle_rotate(t_triangle *triangle, int x, int y, int z)
{
	double	angle;

	if (x)
	{
		angle = 10 * (M_PI / 180) * x;
		triangle->b->x -= triangle->a->x;
		triangle->b->y -= triangle->a->y;
		triangle->b->z -= triangle->a->z;
		triangle->c->x -= triangle->a->x;
		triangle->c->y -= triangle->a->y;
		triangle->c->z -= triangle->a->z;
		vector_rot_x(triangle->b, angle);
		vector_rot_x(triangle->c, angle);
		triangle->b->x += triangle->a->x;
		triangle->b->y += triangle->a->y;
		triangle->b->z += triangle->a->z;
		triangle->c->x += triangle->a->x;
		triangle->c->y += triangle->a->y;
		triangle->c->z += triangle->a->z;
		vector_rot_x(triangle->normal, angle);
		vector_rot_x(triangle->up, angle);
	}
	else if (y)
	{
		angle = 10 * (M_PI / 180) * y;
		triangle->b->x -= triangle->a->x;
		triangle->b->y -= triangle->a->y;
		triangle->b->z -= triangle->a->z;
		triangle->c->x -= triangle->a->x;
		triangle->c->y -= triangle->a->y;
		triangle->c->z -= triangle->a->z;
		vector_rot_y(triangle->b, angle);
		vector_rot_y(triangle->c, angle);
		triangle->b->x += triangle->a->x;
		triangle->b->y += triangle->a->y;
		triangle->b->z += triangle->a->z;
		triangle->c->x += triangle->a->x;
		triangle->c->y += triangle->a->y;
		triangle->c->z += triangle->a->z;
		vector_rot_y(triangle->normal, angle);
		vector_rot_y(triangle->up, angle);
	}
	else if (z)
	{
		angle = 10 * (M_PI / 180) * z;
		triangle->b->x -= triangle->a->x;
		triangle->b->y -= triangle->a->y;
		triangle->b->z -= triangle->a->z;
		triangle->c->x -= triangle->a->x;
		triangle->c->y -= triangle->a->y;
		triangle->c->z -= triangle->a->z;
		vector_rot_z(triangle->b, angle);
		vector_rot_z(triangle->c, angle);
		triangle->b->x += triangle->a->x;
		triangle->b->y += triangle->a->y;
		triangle->b->z += triangle->a->z;
		triangle->c->x += triangle->a->x;
		triangle->c->y += triangle->a->y;
		triangle->c->z += triangle->a->z;
		vector_rot_z(triangle->normal, angle);
		vector_rot_z(triangle->up, angle);
	}
}

void	rotate_one(t_obj_list *nearest, int x, int y, int z)
{
	double	angle;

	if (!nearest)
		return ;
	if (nearest->type == triangle)
		triangle_rotate(nearest->triangle, x, y, z);
	else if (x)
	{
		angle = 10 * (M_PI / 180) * x;
		if (nearest->type == cylinder)
		{
			vector_rot_x(nearest->cylinder->direction, angle);
			vector_rot_x(nearest->cylinder->up, angle);
		}
		if (nearest->type == plane)
		{
			vector_rot_x(nearest->plane->direction, angle);
			vector_rot_x(nearest->plane->up, angle);
		}
		if (nearest->type == ellipsoid)
		{
			vector_rot_x(nearest->ellipsoid->direction, angle);
			vector_rot_x(nearest->ellipsoid->up, angle);
		}
		if (nearest->type == sphere)
		{
			vector_rot_x(nearest->sphere->direction, angle);
			vector_rot_x(nearest->sphere->up, angle);
		}
	}
	else if (y)
	{
		angle = 10 * (M_PI / 180) * y;
		if (nearest->type == cylinder)
		{
			vector_rot_y(nearest->cylinder->direction, angle);
			vector_rot_y(nearest->cylinder->up, angle);
		}
		if (nearest->type == plane)
		{
			vector_rot_y(nearest->plane->direction, angle);
			vector_rot_y(nearest->plane->up, angle);
		}
		if (nearest->type == ellipsoid)
		{
			vector_rot_y(nearest->ellipsoid->direction, angle);
			vector_rot_y(nearest->ellipsoid->up, angle);
		}
		if (nearest->type == sphere)
		{
			vector_rot_y(nearest->sphere->direction, angle);
			vector_rot_y(nearest->sphere->up, angle);
		}
	}
	else if (z)
	{
		angle = 10 * (M_PI / 180) * z;
		if (nearest->type == cylinder)
		{
			vector_rot_z(nearest->cylinder->direction, angle);
			vector_rot_z(nearest->cylinder->up, angle);
		}
		if (nearest->type == plane)
		{
			vector_rot_z(nearest->plane->direction, angle);
			vector_rot_z(nearest->plane->up, angle);
		}
		if (nearest->type == ellipsoid)
		{
			vector_rot_z(nearest->ellipsoid->direction, angle);
			vector_rot_z(nearest->ellipsoid->up, angle);
		}
		if (nearest->type == sphere)
		{
			vector_rot_z(nearest->sphere->direction, angle);
			vector_rot_z(nearest->sphere->up, angle);
		}
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
		else if (cursor->type == ellipsoid)
			current_distance = ellipsoid_hit(cursor->ellipsoid, ray);
		else if (cursor->type == triangle)
			current_distance = triangle_hit(cursor->triangle, ray);
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
