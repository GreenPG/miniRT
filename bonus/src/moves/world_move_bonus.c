/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_move_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:54:16 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/10 15:41:44 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	world_rot_x(t_vector *world_base, double angle)
{
	vector_rot_x(&world_base[0], angle);
	vector_rot_x(&world_base[1], angle);
	vector_rot_x(&world_base[2], angle);
	vector_norm(&world_base[0]);
	vector_norm(&world_base[1]);
	vector_norm(&world_base[2]);
}

void	world_rot_y(t_vector *world_base, double angle)
{
	vector_rot_y(&world_base[0], angle);
	vector_rot_y(&world_base[1], angle);
	vector_rot_y(&world_base[2], angle);
	vector_norm(&world_base[0]);
	vector_norm(&world_base[1]);
	vector_norm(&world_base[2]);
}

void	world_rot_z(t_vector *world_base, double angle)
{
	vector_rot_z(&world_base[0], angle);
	vector_rot_z(&world_base[1], angle);
	vector_rot_z(&world_base[2], angle);
	vector_norm(&world_base[0]);
	vector_norm(&world_base[1]);
	vector_norm(&world_base[2]);
}