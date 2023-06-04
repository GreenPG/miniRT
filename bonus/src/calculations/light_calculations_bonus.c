/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calculations_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:48:50 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/04 16:15:04 by gpasquet         ###   ########.fr       */
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

static int	light_intersect(t_scene *scene, t_vector light_dir, t_normal normal,
		t_vector ray)
{
	t_obj_list	*cursor;
	double		distance;
	double		light_source_d;

	light_source_d = get_light_distance(scene->light_list->light, normal);
	cursor = scene->obj_list;
	distance = 0;
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

static t_vector	get_light_dir(t_light *light, t_normal normal)
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

int	get_specular_ratio(t_light *light, t_vector ray, t_vector light_dir, t_vector normal)
{
	double			n_l_dot_product;
	t_vector		reflection_vector;
 	int				r;
	int				g;
	int				b;

	n_l_dot_product = dot_product(normal, light_dir);
	reflection_vector.x = light_dir.x - 2 * n_l_dot_product * normal.x;
	reflection_vector.y = light_dir.y - 2 * n_l_dot_product * normal.y;
	reflection_vector.z = light_dir.z - 2 * n_l_dot_product * normal.z;
	r = pow(dot_product(ray, reflection_vector) * get_r(light->colors) * light->brightness, 1);
	g = pow(dot_product(ray, reflection_vector) * get_g(light->colors) * light->brightness, 1);
	b = pow(dot_product(ray, reflection_vector) * get_b(light->colors) * light->brightness, 1);
	return (get_rgba(r, g, b, 255));
}

static int	get_diffuse_ratio(t_light *light, t_normal normal, t_vector light_dir)
{
	double			diffuse_ratio;
	int				r;
	int				g;
	int				b;

	diffuse_ratio = fabs(dot_product(normal.dir, light_dir));
	diffuse_ratio = fmax(0.0, diffuse_ratio);
	diffuse_ratio *= light->brightness;
	r = get_r(light->colors) * diffuse_ratio;
	g = get_g(light->colors) * diffuse_ratio;
	b = get_b(light->colors) * diffuse_ratio;
	return (get_rgba(r, g, b, 255));
}

int	get_shading_color(t_scene *scene, t_normal normal, t_vector ray)
{
	t_vector		light_dir;
	t_light_list	*light_list;
	int				light_cnt;
	double			diffuse_ratio;
	double			specular_ratio;
	int				r;
	int				g;
	int				b;

	r = 0;
	g = 0;
	b = 0;
	light_cnt = 0;
	light_list = scene->light_list;
	while (light_list)
	{
		light_dir = get_light_dir(light_list->light, normal);
		if (light_intersect(scene, light_dir, normal, ray) == 0)
		{
			diffuse_ratio = get_diffuse_ratio(light_list->light, normal, light_dir);
			specular_ratio = get_specular_ratio(light_list->light, ray, invert_vector(light_dir), invert_vector(normal.dir));
			r += get_r(diffuse_ratio) + get_r(specular_ratio);
			g += get_g(diffuse_ratio) + get_g(specular_ratio);
			b += get_b(diffuse_ratio) + get_b(specular_ratio);
		}
		light_list = light_list->next;
		light_cnt++;
	}
	r /= light_cnt;
	g /= light_cnt;
	b /= light_cnt;
	return (get_rgba(r, g, b, 255));
}
