/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:35:45 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/12 13:21:28 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	free_cylinder(t_cylinder **cylinder)
{
	if (!cylinder || !*cylinder)
		return ;
	if ((*cylinder)->vector)
		free((*cylinder)->vector);
	free(*cylinder);
	*cylinder = NULL;
	return ;
}

// static double	*hit_body(t_cylinder *cylinder, t_vector ray)
// {
// 	t_vector	oc;
// 	t_vector	tmp1;
// 	t_vector	tmp2;
// 	double		a;
// 	double		b;
// 	double		c;

// 	oc.x_o = 0;
// 	oc.y_o = 0;
// 	oc.z_o = 0;
// 	oc.x_d = -cylinder->vector->x_o;
// 	oc.y_d = -cylinder->vector->y_o;
// 	oc.z_d = -cylinder->vector->z_o;
// 	tmp1 = vector_cross(ray, *cylinder->vector);
// 	a = dot_product(tmp1, tmp1);
// 	tmp2 = vector_cross(oc, *cylinder->vector);
// 	b = 2 * dot_product(tmp1, tmp2);
// 	c = dot_product(tmp1, tmp2) - pow((cylinder->diameter / 2), 2);
// 	return (cyl_quadratic(a, b, c));
// }

// static double	*caps_hit(t_cylinder *cylinder, t_vector ray)
// {
// 	t_vector	mid_vect;
// 	t_vector	mid_point;
// 	double		tmp1;
// 	double		tmp2;
// 	double		*t;

// 	t = malloc(sizeof(double) * 2);
// 	if (!t)
// 	{
// 		ft_error("ERROR\n");
// 		return (NULL);
// 	}
// 	mid_vect = scalar_multiplication(cylinder->vector, (cylinder->height / 2));
// 	mid_point.x_o = cylinder->vector->x_o + mid_vect.x_o - ray.x_o;
// 	mid_point.y_o = cylinder->vector->y_o + mid_vect.y_o - ray.y_o;
// 	mid_point.z_o = cylinder->vector->z_o + mid_vect.z_o - ray.z_o;
// 	mid_point.x_d = cylinder->vector->x_d + mid_vect.x_d;
// 	mid_point.y_d = cylinder->vector->y_d + mid_vect.y_d;
// 	mid_point.z_d = cylinder->vector->z_d + mid_vect.z_d;
// 	tmp1 = dot_product(mid_point, *cylinder->vector);
// 	tmp2 = dot_product(ray, *cylinder->vector);
// 	t[0] = (tmp1 + (cylinder->height / 2)) / tmp2;
// 	t[1] = (tmp1 - (cylinder->height / 2)) / tmp2;
// 	return (t);
// }

// double	cylinder_hit(t_cylinder *cylinder, t_vector ray)
// {
// 	double	*t1;
// 	double	*t2;
// 	double	t_final;

// 	t1 = hit_body(cylinder, ray);
// 	t2 = caps_hit(cylinder, ray);
// 	if (!t1 || !t2)
// 		return (INFINITY);
// 	if (t1[0] > t1[1])
// 		ft_swap(t1);
// 	if (t2[0] > t2[1])
// 		ft_swap(t2);
// 	if (t2[0] > t1[1] || t2[1] < t1[0])
// 		return (INFINITY);
// 	t_final = fmax(t1[0], t2[0]);
// 	if (t_final < 0)
// 		t_final = fmin(t1[1], t2[1]);
// 	free(t1);
// 	free(t2);
// 	if (t_final <= 0)
// 		return (INFINITY);
// 	return (t_final);
// }

