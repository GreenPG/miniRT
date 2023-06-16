/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_move_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:54:16 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/16 09:03:32 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	world_rot_x(t_scene *scene, double angle)
{
	vector_rot_x(scene->direction, angle);
	vector_rot_x(scene->up, angle);
	vector_norm(scene->up);
	vector_norm(scene->direction);
}

void	world_rot_y(t_scene *scene, double angle)
{
	vector_rot_y(scene->direction, angle);
	vector_rot_y(scene->up, angle);
	vector_norm(scene->up);
	vector_norm(scene->direction);
}

void	world_rot_z(t_scene *scene, double angle)
{
	vector_rot_z(scene->direction, angle);
	vector_rot_z(scene->up, angle);
	vector_norm(scene->up);
	vector_norm(scene->direction);
}
