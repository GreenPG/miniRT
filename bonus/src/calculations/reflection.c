/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:30:12 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/04 11:44:45 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

int	get_specular_ratio(t_scene *scene, )
{
	double			specular_ratio;
	t_vector		light_dir;
	t_vector		reflection_vector;
	t_light_list	*light_list;
	int				r;
	int				g;
	int				b;

	light_list = scene->light_list;
	r = 0;
	g = 0;
	b = 0;
	while (light_list)
	{
		light_dir = get_light_dir(light_list->light, normal);
	}
}
