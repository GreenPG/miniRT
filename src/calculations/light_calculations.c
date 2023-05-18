/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calculations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:48:50 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/17 16:49:14 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

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

int	get_diffuse_ratio(t_light *light, t_normal normal)
{
	double		diffuse_ratio;
	t_vector	light_dir;
	int			r;
	int			g;
	int			b;

	light_dir = get_light_dir(light, normal);
	diffuse_ratio = dot_product(normal.dir, light_dir);
	diffuse_ratio = fmax(0.0, diffuse_ratio);
	diffuse_ratio *= light->brightness;
	r = get_r(light->colors) * diffuse_ratio;
	g = get_g(light->colors) * diffuse_ratio;
	b = get_b(light->colors) * diffuse_ratio;
	return (get_rgba(r, g, b, 255));
}
