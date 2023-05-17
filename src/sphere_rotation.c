/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:29:26 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/17 15:29:51 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	sphere_rot_x(t_sphere *sphere, double angle)
{
	vector_rot_x(sphere->origin, angle);
}

void	sphere_rot_y(t_sphere *sphere, double angle)
{
	vector_rot_y(sphere->origin, angle);
}
