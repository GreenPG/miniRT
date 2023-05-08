/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:35:45 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/08 14:24:01 by gpasquet         ###   ########.fr       */
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

static double	*hit_body(t_cylinder *cylinder, t_vector ray)
{
	t_vector	tmp1;
	t_vector	tmp2;
	double		a;
	double		b;
	double		c;

	tmp1 = vector_cross(ray, *cylinder->vector);
	a = dot_product(tmp1, tmp1);
	tmp2 = vector_cross(vector_origin_addition(ray, *cylinder->vector, -1), *cylinder->vector);
	b = 2.0 * dot_product(tmp1, tmp2);
	c = dot_product(tmp2, tmp2) - pow((cylinder->diameter / 2.0), 2);
	return (cyl_quadratic(a, b, c));
}
/*
static t_vector	get_mid_point(t_vector cylinder_vect, t_vector mid_vect)
{
	t_vector	mid_point;

	mid_point.x_o = 0;
	mid_point.y_o = 0;
	mid_point.x_o = 0;
	mid_point.x_d = cylinder_vect.x_o + mid_vect.x_d;
	mid_point.y_d = cylinder_vect.y_o + mid_vect.y_d;
	mid_point.z_d = cylinder_vect.z_o + mid_vect.z_d;
	return (mid_point);
}

static double	*caps_hit(t_cylinder *cylinder, t_vector ray)
{
	t_vector	mid_vect;
	t_vector	mid_point;
	double		tmp1;	
	double		tmp2;	
	double		*r;

	r = malloc(sizeof(double) * 2);
	if (!r)
		return (NULL);
	mid_vect = scalar_multiplication(cylinder->vector, (cylinder->height / 2));
	mid_point = get_mid_point(*cylinder->vector, mid_vect);
	tmp1 = dot_product(mid_point, *cylinder->vector);
	tmp2 = dot_product(ray, *cylinder->vector);
	r[0] = (tmp1 + (cylinder->height / 2)) / tmp2;
	r[1] = (tmp1 - (cylinder->height / 2)) / tmp2;
	return (r);
}
*/
double	cylinder_hit(t_cylinder *cylinder, t_vector ray)
{
	double	*t1;
	//double	*t2;
//	double	intersection;

	t1 = hit_body(cylinder, ray);
	/*t2 = caps_hit(cylinder, ray);
	if (t1[0] > t1[1])
		ft_swap(t1);
	if (t2[0] > t2[1])
		ft_swap(t2);
	if (t2[0] > t1[1] || t2[1] < t1[0])
		return (INFINITY);
	intersection = fmax(t1[0], t2[0]);
	if (intersection < 0)
		intersection = fmin(t1[1], t2[1]);
	if (intersection <= 0)
		return (INFINITY);
	return (intersection);*/
	if (t1[0] > 0 && (t1[1] < 0 || t1[0] < t1[1]))
		return (t1[0]);
	if (t1[1] > 0)
		return (t1[1]);
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
