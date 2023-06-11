/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: gtouzali <gtouzali@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/04/17 17:10:29 by gpasquet		  #+#	#+#			 */
/*   Updated: 2023/06/02 14:17:58 by gpasquet         ###   ########.fr       */
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

static int	get_final_color(int color, int diffuse_color, t_scene *scene)
{
	int	r;
	int	g;
	int	b;

	r = get_r(color) * (scene->ambiant_l->light_ratio
			* get_r(scene->ambiant_l->colors) + get_r(diffuse_color)) / 255;
	if (r > 255)
		r = 255;
	g = get_g(color) * (scene->ambiant_l->light_ratio
			* get_g(scene->ambiant_l->colors) + get_g(diffuse_color)) / 255;
	if (g > 255)
		g = 255;
	b = get_b(color) * (scene->ambiant_l->light_ratio
			* get_b(scene->ambiant_l->colors) + get_b(diffuse_color)) / 255;
	if (b > 255)
		b = 255;
	return (get_rgba(r, g, b, 255));
}

t_vector	ray_to_world(t_vector *base, t_vector ray)
{
	t_vector world_ray;

	world_ray.x = base[0].x * ray.x + base[1].x * ray.y + base[2].x * ray.z;
	world_ray.y = base[0].y * ray.x + base[1].y * ray.y + base[2].y * ray.z;
	world_ray.z = base[0].z * ray.x + base[1].z * ray.y + base[2].z * ray.z;
	vector_norm(&world_ray);
	return(world_ray);
}

static int	sky_color(t_scene *scene, t_vector ray)
{
	double	t;

	ray = ray_to_world(scene->world_base, ray);
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
	int			color;
	t_normal	normal;

	if (nearest)
	{
		normal = get_normal(nearest, ray, distance);
		color = get_normal_color(nearest, ray, normal, scene->camera);
		diffuse_color = get_diffuse_ratio(scene, normal, ray);
		color = get_final_color(color, diffuse_color, scene);
		nearest->hitted = 0;
		return (color);
	}
	return (sky_color(scene, ray));
}
