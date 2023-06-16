/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_obj_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:55:26 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/16 13:11:53 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	rotate_one_x(t_obj_list *nearest, int x)
{
	double	angle;

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

static void	rotate_one_y(t_obj_list *nearest, int y)
{
	double	angle;

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

static void	rotate_one_z(t_obj_list *nearest, int z)
{
	double	angle;

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

void	rotate_one(t_obj_list *nearest, int x, int y, int z)
{
	if (!nearest)
		return ;
	if (x)
		rotate_one_x(nearest, x);
	else if (y)
		rotate_one_y(nearest, y);
	else if (z)
		rotate_one_z(nearest, z);
}
