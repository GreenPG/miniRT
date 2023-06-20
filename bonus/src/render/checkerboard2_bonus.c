/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:16:21 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/20 16:16:55 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

int	checkerboard_triangle(t_vector vec, t_triangle *triangle)
{
	vec.x -= triangle->a->x;
	vec.y -= triangle->a->y;
	vec.z -= triangle->a->z;
	vec = camera_to_object_space(vec, *triangle->normal, *triangle->up);
	if ((int)(floor(vec.x) + floor(vec.z)) % 2 == 0)
		return (get_rgba(255, 255, 255, 0));
	return (0);
}
