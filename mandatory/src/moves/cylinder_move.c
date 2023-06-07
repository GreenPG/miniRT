/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:23:06 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/07 13:50:36 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	cylinder_rot_x(t_cylinder *cylinder, double angle)
{
	vector_rot_x(cylinder->origin, angle);
	vector_rot_x(cylinder->direction, angle);
		double	len;

	len = sqrt(dot_product(*cylinder->direction, *cylinder->direction));
	cylinder->direction->x /= len;
	cylinder->direction->y /= len;
	cylinder->direction->z /= len;
}

void	cylinder_rot_y(t_cylinder *cylinder, double angle)
{
	vector_rot_y(cylinder->origin, angle);
	vector_rot_y(cylinder->direction, angle);
		double	len;

	len = sqrt(dot_product(*cylinder->direction, *cylinder->direction));
	cylinder->direction->x /= len;
	cylinder->direction->y /= len;
	cylinder->direction->z /= len;
}

void	cylinder_rot_z(t_cylinder *cylinder, double angle)
{
	vector_rot_z(cylinder->origin, angle);
	vector_rot_z(cylinder->direction, angle);
		double	len;

	len = sqrt(dot_product(*cylinder->direction, *cylinder->direction));
	cylinder->direction->x /= len;
	cylinder->direction->y /= len;
	cylinder->direction->z /= len;
}

void	cylinder_translate(t_cylinder *cylinder, double x, double y,
		double z)
{
	cylinder->origin->x += x;
	cylinder->origin->y += y;
	cylinder->origin->z += z;
}
