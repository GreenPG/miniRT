/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:12:52 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/19 15:18:20 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

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
	if (check_triple_int(str, &i) == 1)
		return (1);
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (check_int(str, &i) == 1)
		return (1);
	return (0);
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
	camera->vector = init_vector(input + i);
	if (!camera->vector)
	{
		free(camera);
		return (NULL);
	}
	while (ft_isspace(input[i]) == 0)
		i++;
	while (ft_isspace(input[i]) == 1)
		i++;
	while (ft_isspace(input[i]) == 0)
		i++;
	while (ft_isspace(input[i]) == 1)
		i++;
	camera->fov = ft_atoi(input + i);
	if (camera->fov < 0 || camera->fov > 180)
	{
		free(camera);
		return (NULL);
	}
	camera->fov *= (M_PI / 180);
	return (camera);
}
