/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/04/18 13:11:47 by gpasquet		  #+#	#+#			 */
/*   Updated: 2023/05/18 15:24:02 by gpasquet         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minirt_bonus.h>

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

t_sphere	*init_sphere_part3(t_sphere *sphere, char *input, int i)
{
	if (!ft_strncmp("checkerboard", &input[i], ft_strlen("checkerboard")))
		sphere->pattern = checkerboard;
	else
	{
		sphere->pattern = texture;
		sphere->tex = mlx_load_png(&input[i]);
		if (!sphere->tex)
			sphere->pattern = plain;
	}
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
	sphere = init_sphere_part3(sphere, input, i);
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