t_vector transform_ray(t_vector ray, t_cylinder *cylinder)
{
	double alpha;
	double beta;

	alpha = atan2(cylinder->vector->x_d, cylinder->vector->y_d);
	beta = -atan2(cylinder->vector->z_d, cylinder->vector->y_d);

	ray.x_o = -cylinder->vector->x_o;
	ray.y_o = -cylinder->vector->y_o;
	ray.z_o = -cylinder->vector->z_o;
	double  tmp;

	tmp = ray.y_o;
	ray.y_o = ray.y_o * cos (beta) - ray.z_o * sin (beta);
	ray.z_o = ray.z_o * cos (beta) + tmp * sin (beta);
	tmp = ray.x_o;
	ray.x_o = ray.x_o * cos(alpha) - ray.y_o * sin(alpha);
	ray.y_o = ray.y_o * cos(alpha) + tmp * sin(alpha);
	
	tmp = ray.y_d;		
	ray.y_d = ray.y_d * cos (beta) - ray.z_d * sin (beta);
    ray.z_d = ray.z_d * cos (beta) + tmp * sin (beta);
    tmp = ray.x_d;
    ray.x_d = ray.x_d * cos(alpha) - ray.y_d * sin(alpha);
    ray.y_d = ray.y_d * cos(alpha) + tmp * sin(alpha);
	return (ray);
	
}
double	cylinder_hit(t_cylinder *cylinder, t_vector ray)
{
	double		a;
	double		b;
	double		c;
	double		*root;

	ray = transform_ray(ray, cylinder);
	a = ray.x_d * ray.x_d + ray.z_d * ray.z_d;
	b = 2 * (ray.x_o * ray.x_d + ray.z_o * ray.z_d);
	c = ray.x_o * ray.x_o + ray.z_o * ray.z_o - (cylinder->diameter / 2);
	root = cyl_quadratic(a, b, c);
	if (!root)
		return (INFINITY);


	if (root[0] > 0 && root[0] < root[1] && ray.y_o + root[0] * ray.y_d > -cylinder->height / 2 && ray.y_o + root[0] * ray.y_d < cylinder->height / 2)
		return (root[0]);
	else if (root[1] > 0 && ray.y_o + root[1] * ray.y_d > -cylinder->height / 2 && ray.y_o + root[1] * ray.y_d < cylinder->height / 2)
		return (root[1]);


	// if (root[0] > root[1] && root[1] >= 0)
	// 	return (root[1]);
	// else if (root[1] >= root[0] && root[0] >= 0)
	// 	return (root[0]);
	// else if (root[0] > 0)
	// 	return (root[0]);
	// else if (root[1] > 0)
	// 	return (root[1]);
	return (INFINITY);
}
static int	check_cylinder(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 2;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (check_triple_float(str, &i) == 1)
		return (1);
	pass_to_next_element(str, &i);
	if (check_triple_float(str, &i) == 1)
		return (1);
	pass_to_next_element(str, &i);
	if (check_int(str, &i) == 1)
		return (1);
	pass_to_next_element(str, &i);
	if (check_int(str, &i) == 1)
		return (1);
	pass_to_next_element(str, &i);
	if (check_triple_int(str, &i) == 1)
		return (1);
	return (0);
}

static t_cylinder	*init_cylinder_part2(t_cylinder *cylinder, char *str, int i)
{
	int			*rgb;

	cylinder->diameter = ft_atof(str + i);
	pass_to_next_element(str, &i);
	cylinder->height = ft_atof(str + i);
	if (cylinder->height <= 0 || cylinder->diameter <= 0)
	{
		ft_error("Cylinder diameter and height must be superior to 0\n");
		free_cylinder(&cylinder);
		return (NULL);
	}
	pass_to_next_element(str, &i);
	rgb = get_color_values(str + i);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[2] < 0
		|| rgb[2] > 255)
	{
		free(rgb);
		free_cylinder(&cylinder);
		return (NULL);
	}
	cylinder->color = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	free(rgb);
	return (cylinder);
}

t_cylinder	*init_cylinder(char *str)
{
	t_cylinder	*cylinder;
	int			i;

	if (!str || check_cylinder(str) == 1)
		return (NULL);
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	i = 2;
	while (ft_isspace(str[i]))
		i++;
	cylinder->vector = init_vector(str + i);
	if (!cylinder->vector)
	{
		free_cylinder(&cylinder);
		return (NULL);
	}
	pass_to_next_element(str, &i);
	pass_to_next_element(str, &i);
	cylinder = init_cylinder_part2(cylinder, str, i);
	return (cylinder);
}
