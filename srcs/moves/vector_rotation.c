/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_rotation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:13:21 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/21 11:13:56 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	vector_rot_z(t_vector *vec, double angle)
{
	t_vector	axis;

	axis.x = 0;
	axis.y = 1;
	axis.z = 0;
	rotate_around_axis(vec, axis, angle);
}

void	vector_rot_y(t_vector *vec, double angle)
{
	t_vector	axis;

	axis.x = 1;
	axis.y = 0;
	axis.z = 0;
	rotate_around_axis(vec, axis, angle);
}

void	vector_rot_x(t_vector *vec, double angle)
{
	t_vector	axis;

	axis.x = 0;
	axis.y = 0;
	axis.z = 1;
	rotate_around_axis(vec, axis, angle);
}
