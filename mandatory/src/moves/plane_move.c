/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:27:21 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/06 09:47:06 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	plane_rot_y(t_plane *plane, double angle)
{
	vector_rot_y(plane->origin, angle);
	vector_rot_y(plane->direction, angle);
}

void	plane_rot_x(t_plane *plane, double angle)
{
	vector_rot_x(plane->origin, angle);
	vector_rot_x(plane->direction, angle);
}

void	plane_rot_z(t_plane *plane, double angle)
{
	vector_rot_z(plane->origin, angle);
	vector_rot_z(plane->direction, angle);
}

void	plane_translate(t_plane *plane, double x, double y, double z)
{
	plane->origin->x += x;
	plane->origin->y += y;
	plane->origin->z += z;
}
