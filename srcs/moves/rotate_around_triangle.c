/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_around_triangle.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:23:13 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/20 16:26:52 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	tr_x_rotate(t_triangle *triangle, int x)
{
	double	angle;

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

static void	tr_y_rotate(t_triangle *triangle, int y)
{
	double	angle;

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

static void	tr_z_rotate(t_triangle *triangle, int z)
{
	double	angle;

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

void	triangle_rotate(t_triangle *triangle, int x, int y, int z)
{
	if (x)
		tr_x_rotate(triangle, x);
	else if (y)
		tr_y_rotate(triangle, y);
	else if (z)
		tr_z_rotate(triangle, z);
}
