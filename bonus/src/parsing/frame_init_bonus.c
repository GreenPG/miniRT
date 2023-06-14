/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:12:28 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/13 09:22:25 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_frame	*frame_init(t_vector *dir)
{
	t_frame		*frame;
	t_vector	front;
	double		angle;

	frame = malloc(sizeof(t_frame));
	if (!frame)
		return (NULL);
	t_vector	cross;
	front.x = 0;
	front.y = 1;
	front.z = 0;
	cross = vector_cross(*dir, front);
	vector_norm(&cross);

		angle = acos(dot_product(*dir, front)
			/ (sqrt(dot_product(*dir, *dir))
				* sqrt(dot_product (front, front))));
	frame->i.x = 1;
	frame->i.y = 0;
	frame->i.z = 0;
	rotate_around_axis(&frame->i, cross, angle);
	frame->j.x = 0;
	frame->j.y = 1;
	frame->j.z = 0;
	rotate_around_axis(&frame->j, cross, angle);
	frame->k.x = 0;
	frame->k.y = 0;
	frame->k.z = 1;
	rotate_around_axis(&frame->k, cross, angle);
	return (frame);
}