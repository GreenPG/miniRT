/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_move.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:54:16 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/16 15:13:24 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	world_rot_x(t_scene *scene, double angle)
{
	vector_rot_x(scene->direction, angle);
	vector_rot_x(scene->up, angle);
	*scene->up = vector_norm(*scene->up);
	*scene->direction = vector_norm(*scene->direction);
}

void	world_rot_y(t_scene *scene, double angle)
{
	vector_rot_y(scene->direction, angle);
	vector_rot_y(scene->up, angle);
	*scene->up = vector_norm(*scene->up);
	*scene->direction = vector_norm(*scene->direction);
}

void	world_rot_z(t_scene *scene, double angle)
{
	vector_rot_z(scene->direction, angle);
	vector_rot_z(scene->up, angle);
	*scene->up = vector_norm(*scene->up);
	*scene->direction = vector_norm(*scene->direction);
}
