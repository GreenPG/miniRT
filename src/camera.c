/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:12:52 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/13 17:59:06 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	free_camera(t_camera **camera)
{
	if (!camera || !*camera)
		return ;
	if ((*camera)->origin)
		free((*camera)->origin);
	if ((*camera)->direction)
		free((*camera)->direction);
	free(*camera);
	*camera = (NULL);
	return ;
}

static int	check_cam(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 1;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (check_triple_float(str, &i) == 1)
		return (1);
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (check_triple_float(str, &i) == 1)
		return (1);
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (check_int(str, &i) == 1)
		return (1);
	return (0);
}

double	get_alpha(t_vector vec)
{
	return (atan2(vec.x, vec.y));
}

double	get_beta(t_vector vec)
{
	return (-atan2(vec.z, fabs(vec.y)));
}

t_camera	*init_camera(char *input)
{
	t_camera	*camera;
	int			i;

	if (!input || check_cam(input) == 1)
		return (NULL);
	camera = malloc(sizeof(t_camera));
	if (!camera)
		return (NULL);
	i = 1;
	while (ft_isspace(input[i]))
		i++;
	camera->origin = get_coords(input + i);
	camera->direction = get_coords(input + i);
	pass_to_next_element(input, &i);
	pass_to_next_element(input, &i);
	camera->fov = ft_atoi(input + i);
	if (!camera->origin || camera->direction || camera->fov < 0 || camera->fov > 180)
	{
		free_camera(&camera);
		return (NULL);
	}
	camera->alpha = get_alpha(*camera->direction) * (180 / M_PI);
	camera->beta  = get_beta(*camera->direction) * (180 / M_PI);
	camera->fov *= (M_PI / 180);
	return (camera);
}
