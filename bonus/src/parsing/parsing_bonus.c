/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:47:32 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/26 11:28:31 by gpasquet         ###   ########.fr       */
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
			ft_error("Error\nError when reading scene file\n");
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
		ft_error("Error\nFailed to open scene file\n");
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
		ft_error("Error\nScene must have one camera, one ambiant light \
				and one light\n");
		free_scene(&scene);
		return (NULL);
	}
	return (scene);
}
