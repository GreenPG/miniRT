/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse_light_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:35:10 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/22 16:36:49 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static double	get_diffuse_ratio(t_normal normal, t_light *light)
{
	double	diffuse_ratio;

	diffuse_ratio = fabs(dot_product(normal.dir, light->direction));
	diffuse_ratio = fmax(0.0, diffuse_ratio);
	diffuse_ratio *= light->brightness;
	return (diffuse_ratio);
}

int	get_diffuse_color(t_scene *scene, t_vector ray, t_normal normal,
		t_obj_list *nearest)
{
	int				*rgb;
	t_light_list	*light_list;
	double			diffuse_ratio;

	rgb = NULL;
	rgb = init_rgb_tab();
	if (!rgb)
		return (0);
	light_list = scene->light_list;
	while (light_list)
	{
		light_list->light->direction = get_light_dir(light_list->light->origin,
				normal);
		if (light_intersect(&scene->obj_list, light_list->light, normal,
				ray) == 0)
		{
			diffuse_ratio = get_diffuse_ratio(normal, light_list->light);
			increment_color(rgb, light_list->light->colors, diffuse_ratio,
				1 - nearest->ks);
		}
		light_list = light_list->next;
	}
	return (clamp_rgb(rgb));
}
