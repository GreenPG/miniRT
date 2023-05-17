/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:35:45 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/17 17:24:46 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	free_cylinder(t_cylinder **cylinder)
{
	if (!cylinder || !*cylinder)
		return ;
	if ((*cylinder)->origin)
		free((*cylinder)->origin);
	if ((*cylinder)->direction)
		free((*cylinder)->direction);
	free(*cylinder);
	*cylinder = NULL;
	return ;
}

t_vector	transform_ray(t_vector ray, t_cylinder *cylinder)
{
	//la la separation en deux relou encore
	double		alpha;
	double		beta;
	double		tmpx;
	double		tmpy;

	alpha = cylinder->alpha;
	beta = cylinder->beta;
	ray.x = -cylinder->origin->x;
	ray.y = -cylinder->origin->y;
	ray.z = -cylinder->origin->z;
	tmpx = ray.x;
	tmpy = ray.y;
	ray.x = ray.x * cos(cylinder->alpha) - ray.y * sin(cylinder->alpha)
		* cos(cylinder->beta) + ray.z * sin(cylinder->alpha)
		* sin(cylinder->beta);
	ray.y = tmpx * sin(cylinder->alpha) + ray.y * cos(cylinder->beta)
		* cos(cylinder->alpha) - ray.z * cos(cylinder->alpha)
		* sin (cylinder->beta);
	ray.z = tmpy * sin(cylinder->beta) + ray.z * cos(cylinder->beta);
	return (ray);
}

double	cylinder_hit(t_cylinder *cylinder, t_vector ray)
{
	double		a;
	double		b;
	double		c;
	double		*root;
	t_vector	rayo;
	double		tmpx;
	double		tmpy;

	tmpx = ray.x;
	tmpy = ray.y;
	ray.x = ray.x * cos(cylinder->alpha) - ray.y * sin(cylinder->alpha)
		* cos(cylinder->beta) + ray.z * sin(cylinder->alpha)
		* sin(cylinder->beta);
	ray.y = tmpx * sin(cylinder->alpha) + ray.y * cos(cylinder->beta)
		* cos(cylinder->alpha) - ray.z * cos(cylinder->alpha)
		* sin (cylinder->beta);
	ray.z = tmpy * sin(cylinder->beta) + ray.z * cos(cylinder->beta);
	rayo = transform_ray(ray, cylinder);
	a = ray.x * ray.x + ray.z * ray.z;
	b = 2 * (rayo.x * ray.x + rayo.z * ray.z);
	c = rayo.x * rayo.x + rayo.z * rayo.z - (cylinder->diameter / 2);
	root = cyl_quadratic(a, b, c);
	if (!root)
		return (INFINITY);
	if (root[0] > 0 && root[0] < root[1] && rayo.y + root[0] * ray.y
		> -cylinder->height / 2 && rayo.y + root[0] * ray.y
		< cylinder->height / 2)
		return (root[0]);
	else if (root[1] > 0 && rayo.y + root[1] * ray.y
		> -cylinder->height / 2 && rayo.y + root[1] * ray.y
		< cylinder->height / 2)
		return (root[1]);
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

static double	get_theta(t_vector vec)
{
	return (-atan2(vec.z, fabs(vec.x)));
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
	cylinder->origin = init_vector(str + i);
	pass_to_next_element(str, &i);
	cylinder->direction = init_vector(str + i);
	if (!cylinder->origin || cylinder->direction->x < -1.0
		|| cylinder->direction->x > 1.0 || cylinder->direction->y
		< -1.0 || cylinder->direction->y > 1.0 || cylinder->direction->z
		< -1.0 || cylinder->direction->z > 1.0 || !cylinder->origin)
	{
		free_cylinder(&cylinder);
		return (NULL);
	}
	pass_to_next_element(str, &i);
	cylinder = init_cylinder_part2(cylinder, str, i);
	cylinder->alpha = get_alpha(*cylinder->direction);
	cylinder->beta = get_beta(*cylinder->direction);
	cylinder->theta = get_theta(*cylinder->direction);
	return (cylinder);
}
