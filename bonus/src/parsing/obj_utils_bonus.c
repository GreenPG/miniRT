/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:31:14 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/30 08:43:51 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	add_obj_error(t_scene **scene)
{
	ft_error("Error\nError when adding an object\n");
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
