/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:31:14 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/18 15:19:06 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	get_specular_const(t_obj_list *obj, char *line)
{
	int	i;

	if (!obj || !line)
		return ;
	i = 0;
	obj->sp_e = ft_atof(&line[i]);
	pass_to_next_element(line, &i);
	obj->ks = ft_atof(&line[i]);
	return ;
}

static char	*get_tex(char *line)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	path = malloc((i + 1) * sizeof(char));
	if (!path)
		return (NULL);
	path [i] = '\0';
	while (i > 0)
	{
		path[i - 1] = line[i - 1];
		i--;
	}
	return (path);
}

int	get_bonus_data(t_obj_list **obj_ptr, char *line)
{
	t_obj_list	*obj;
	int			i;

	if (! obj_ptr || !*obj_ptr || !line)
		return (1);
	obj = *obj_ptr;
	i = 2;
	obj->has_bump = 0;
	while (ft_isalpha(line[i]) == 0)
		i++;
	if (!ft_strncmp("./", &line[i - 2], ft_strlen("./")))
		i -= 2;
	if (!ft_strncmp("specular", &line[i], ft_strlen("specular")))
	{
		while (ft_isalpha(line[i]) == 1)
			i++;
		while (ft_isspace(line[i]) == 1)
			i++;
		get_specular_const(obj, &line[i]);
		pass_to_next_element(line, &i);
	}
	if (!ft_strncmp("bump", &line[i], ft_strlen("bump")))
	{
		while (ft_isalpha(line[i]) == 1)
			i++;
		while (ft_isspace(line[i]) == 1)
			i++;
		obj->bump_map = mlx_load_png(get_tex(&line[i]));
		if (!obj->bump_map)
			return (1);
		obj->has_bump = 1;
		pass_to_next_element(line, &i);
	}
	if (!ft_strncmp("checkerboard", &line[i], ft_strlen("checkerboard")))
		obj->pattern = checkerboard;
	else if (!ft_strncmp("./", &line[i], ft_strlen("./")))
	{
		obj->pattern = texture;
		obj->tex = mlx_load_png(get_tex(&line[i]));
		if (!obj->tex)
			return (1);
	}
	else
		obj->pattern = plain;
	return (0);
}

void	add_obj_error(t_scene **scene)
{
	ft_error("Error when adding an object\n");
	free_scene(scene);
	return ;
}

void	add_obj(t_obj_list **list_ptr, t_obj_list *obj)
{
	t_obj_list	*tmp;
	t_obj_list	*prev;

	if (*list_ptr)
	{
		tmp = *list_ptr;
		while (tmp)
		{	
			prev = tmp;
			tmp = tmp->next;
		}
		tmp = obj;
		prev->next = obj;
	}
	else
		*list_ptr = obj;
}
