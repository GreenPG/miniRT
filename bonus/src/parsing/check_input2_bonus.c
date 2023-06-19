/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:14:21 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/19 11:36:20 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

int	check_bonus_var(char *str)
{
	int	i;

	i = 0;
	if (ft_strncmp("specular", str, ft_strlen("specular")) == 0)
		if (check_specular(str, &i) == 1)
			return (1);
	if (ft_strncmp("bump", str, ft_strlen("bump")) == 0)
	{
		pass_to_next_element(str, &i);
		pass_to_next_element(str, &i);
	}
	if (ft_strncmp("checkerboard", str, ft_strlen("checkerboard"))
		== 0 || ft_strncmp("./", str, ft_strlen("./")) == 0)
		pass_to_next_element(str, &i);
	return (0);
}

static int	check_triangle2(char *input)
{
	int	i;

	i = 0;
	while (ft_isspace(input[i]))
		i++;
	if (input[i] == '\0')
		return (0);
	if (check_bonus_var(input) == 1)
		return (1);
	return (0);
}

int	check_triangle(char *input)
{
	int	i;

	if (!input)
		return (1);
	i = 2;
	while (ft_isspace(input[i]) == 1)
		i++;
	if (check_triple_float(input, &i) == 1)
		return (1);
	while (ft_isspace(input[i]) == 1)
		i++;
	if (check_triple_float(input, &i) == 1)
		return (1);
	while (ft_isspace(input[i]) == 1)
		i++;
	if (check_triple_float(input, &i) == 1)
		return (1);
	while (ft_isspace(input[i]) == 1)
		i++;
	if (check_triple_int(input, &i) == 1)
		return (1);
	if (check_triangle2(&input[i]) == 1)
		return (1);
	return (0);
}

static int	check_cylinder2(char *str, int i)
{
	if (check_triple_int(str, &i) == 1)
		return (1);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\0')
		return (0);
	if (check_bonus_var(str) == 1)
		return (1);
	return (0);
}

int	check_cylinder(char *str)
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
	if (check_int(str, &i) == 1)
		return (1);
	pass_to_next_element(str, &i);
	if (check_int(str, &i) == 1)
		return (1);
	pass_to_next_element(str, &i);
	if (check_cylinder2(str, i) == 1)
		return (1);
	return (0);
}
