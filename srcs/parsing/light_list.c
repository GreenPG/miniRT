/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:31:34 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/22 16:25:12 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	free_light_list(t_light_list *light_list)
{
	t_light_list	*tmp;

	tmp = NULL;
	while (light_list)
	{
		tmp = light_list->next;
		free_light(&light_list->light);
		free(light_list);
		light_list = tmp;
	}
	free(tmp);
	free(light_list);
}

void	add_light(t_light_list **light_list, char *line)
{
	t_light_list	*tmp;

	if (!light_list || !(*light_list) || !line)
	{
		free_light_list(*light_list);
		light_list = NULL;
		return ;
	}
	tmp = *light_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = init_light_list(line);
	return ;
}

t_light_list	*init_light_list(char *line)
{
	t_light_list	*light_list;

	if (!line)
		return (NULL);
	light_list = malloc(sizeof(t_light_list));
	if (!light_list)
		return (NULL);
	light_list->light = init_light(line);
	if (!light_list->light)
	{
		free(light_list);
		return (NULL);
	}
	light_list->next = NULL;
	return (light_list);
}
