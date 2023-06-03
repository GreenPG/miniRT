/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:47:32 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/03 16:53:35 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

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

static t_scene	*init_scene(void)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
	{
		ft_error("Error\n");
		return (NULL);
	}
	scene->camera = NULL;
	scene->ambiant_l = NULL;
	scene->light_list = NULL;
	scene->obj_list = NULL;
	return (scene);
}

static void	finish_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

static t_scene	*fill_scene(t_scene *scene, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (!line)
		{
			ft_error("Error\n");
			return (NULL);
		}
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		choose_component(line, &scene);
		free(line);
		if (!scene)
		{
			finish_gnl(fd);
			return (NULL);
		}
		line = get_next_line(fd);
	}
	return (scene);
}

t_scene	*parsing(char *path)
{
	int		fd;
	t_scene	*scene;

	if (!path || check_path(path) == 1)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_error("Error\n");
		return (NULL);
	}
	scene = init_scene();
	if (!scene)
		return (NULL);
	scene = fill_scene(scene, fd);
	if (!scene)
		return (NULL);
	close(fd);
	if (!scene->camera || !scene->ambiant_l || !scene->light_list)
	{
		ft_error("Scene must have one camera, one ambiant light \
				and one light\n");
		free_scene(&scene);
		return (NULL);
	}
	return (scene);
}
