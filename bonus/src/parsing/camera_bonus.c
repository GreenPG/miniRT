/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:12:52 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/27 13:54:10 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	null_all_camera(t_camera *camera)
{
	camera->origin = NULL;
	camera->direction = NULL;
	camera->rays = NULL;
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
	{
		ft_error("Error\nDirection values must be between -1 and 1\n");
		return (1);
	}
	return (0);
}

static t_camera	*init_camera2(t_camera *camera)
{
	if (!camera->origin || !camera->direction
		||check_camera_dir(camera->direction) == 1
		|| camera->fov < 0 || camera->fov > 180)
	{
		ft_error("Error\ncamera init\n");
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
	{
		ft_error("Error\nMalloc error\n");
		return (NULL);
	}
	null_all_camera(camera);
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
