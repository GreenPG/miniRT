/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid_shadow_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:45:41 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/16 16:45:59 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

double	ellipsoid_shadow(t_ellipsoid *ellipsoid, t_normal normal,
		t_vector ray)
{
	double		distance;
	t_cyl_calc	data;

	data.rayo.x = normal.origin.x - ellipsoid->origin->x;
	data.rayo.y = normal.origin.y - ellipsoid->origin->y;
	data.rayo.z = normal.origin.z - ellipsoid->origin->z;
	distance = ellipsoid_distance(ellipsoid, data, ray);
	return (distance);
}
