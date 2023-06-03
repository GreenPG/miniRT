/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_functions_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:12:19 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/02 15:00:09 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

double	plane_hit(t_plane *obj, t_vector ray)
{
	double	is_hitted;
	double	t;

	is_hitted = dot_product(*obj->direction, ray);
	if (is_hitted > 1e-6 || is_hitted < 1e-6)
	{
		t = dot_product(*obj->origin, *obj->direction);
		t = t / is_hitted;
		if (t >= 0)
			return (t);
		else
			return (INFINITY);
	}
	return (INFINITY);
}
