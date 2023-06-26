/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinate_frame_transform_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 09:37:46 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/23 09:14:12 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_vector	camera_to_object_space(	t_vector vec,
									t_vector obj_dir,
									t_vector obj_up)
{
	t_cyl_calc	data;

	obj_up = camera_to_object_space_sym(obj_up, obj_dir);
	vec = camera_to_object_space_sym(vec, obj_dir);
	data.front.x = 0;
	data.front.y = 0;
	data.front.z = 1;
	if (is_aligned(data.front, obj_up))
		return (vec);
	if (dot_product(obj_up, data.front) > -1 + 1e-6)
	{
		data.cross = vector_cross(obj_up, data.front);
		data.cross = vector_norm(data.cross);
		data.angle = acos(fmin(dot_product(obj_up, data.front)
					/ (sqrt(dot_product(obj_up, obj_up))
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

int	is_rcolinear(t_vector u, t_vector v)
{
	u.x += v.x;
	u.y += v.y;
	u.z += v.z;
	if (fabs(u.x) <= 1e-6 && fabs(u.y) <= 1e-6 && fabs(u.z) <= 1e-6)
		return (1);
	return (0);
}

t_vector	camera_to_object_space_sym(t_vector vec, t_vector obj_dir)
{
	t_cyl_calc	data;

	data.front.x = 0;
	data.front.y = 1;
	data.front.z = 0;
	if (is_aligned(data.front, obj_dir))
		return (vec);
	if (is_rcolinear(data.front, obj_dir))
	{
		vector_rot_x(&vec, M_PI);
		return (vec);
	}
	data.cross = vector_cross(obj_dir, data.front);
	data.cross = vector_norm(data.cross);
	data.angle = acos(fmin(dot_product(obj_dir, data.front)
				/ (sqrt(dot_product(obj_dir, obj_dir)))
				* sqrt(dot_product (data.front, data.front)), 1.));
	rotate_around_axis(&vec, data.cross, -data.angle);
	return (vec);
}
