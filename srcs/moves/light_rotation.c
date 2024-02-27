/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_rotation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:31:33 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/09 18:05:15 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	light_rot_y(t_light_list *light_list, double angle)
{
	t_light_list	*tmp;

	tmp = light_list;
	while (tmp)
	{
		vector_rot_y(tmp->light->origin, angle);
		tmp = tmp->next;
	}
}

void	light_rot_x(t_light_list *light_list, double angle)
{
	t_light_list	*tmp;

	tmp = light_list;
	while (tmp)
	{
		vector_rot_x(tmp->light->origin, angle);
		tmp = tmp->next;
	}
}

void	light_rot_z(t_light_list *light_list, double angle)
{
	t_light_list	*tmp;

	tmp = light_list;
	while (tmp)
	{
		vector_rot_z(tmp->light->origin, angle);
		tmp = tmp->next;
	}
}
