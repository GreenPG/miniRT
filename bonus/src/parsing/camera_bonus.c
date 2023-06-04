/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:12:52 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/04 10:39:04 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	free_camera(t_camera **camera)
{
	if (!camera || !*camera)
		return ;
	if ((*camera)->origin)
		free((*camera)->origin);
	if ((*camera)->direction)
		free((*camera)->direction);
	if ((*camera)->rays)
		free_rays((*camera)->rays);
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

static int	check_camera_dir(t_vector *direction)
{
	if (direction->x < -1.0 || direction->x > 1.0
		|| direction->y < -1.0 || direction->y > 1.0
		|| direction->z < -1.0 || direction->z > 1.0
		|| (direction->x == 0 && direction->y == 0
			&& direction->z == 0))
		return (1);
	return (0);
}

static t_camera	*init_camera2(t_camera *camera)
{
	if (!camera->origin || !camera->direction
		||check_camera_dir(camera->direction) == 1
		|| camera->fov < 0 || camera->fov > 180)
	{
		ft_error("Error:camera init\n");
		free_camera(&camera);
		return (NULL);
	}
	camera->alpha = get_alpha(*camera->direction) * (180 / M_PI);
	camera->beta = get_beta(*camera->direction) * (180 / M_PI);
	camera->fov *= (M_PI / 180);
	camera->rays = NULL;
	return (camera);
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
	camera->origin = init_vector(input + i);
	pass_to_next_element(input, &i);
	camera->direction = init_vector(input + i);
	pass_to_next_element(input, &i);
	camera->fov = ft_atoi(input + i);
	camera = init_camera2(camera);
	return (camera);
}
