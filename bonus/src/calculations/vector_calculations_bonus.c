/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calculations_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:22:48 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/20 10:33:11 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_vector	vector_norm(t_vector vec)
{
	double	len;

	len = sqrt(dot_product(vec, vec));
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
	return (vec);
}

t_vector	invert_vector(t_vector u)
{
	u.x = -u.x;
	u.y = -u.y;
	u.z = -u.z;
	return (u);
}

t_vector	vector_cross(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = (a.y * b.z) - (a.z * b.y);
	result.y = (a.x * b.z) - (a.z * b.x);
	result.z = (a.x * b.y) - (a.y * b.x);
	return (result);
}

double	dot_product(t_vector v, t_vector u)
{
	return (v.x * u.x + v.y * u.y + v.z * u.z);
}
