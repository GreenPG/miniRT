/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:47:32 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/17 17:16:58 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	check_path(char *path)
{
	int		start;
	char	*extension;

	start = ft_strlen(path) - 3;
	extension = ft_substr(path, start, 3);
	if (ft_strncmp(extension, ".rt", 3) != 0)
	{
		free(extension);
		return (1);
	}
	free(extension);
	return (0);
}

static int	check_ambiant_l_def(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]) == 1)
		i++;
	if (check_float(str, &i) == 1)
		return (1);
	while (ft_isspace(str[i]) == 1)
		i++;
	if (check_triple_int(str, &i) == 1)
		return (1);
	return (0);
}

t_ambiant_l	*init_ambiant_l(char *input)
{
	t_ambiant_l	*ambiant_l;
	int			i;
	int			start;

	if (!input || check_ambiant_l_def(input + 1) == 1)
		return (NULL);
	ambiant_l = malloc(sizeof(t_ambiant_l));
	if (!ambiant_l)
	{
		ft_error("Error: fatal\n");
		return (NULL);
	}
	i = 1;
	while (ft_isspace(input[i == 1]))
		i++;
	start = i;
	while (ft_isspace(input[i]) == 0)
		i++;
	ambiant_l->light_ratio = ft_atof(ft_substr(input, start, i));
	if (ambiant_l->light_ratio < 0 || ambiant_l->light_ratio > 1)
	{
		ft_error("Light ratio should be within the range of 0 to 1");
		free(ambiant_l);
		return (NULL);
	}
	while (ft_isspace(input[i]))
		i++;
	ambiant_l->colors = get_color(input + i);
	if (ambiant_l->colors == -1)
	{
		free(ambiant_l);
		return (NULL);
	}
	return (ambiant_l);
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
	if (check_triple_int(str, &i))
		return (1);
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (check_int(str, &i))
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
	camera->pos = get_coords(input + i);
	if (!camera->pos)
	{
		free(camera);
		return (NULL);
	}
	while (ft_isspace(input[i]) == 0)
		i++;
	while (ft_isspace(input[i]) == 1)
		i++;
	camera->orientation_vector = get_vector(input + i);
	if (!camera->orientation_vector)
	{
		free(camera);
		return (NULL);
	}
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
