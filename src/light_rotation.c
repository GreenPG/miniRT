/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:31:33 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/17 15:31:56 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	light_rot_y(t_light *light, double angle)
{
	vector_rot_y(light->origin, angle);
}

void	light_rot_x(t_light *light, double angle)
{
	vector_rot_x(light->origin, angle);
}
