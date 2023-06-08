/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:31:14 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/08 09:52:56 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	get_specular_const(t_obj_list **obj_ptr, char *line)
{
	t_obj_list	*obj;
	int			i;

	if (!obj_ptr || !*obj_ptr || !line)
		return ;
	obj = *obj_ptr;
	i = 2;
	while (line[i] && line[i] != 's')
		i++;
	if (line[i] == '\0')
	{
		obj->sp_e = 0;
		obj->ks = 0;
		return ;
	}
	pass_to_next_element(line, &i);
	obj->sp_e = ft_atof(&line[i]);
	pass_to_next_element(line, &i);
	obj->ks = ft_atof(&line[i]);
	return ;
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
