/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:38:05 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/19 11:27:38 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	pass_to_next_element(char *str, int *i)
{
	while (str[*i] && ft_isspace(str[*i]) == 0)
		(*i)++;
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
}

int	check_bump(char *str, int *i)
{
	if (!str)
		return (1);
	while (ft_isalpha(str[*i]))
		(*i)++;
	while (ft_isspace(str[*i]))
		(*i)++;
	return (0);
}
