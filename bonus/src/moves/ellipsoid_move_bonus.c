/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid_move_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:27:21 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/08 16:05:11 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	ellipsoid_rot_y(t_ellipsoid *ellipsoid, double angle)
{
	vector_rot_y(ellipsoid->origin, angle);
	vector_rot_y(ellipsoid->direction, angle);
	ellipsoid->alpha -= angle;
}

void	ellipsoid_rot_x(t_ellipsoid *ellipsoid, double angle)
{
	vector_rot_x(ellipsoid->origin, angle);
	vector_rot_x(ellipsoid->direction, angle);
	ellipsoid->alpha -= angle;
}

void	ellipsoid_translate(t_ellipsoid *ellipsoid, double x, double y,
		double z)
{
	ellipsoid->origin->x += x;
	ellipsoid->origin->y += y;
	ellipsoid->origin->z += z;
}
