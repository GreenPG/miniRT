/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_parsing_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:49:23 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/21 10:44:33 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static mlx_texture_t	*get_tex_path(char *line)
{
	char			*path;
	int				i;
	mlx_texture_t	*tex;

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
	tex = mlx_load_png(path);
	free (path);
	if (!tex)
		return (NULL);
	return (tex);
}

static int	get_bump_data(t_obj_list *obj, char *line, int *i)
{
	while (ft_isalpha(line[*i]) == 1)
		(*i)++;
	while (ft_isspace(line[*i]) == 1)
		(*i)++;
	obj->bump_map = get_tex_path(&line[*i]);
	if (!obj->bump_map)
		return (1);
	obj->has_bump = 1;
	pass_to_next_element(line, i);
	return (0);
}

static void	get_specular_const(t_obj_list *obj, char *line, int *i)
{
	if (!obj || !line)
		return ;
	while (ft_isalpha(line[*i]) == 1)
		(*i)++;
	while (ft_isspace(line[*i]) == 1)
		(*i)++;
	obj->sp_e = ft_atof(&line[*i]);
	pass_to_next_element(line, i);
	obj->ks = ft_atof(&line[*i]);
	pass_to_next_element(line, i);
}

static int	get_tex(t_obj_list *obj, char *line)
{
	int		i;

	i = 0;
	obj->pattern = texture;
	obj->tex = get_tex_path(&line[i]);
	if (!obj->tex)
		return (1);
	return (0);
}

int	get_bonus_data(t_obj_list **obj_ptr, char *line)
{
	t_obj_list	*obj;
	int			i;

	if (! obj_ptr || !*obj_ptr || !line)
		return (1);
	obj = *obj_ptr;
	i = 2;
	while (line[i] && ft_isalpha(line[i]) == 0)
		i++;
	if (!ft_strncmp("./", &line[i - 2], ft_strlen("./")))
		i -= 2;
	if (!ft_strncmp("specular", &line[i], ft_strlen("specular")))
		get_specular_const(obj, line, &i);
	if (!ft_strncmp("bump", &line[i], ft_strlen("bump")))
		if (get_bump_data(obj, line, &i) == 1)
			return (1);
	if (!ft_strncmp("checkerboard", &line[i], ft_strlen("checkerboard")))
		obj->pattern = checkerboard;
	else if (!ft_strncmp("./", &line[i], ft_strlen("./")))
		if (get_tex(obj, &line[i]) == 1)
			return (1);
	return (0);
}
