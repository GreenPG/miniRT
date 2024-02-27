/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:26:56 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/22 16:38:31 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static double	get_specular_ratio(t_vector reflection, t_vector ray,
	t_obj_list *nearest, t_light *light)
{
	double				ray_reflect_dot_product;
	double				specular_ratio;

	ray = invert_vector(ray);
	ray = vector_norm(ray);
	ray_reflect_dot_product = fmax(0.0, dot_product(ray, reflection));
	specular_ratio = fmax(0.0, pow(ray_reflect_dot_product,
				nearest->sp_e) * light->brightness);
	return (specular_ratio);
}

static t_vector	get_reflect_vector(t_normal normal, t_vector light_dir)
{
	t_vector			reflection;

	reflection.x = 2 * dot_product(normal.dir, light_dir) * normal.dir.x
		- light_dir.x;
	reflection.y = 2 * dot_product(normal.dir, light_dir) * normal.dir.y
		- light_dir.y;
	reflection.z = 2 * dot_product(normal.dir, light_dir) * normal.dir.z
		- light_dir.z;
	return (reflection);
}

int	get_specular_color(t_scene *scene, t_vector ray, t_normal normal,
		t_obj_list *nearest)
{
	t_vector			reflect;
	t_light_list		*light_list;
	double				specular_ratio;
	int					*rgb;

	rgb = init_rgb_tab();
	if (!rgb)
		return (0);
	light_list = scene->light_list;
	while (light_list)
	{
		light_list->light->direction = get_light_dir(light_list->light->origin,
				normal);
		if (light_intersect(&scene->obj_list, light_list->light, normal, ray)
			== 0)
		{
			reflect = get_reflect_vector(normal, light_list->light->direction);
			specular_ratio = get_specular_ratio(reflect, ray, nearest,
					light_list->light);
			increment_color(rgb, light_list->light->colors, specular_ratio,
				nearest->ks);
		}
		light_list = light_list->next;
	}
	return (clamp_rgb(rgb));
}
