/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_move.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:23:06 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/19 11:07:07 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	cylinder_rot_x(t_cylinder *cylinder, double angle)
{
	vector_rot_x(cylinder->origin, angle);
	vector_rot_x(cylinder->direction, angle);
	vector_rot_x(cylinder->up, angle);
	*cylinder->direction = vector_norm(*cylinder->direction);
}

void	cylinder_rot_y(t_cylinder *cylinder, double angle)
{
	vector_rot_y(cylinder->origin, angle);
	vector_rot_y(cylinder->direction, angle);
	vector_rot_y(cylinder->up, angle);
	*cylinder->direction = vector_norm(*cylinder->direction);
}

void	cylinder_rot_z(t_cylinder *cylinder, double angle)
{
	vector_rot_z(cylinder->origin, angle);
	vector_rot_z(cylinder->direction, angle);
	vector_rot_z(cylinder->up, angle);
	*cylinder->direction = vector_norm(*cylinder->direction);
}

void	cylinder_translate(t_cylinder *cylinder, double x, double y,
		double z)
{
	cylinder->origin->x += x;
	cylinder->origin->y += y;
	cylinder->origin->z += z;
}
