/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:11:47 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/16 10:38:37 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	free_sphere(t_sphere **sphere)
{
	if (!sphere || !*sphere)
		return ;
	if ((*sphere)->origin)
		free((*sphere)->origin);
	free(*sphere);
	*sphere = NULL;
	return ;
}

double	sphere_hit(t_sphere *sphere, t_vector ray)
{
	t_vector oc;
	double a;
	double b;
	double c;
	double d;

	oc.x = -sphere->origin->x;
	oc.y = -sphere->origin->y;
	oc.z = -sphere->origin->z;
	
    a = dot_product(ray, ray);
    b = dot_product(oc, ray);
    c = dot_product(oc, oc) - ((sphere->diameter / 2) * (sphere->diameter / 2));
    d = (b * b) - (a * c);
    if (d > 0)
	{
		double r0;
		double r1;

		r0 = (-b - sqrt(d)) / (a);
		r1 = (-b + sqrt(d)) / (a);
		if (r0 > r1 && r1 >= 0)
			return (r1);
		else if (r1 >= r0 && r0 >= 0)
			return (r0);
		else if (r0 > 0)
			return (r0);
		else if (r1 > 0)
			return (r1);
	}
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
		free_sphere(&sphere);
		return (NULL);
	}
	pass_to_next_element(input, &i);
	rgb = get_color_values(input + i);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[2] < 0
		|| rgb[2] > 255)
	{
		free(rgb);
		free_sphere(&sphere);
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
	sphere->origin = init_vector(input + i);
	if (!sphere->origin)
	{
		free_sphere(&sphere);
		return (NULL);
	}
	sphere = init_sphere_part2(sphere, input, i);
	return (sphere);
}
