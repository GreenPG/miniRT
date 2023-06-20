/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinate_frame_transform_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 09:37:46 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/20 10:35:30 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_vector	camera_to_object_space(	t_vector vec,
									t_vector obj_dir,
									t_vector obj_up)
{
	t_vector	tmp;
	t_cyl_calc	data;

	tmp.x = obj_up.x;
	tmp.y = obj_up.y;
	tmp.z = obj_up.z;
	data.front.x = 1e-6;
	data.front.y = 1;
	data.front.z = 1e-6;
	data.cross = vector_cross(obj_dir, data.front);
	data.cross = vector_norm(data.cross);
	data.angle = acos(dot_product(obj_dir, data.front)
			/ (sqrt(dot_product(obj_dir, obj_dir))
				* sqrt(dot_product (data.front, data.front))));
	rotate_around_axis(&vec, data.cross, -data.angle);
	rotate_around_axis(&tmp, data.cross, -data.angle);
	data.front.x = 0;
	data.front.y = 0;
	data.front.z = 1;
	if (dot_product(tmp, data.front) > -1 + 1e-6)
	{
		data.cross = vector_cross(tmp, data.front);
		data.cross = vector_norm(data.cross);
		data.angle = acos(fmin(dot_product(tmp, data.front)
					/ (sqrt(dot_product(tmp, tmp))
						* sqrt(dot_product (data.front, data.front))), 1.0));
		rotate_around_axis(&vec, data.cross, data.angle);
	}
	else
	{
		vec.x = -vec.x;
		vec.z = -vec.z;
	}
	return (vec);
}

t_vector	camera_to_object_space_sym(t_vector vec, t_vector obj_dir)
{
	t_cyl_calc	data;

	data.front.x = 1e-6;
	data.front.y = 1;
	data.front.z = 1e-6;
	data.cross = vector_cross(obj_dir, data.front);
	data.cross = vector_norm(data.cross);
	data.angle = acos(dot_product(obj_dir, data.front)
			/ (sqrt(dot_product(obj_dir, obj_dir))
				* sqrt(dot_product (data.front, data.front))));
	rotate_around_axis(&vec, data.cross, -data.angle);
	return (vec);
}
