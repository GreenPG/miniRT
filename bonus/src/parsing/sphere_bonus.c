/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   sphere_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/04/18 13:11:47 by gpasquet		  #+#	#+#			 */
/*   Updated: 2023/06/16 09:44:58 by gpasquet         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minirt_bonus.h>

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
	while (ft_isspace(input[i]))
		i++;
	if (input[i] == '\0')
		return (0);
	if (ft_strncmp("specular", &input[i], ft_strlen("specular")) == 0)
		if (check_specular(input, &i) == 1)
			return (1);
	if (ft_strncmp("checkerboard", &input[i], ft_strlen("checkerboard")) == 0 || ft_strncmp("./", &input[i], ft_strlen("./")) == 0)
		pass_to_next_element(input, &i);	
	if (input[i] != '\0')
		return (1);
	return (0);
}

t_sphere	*init_sphere_part3(t_sphere *sphere)
{
	sphere->up = malloc(sizeof(t_vector));
	sphere->up->x = 0;
	sphere->up->y = 0;
	sphere->up->z = 1;
	sphere->direction = malloc(sizeof(t_vector));
	sphere->direction->x = 0;
	sphere->direction->y = 1;
	sphere->direction->z = 0;
	return (sphere);
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
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255
		|| rgb[2] < 0 || rgb[2] > 255)
	{
		free(rgb);
		free_sphere(&sphere);
		return (NULL);
	}
	sphere->color = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	pass_to_next_element(input, &i);
	free(rgb);
	sphere = init_sphere_part3(sphere);
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
