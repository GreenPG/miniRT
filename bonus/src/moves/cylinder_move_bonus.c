/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_move_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:23:06 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/02 15:00:09 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	cylinder_rot_x(t_cylinder *cylinder, double angle)
{
	vector_rot_x(cylinder->origin, angle);
	vector_rot_x(cylinder->direction, angle);
	cylinder->alpha -= angle;
}

void	cylinder_rot_y(t_cylinder *cylinder, double angle)
{
	vector_rot_y(cylinder->origin, angle);
	vector_rot_y(cylinder->direction, angle);
	cylinder->beta -= angle;
}

void	cylinder_translate(t_cylinder *cylinder, double x, double y,
		double z)
{
	cylinder->origin->x += x;
	cylinder->origin->y += y;
	cylinder->origin->z += z;
}
