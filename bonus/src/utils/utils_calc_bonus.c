/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:41:32 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/16 16:41:58 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	get_angle(t_cyl_calc data, t_ellipsoid *ellipsoid, int dir)
{
	if (dir == 0)
	{
		data.front.x = 0.0000001;
		data.front.y = 1;
		data.front.z = 0.0000001;
	}
	else
	{
		data.front.x = 0.0000001;
		data.front.y = 0.0000001;
		data.front.z = 1;
	}
	data.cross = vector_cross(*ellipsoid->direction, data.front);
	data.cross = vector_norm(data.cross);
	data.angle = acos(dot_product(*ellipsoid->direction, data.front)
			/ (sqrt(dot_product(*ellipsoid->direction, *ellipsoid->direction))
				* sqrt(dot_product (data.front, data.front))));
}
