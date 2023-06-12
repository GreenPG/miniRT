/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_calculations_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:43:10 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/09 17:21:42 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

double	*caps_hit(t_vector ray, t_vector rayo, t_cylinder *cylinder)
{
	double	*r;

	r = malloc(sizeof(double) * 2);
	if (!r)
	{
		ft_error("Error\n");
		return (NULL);
	}
	r[0] = INFINITY;
	r[1] = INFINITY;
	r[0] = (-cylinder->height / 2 - rayo.y) / ray.y;
	if ((rayo.x + r[0] * ray.x) * (rayo.x + r[0] * ray.x)
		+ (rayo.z + r[0] * ray.z) * (rayo.z + r[0] * ray.z)
		> (cylinder->diameter / 2) * (cylinder->diameter / 2))
		r[0] = INFINITY;
	r[1] = (cylinder->height / 2 - rayo.y) / ray.y;
	if ((rayo.x + r[1] * ray.x) * (rayo.x + r[1] * ray.x)
		+ (rayo.z + r[1] * ray.z) * (rayo.z + r[1] * ray.z)
		> (cylinder->diameter / 2) * (cylinder->diameter / 2))
		r[1] = INFINITY;
	return (r);
}

double	*body_hit(t_vector ray, t_vector rayo,
		t_cylinder *cylinder)
{
	double	a;
	double	b;
	double	c;

	a = ray.x * ray.x + ray.z * ray.z;
	b = (rayo.x * ray.x + rayo.z * ray.z);
	c = rayo.x * rayo.x + rayo.z * rayo.z
		- (cylinder->diameter / 2) * (cylinder->diameter / 2);
	return (cyl_quadratic(a, b, c));
}

void	free_cyl_roots(double *root, double *caps)
{
	if (root)
		free(root);
	if (caps)
		free(caps);
}

double	*between_caps(double *root, t_vector rayo,
		t_vector ray, t_cylinder *cylinder)
{
	if (!(root[0] > 0 && rayo.y + root[0] * ray.y
			> -cylinder->height / 2 && rayo.y + root[0] * ray.y
			< cylinder->height / 2))
		root[0] = INFINITY;
	if (!(root[1] > 0 && rayo.y + root[1] * ray.y
			> -cylinder->height / 2 && rayo.y + root[1] * ray.y
			< cylinder->height / 2))
		root[1] = INFINITY;
	return (root);
}

static double	cylinder_distance(t_cylinder *cylinder, t_vector ray,
	t_cyl_calc	data)
{
	double		*root;
	double		*caps;
	double		distance;

	root = body_hit(ray, data.rayo, cylinder);
	caps = caps_hit(ray, data.rayo, cylinder);
	if (!root || !caps)
	{
		free_cyl_roots(root, caps);
		return (INFINITY);
	}
	root = between_caps(root, data.rayo, ray, cylinder);
	if (min_cyl(root[0], root[1], caps[0], caps[1]) != INFINITY
		&& (min_cyl(root[0], root[1], caps[0], caps[1]) == root[0]
			|| min_cyl(root[0], root[1], caps[0], caps[1]) == root[1]))
		cylinder->hit_body = true;
	distance = min_cyl(root[0], root[1], caps[0], caps[1]);
	free_cyl_roots(root, caps);
	return (distance);
}

double	cylinder_hit(t_cylinder *cylinder, t_vector ray)
{
	t_cyl_calc	data;

	data.front.x = 0;
	data.front.y = 1;
	data.front.z = 0;
	data.cross = vector_cross(*cylinder->direction, data.front);
	vector_norm(&data.cross);
	data.angle = acos(dot_product(*cylinder->direction, data.front)
			/ (sqrt(dot_product(*cylinder->direction, *cylinder->direction))
				* sqrt(dot_product (data.front, data.front))));
	rotate_around_axis(&ray, data.cross, -data.angle);
	data.rayo.x = -cylinder->origin->x;
	data.rayo.y = -cylinder->origin->y;
	data.rayo.z = -cylinder->origin->z;
	rotate_around_axis(&data.rayo, data.cross, -data.angle);
	return (cylinder_distance(cylinder, ray, data));
}
