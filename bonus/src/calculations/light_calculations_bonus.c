/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calculations_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:48:50 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/22 16:35:32 by gpasquet         ###   ########.fr       */
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

int	light_intersect(t_obj_list **obj_ptr, t_light *light, t_normal normal,
		t_vector ray)
{
	t_obj_list	*cursor;
	double		distance;
	double		light_source_d;

	light_source_d = get_light_distance(light, normal);
	cursor = *obj_ptr;
	distance = INFINITY;
	while (cursor)
	{
		if (cursor->hitted == 0)
			distance = get_shadow_distance(cursor, normal, light->direction);
		if (cursor->hitted == 1)
			if (wich_side(ray, light->direction, normal) == 0)
				return (1);
		if (distance > 0 && distance < light_source_d)
			return (1);
		cursor = cursor->next;
	}
	return (0);
}

t_vector	get_light_dir(t_vector *light_o, t_normal normal)
{
	double		light_dir_len;
	t_vector	light_dir;

	light_dir.x = light_o->x - normal.origin.x;
	light_dir.y = light_o->y - normal.origin.y;
	light_dir.z = light_o->z - normal.origin.z;
	light_dir_len = sqrt(dot_product(light_dir, light_dir));
	light_dir.x /= light_dir_len;
	light_dir.y /= light_dir_len;
	light_dir.z /= light_dir_len;
	return (light_dir);
}
