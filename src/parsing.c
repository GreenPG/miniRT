/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:47:32 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/19 16:48:29 by gpasquet         ###   ########.fr       */
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

void	add_obj(char *line, t_obj_list **list_ptr, t_type type)
{
	t_obj_list	*tmp;
	t_obj_list	*prev;
	t_obj_list	*obj;

	if (!line)
		return ;
	obj = malloc(sizeof(t_obj_list));
	if (!obj)
	{
		*list_ptr = NULL;
		return ;
	}
	obj->type = type;
	if (type == sphere)
		obj->obj = init_sphere(line);
	obj->next = NULL;
	if (*list_ptr)
	{
		tmp = *list_ptr;
		while (*list_ptr) 
		{	
			prev = tmp;
			tmp = tmp->next;
		}
		*list_ptr = obj;
		tmp->next = obj;
	}
	else
		*list_ptr = obj;
	return ;
}		

static void	choose_component(char *line, t_scene *scene)
{
	int	i;

	if (!line || !scene)
		return ;
	i = 0;
	while (line[i] && ft_isspace(line[i]) == 1)
		i++;
	if (ft_strncmp(line + i, "A ", 2) == 0)
	{
		if (scene->ambiant_l)
		{
			ft_error("Scene must have only one ambiant light\n");
			scene = NULL;
			return ;
		}
		scene->ambiant_l = init_ambiant_l(line + i);
	}
	else if (ft_strncmp(line + i, "C ", 2) == 0)
	{	
		if (scene->camera)
		{
			ft_error("Scene must have only one ambiant light\n");
			scene = NULL;
			return ;
		}
		scene->camera = init_camera(line  + i);
	}
	else if (ft_strncmp(line + i, "L ", 2) == 0)
	{
		if (scene->light)
		{
			ft_error("Scene must have only one light\n");
			scene = NULL;
			return ;
		}
		scene->light = init_light(line + i);
	}
	else if (ft_strncmp(line + i, "sp ", 2) == 0)
	{	
		add_obj(line + i, &scene->obj_list, sphere);
		if (!scene->obj_list)
		{
			ft_error("Error when adding an object\n");
			free(scene);
			scene = NULL;
			return ;
		}
	}
	return ;
}

t_scene	*parsing(char *path)
{
	char	*line;
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
	scene = malloc(sizeof(t_scene));
	if (!scene)
	{
		ft_error("Error\n");
		return (NULL);
	}
	scene->camera = NULL;
	scene->ambiant_l = NULL;
	scene->light = NULL;
	scene->obj_list = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (!line)
		{
			ft_error("Error\n");
			return (NULL);
		}
		line[ft_strlen(line) - 1] = '\0';
		choose_component(line, scene);
		free(line);
		if (!scene)
		{
			return (NULL);
		}
		line = get_next_line(fd);
	}
	close(fd);
	if (!scene->camera || !scene->ambiant_l || !scene->light)
	{
		ft_error("Scene must have one camera, one ambiant light and one light\n");
		free(scene);
		return (NULL);
	}
	return (scene);
}
