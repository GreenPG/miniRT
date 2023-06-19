/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calculations_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:48:50 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/16 15:36:27 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static double	get_light_distance(t_light *light, t_normal normal)
{
	double		light_distance;
	t_vector	hit_to_light;

	hit_to_light.x = light->origin->x - normal.origin.x;
	hit_to_light.y = light->origin->y - normal.origin.y;
	hit_to_light.z = light->origin->z - normal.origin.z;
	light_distance = sqrt(dot_product(hit_to_light, hit_to_light));
	return (light_distance);
}

static int	wich_side(t_vector ray, t_vector light_dir,	t_normal normal)
{
	double	a;
	double	b;

	light_dir.x *= -1;
	light_dir.y *= -1;
	light_dir.z *= -1;
	a = dot_product(normal.dir, ray);
	b = dot_product(normal.dir, light_dir);
	if ((a < 0 && b < 0) || (a > 0 && b > 0))
		return (1);
	return (0);
}

int	light_intersect(t_scene *scene, t_vector light_dir, t_normal normal,
		t_vector ray)
{
	t_obj_list	*cursor;
	double		distance;
	double		light_source_d;

	light_source_d = get_light_distance(scene->light_list->light, normal);
	cursor = scene->obj_list;
	distance = INFINITY;
	while (cursor)
	{
		if (cursor->hitted == 0)
			distance = get_shadow_distance(cursor, normal, light_dir);
		if (cursor->hitted == 1)
			if (wich_side(ray, light_dir, normal) == 0)
				return (1);
		if (distance > 0 && distance < light_source_d)
			return (1);
		cursor = cursor->next;
	}
	return (0);
}

t_vector	get_light_dir(t_light *light, t_normal normal)
{
	double		light_dir_len;
	t_vector	light_dir;

	light_dir.x = light->origin->x - normal.origin.x;
	light_dir.y = light->origin->y - normal.origin.y;
	light_dir.z = light->origin->z - normal.origin.z;
	light_dir_len = sqrt(dot_product(light_dir, light_dir));
	light_dir.x /= light_dir_len;
	light_dir.y /= light_dir_len;
	light_dir.z /= light_dir_len;
	return (light_dir);
}

int	get_diffuse_color(t_scene *scene, t_vector ray, t_normal normal,
		t_obj_list *nearest)
{
	t_vector		light_dir;
	int				*rgb;
	t_light_list	*light_list;
	double			diffuse_ratio;

	rgb = init_rgb_tab();
	if (!rgb)
		return (0);
	light_list = scene->light_list;
	while (light_list)
	{
		light_dir = get_light_dir(light_list->light, normal);
		if (light_intersect(scene, light_dir, normal, ray) == 0)
		{
			diffuse_ratio = fabs(dot_product(normal.dir, light_dir));
			diffuse_ratio = fmax(0.0, diffuse_ratio);
			diffuse_ratio *= light_list->light->brightness;
			increment_color(rgb, light_list->light->colors, diffuse_ratio,
				1 - nearest->ks);
		}
		light_list = light_list->next;
	}
	clamp_rgb(rgb);
	return (get_rgba(rgb[0], rgb[1], rgb[2], 255));
}
