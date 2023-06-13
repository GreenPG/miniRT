/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_move_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:29:26 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/13 13:31:14 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	sphere_rot_x(t_sphere *sphere, double angle)
{
	vector_rot_x(sphere->origin, angle);
	vector_rot_x(sphere->direction, angle);
	vector_rot_x(sphere->up, angle);
}

void	sphere_rot_y(t_sphere *sphere, double angle)
{
	vector_rot_y(sphere->origin, angle);
	vector_rot_y(sphere->direction, angle);
	vector_rot_y(sphere->up, angle);
}

void	sphere_rot_z(t_sphere *sphere, double angle)
{
	vector_rot_z(sphere->origin, angle);
	vector_rot_z(sphere->direction, angle);
	vector_rot_z(sphere->up, angle);
}

void	sphere_translate(t_sphere *sphere, double x, double y, double z)
{
	sphere->origin->x += x;
	sphere->origin->y += y;
	sphere->origin->z += z;
}
