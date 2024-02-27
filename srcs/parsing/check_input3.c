/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:30:25 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/30 09:55:17 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static int	check_ellipsoid2(char *str, int i)
{
	if (check_triple_int(str, &i) == 1)
		return (1);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\0')
		return (0);
	if (check_var(&str[i]) == 1)
		return (1);
	return (0);
}

int	check_ellipsoid(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 2;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (check_triple_float(str, &i) == 1)
		return (1);
	pass_to_next_element(str, &i);
	if (check_triple_float(str, &i) == 1)
		return (1);
	pass_to_next_element(str, &i);
	if (check_float(str, &i) == 1)
		return (1);
	pass_to_next_element(str, &i);
	if (check_float(str, &i) == 1)
		return (1);
	pass_to_next_element(str, &i);
	if (check_float(str, &i) == 1)
		return (1);
	pass_to_next_element(str, &i);
	if (check_ellipsoid2(str, i) == 1)
		return (1);
	return (0);
}
