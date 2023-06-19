/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_move_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:19:19 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/19 11:47:43 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	triangle_rot_y(t_triangle *triangle, double angle)
{
	vector_rot_y(triangle->a, angle);
	vector_rot_y(triangle->b, angle);
	vector_rot_y(triangle->c, angle);
	vector_rot_y(triangle->normal, angle);
	vector_rot_y(triangle->up, angle);
}

void	triangle_rot_z(t_triangle *triangle, double angle)
{
	vector_rot_z(triangle->a, angle);
	vector_rot_z(triangle->b, angle);
	vector_rot_z(triangle->c, angle);
	vector_rot_z(triangle->normal, angle);
	vector_rot_z(triangle->up, angle);
}

void	triangle_rot_x(t_triangle *triangle, double angle)
{
	vector_rot_x(triangle->a, angle);
	vector_rot_x(triangle->b, angle);
	vector_rot_x(triangle->c, angle);
	vector_rot_x(triangle->normal, angle);
	vector_rot_x(triangle->up, angle);
}

void	triangle_rotate(t_triangle *triangle, int x, int y, int z)
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

void	triangle_translate(t_triangle *triangle, double x, double y, double z)
{
	triangle->a->x += x;
	triangle->a->y += y;
	triangle->a->z += z;
	triangle->b->x += x;
	triangle->b->y += y;
	triangle->b->z += z;
	triangle->c->x += x;
	triangle->c->y += y;
	triangle->c->z += z;
}
