/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:11:47 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/22 14:22:39 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

double	sphere_hit(void *sphere, t_vector ray)
{
	t_sphere *obj;
	t_vector oc;
	double a;
	double b;
	double c;
	double d;

	obj = (t_sphere *)sphere;
	oc.x_d = -obj->pos->x;
	oc.y_d = -obj->pos->y;
	oc.z_d = -obj->pos->z;
	oc.x_o = 0;
	oc.y_o = 0;
	oc.z_o = 0;
	d = 0;


    a = dot_product(ray, ray);
    b = 2.0 * dot_product(oc, ray);
    c = dot_product(oc, oc) - ((obj->diameter / 2) * (obj->diameter / 2));
    d = (b * b) - (4. * a * c);
    if (d > 0)
		return (obj->pos->y);
	return (INFINITY);
}

static int	check_sphere(char *input)
{
	int	i;

	if (!input)
		return (-1);
	i = 2;
	while (ft_isspace(input[i]) == 1)
		i++;
	if (check_triple_float(input, &i) == 1)
		return (1);
	while (ft_isspace(input[i]) == 1)
		i++;
	if (check_float(input, &i) == 1)
		return (1);
	while (ft_isspace(input[i]) == 1)
		i++;
	if (check_triple_int(input, &i) == 1)
		return (1);
	return (0);
}

t_sphere	*init_sphere_part2(t_sphere *sphere, char *input, int i)
{
	int			*rgb;

	pass_to_next_element(input, &i);
	sphere->diameter = ft_atof(input + i);
	if (sphere->diameter <= 0)
	{
		free(sphere);
		return (NULL);
	}
	pass_to_next_element(input, &i);
	rgb = get_color_values(input + i);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[2] < 0
		|| rgb[2] > 255)
	{
		free(rgb);
		free(sphere);
		return (NULL);
	}
	sphere->color = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	free(rgb);
	return (sphere);
}

t_sphere	*init_sphere(char *input)
{
	int			i;
	t_sphere	*sphere;

	if (!input || check_sphere(input) == 1)
		return (NULL);
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	i = 2;
	while (ft_isspace(input[i]) == 1)
		i++;
	sphere->pos = get_coords(input + i);
	if (!sphere->pos)
	{
		free(sphere);
		return (NULL);
	}
	sphere = init_sphere_part2(sphere, input, i);
	return (sphere);
}
