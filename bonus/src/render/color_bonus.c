/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: gtouzali <gtouzali@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/04/17 17:10:29 by gpasquet		  #+#	#+#			 */
/*   Updated: 2023/06/15 15:04:42 by gpasquet         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minirt_bonus.h>

int	add_ambient(int color, t_ambiant_l *ambiant)
{
	int	r;
	int	g;
	int	b;

	r = (get_r(color) * get_r(ambiant->colors) / 255) * ambiant->light_ratio;
	g = (get_g(color) * get_g(ambiant->colors) / 255) * ambiant->light_ratio;
	b = (get_b(color) * get_b(ambiant->colors) / 255) * ambiant->light_ratio;
	return (get_rgba(r, g, b, 255));
}

static int	get_final_color(int color, int diffuse_color, int specular_color,
		t_scene *scene)
{
	int	r;
	int	g;
	int	b;

	r = get_r(color) * (scene->ambiant_l->light_ratio
			* get_r(scene->ambiant_l->colors) / 255)
		+ ((float)get_r(diffuse_color) / 255) * get_r(color)
		+ get_r(specular_color);
	if (r > 255)
		r = 255;
	g = get_g(color) * (scene->ambiant_l->light_ratio
			* get_g(scene->ambiant_l->colors) / 255)
		+ ((float)get_g(diffuse_color) / 255) * get_g(color)
		+ get_g(specular_color);
	if (g > 255)
		g = 255;
	b = get_b(color) * (scene->ambiant_l->light_ratio
			* get_b(scene->ambiant_l->colors) / 255)
		+ ((float)get_b(diffuse_color) / 255) * get_b(color)
		+ get_b(specular_color);
	if (b > 255)
		b = 255;
	return (get_rgba(r, g, b, 255));
}

static int	sky_color(t_scene *scene, t_vector ray)
{
	double	t;

	t_vector	tmp;

	tmp.x = scene->up->x;
	tmp.y = scene->up->y;
	tmp.z = scene->up->z;
	t_cyl_calc	data;

	data.front.x = 0.0000001;
	data.front.y = 1;
	data.front.z = 0.0000001;
	data.cross = vector_cross(*scene->direction, data.front);
	vector_norm(&data.cross);
	data.angle = acos(dot_product(*scene->direction, data.front)
			/ (sqrt(dot_product(*scene->direction, *scene->direction))
				* sqrt(dot_product (data.front, data.front))));
	rotate_around_axis(&ray, data.cross, -data.angle);
	rotate_around_axis(&tmp, data.cross, -data.angle);
	data.front.x = 0.0000001;
	data.front.y = 0.0000001;
	data.front.z = 1;
	data.cross = vector_cross(tmp, data.front);
	vector_norm(&data.cross);
	data.angle = acos(dot_product(tmp, data.front)
			/ (sqrt(dot_product(tmp, tmp))
				* sqrt(dot_product (data.front, data.front))));
	rotate_around_axis(&ray, data.cross, data.angle);
	t = sin(ray.z);
	if (t > 0)
		return (get_rgba(scene->ambiant_l->light_ratio * (255 * (1 - t) + t
					* 156), scene->ambiant_l->light_ratio * (255 * (1 - t) + t
					* 156), scene->ambiant_l->light_ratio * (255 * (1 - t) + t
					* 245), 255));
	t = -t;
	return (get_rgba(scene->ambiant_l->light_ratio * (255 * (1 - t) + t * 231),
			scene->ambiant_l->light_ratio * (255 * (1 - t) + t * 109),
			scene->ambiant_l->light_ratio * (255 * (1 - t) + t * 245), 255));
}

int	get_obj_color(t_obj_list *nearest, t_vector ray, t_scene *scene,
		double distance)
{
	int			diffuse_color;
	int			specular_color;
	int			color;
	t_normal	normal;

	if (nearest)
	{
		normal = get_normal(nearest, ray, distance);
		color = get_normal_color(nearest, ray, normal);
		diffuse_color = get_diffuse_color(scene, ray, normal, nearest);
		if (nearest->sp_e == 0)
			specular_color = 0;
		else
			specular_color = get_specular_color(scene, ray, normal, nearest);
		color = get_final_color(color, diffuse_color, specular_color, scene);
		nearest->hitted = 0;
		return (color);
	}
	return (sky_color(scene, ray));
}
