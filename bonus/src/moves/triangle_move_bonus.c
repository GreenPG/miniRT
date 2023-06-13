/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_move_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:19:19 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/13 11:28:01 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	triangle_rot_y(t_triangle *triangle, double angle)
{
	vector_rot_y(triangle->a, angle);
	vector_rot_y(triangle->b, angle);
	vector_rot_y(triangle->c, angle);
	vector_rot_y(triangle->normal, angle);
}

void	triangle_rot_z(t_triangle *triangle, double angle)
{
	vector_rot_z(triangle->a, angle);
	vector_rot_z(triangle->b, angle);
	vector_rot_z(triangle->c, angle);
	vector_rot_z(triangle->normal, angle);
}

void	triangle_rot_x(t_triangle *triangle, double angle)
{
	vector_rot_x(triangle->a, angle);
	vector_rot_x(triangle->b, angle);
	vector_rot_x(triangle->c, angle);
	vector_rot_x(triangle->normal, angle);
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
