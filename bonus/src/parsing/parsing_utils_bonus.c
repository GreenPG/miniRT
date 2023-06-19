/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:38:05 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/15 17:08:02 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	pass_to_next_element(char *str, int *i)
{
	while (str[*i] && ft_isspace(str[*i]) == 0)
		(*i)++;
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
}
