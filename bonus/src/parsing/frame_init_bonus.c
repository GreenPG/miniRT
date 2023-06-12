/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:12:28 by gtouzali          #+#    #+#             */
/*   Updated: 2023/06/12 10:14:40 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_frame	*frame_init(void)
{
	t_frame	*frame;

	frame = malloc(sizeof(t_frame));
	if (!frame)
		return (NULL);
	frame->i.x = 1;
	frame->i.y = 0;
	frame->i.z = 0;
	frame->j.x = 0;
	frame->j.y = 1;
	frame->j.z = 0;
	frame->k.x = 0;
	frame->k.y = 0;
	frame->k.z = 1;
	return (frame);
}