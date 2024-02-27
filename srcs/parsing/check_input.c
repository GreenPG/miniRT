/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:07:43 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/15 17:20:48 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	check_specular(char *str, int *i)
{
	if (!str)
		return (1);
	while (ft_isalpha(str[*i]))
		(*i)++;
	while (ft_isspace(str[*i]))
		(*i)++;
	if (check_float(str, i) == 1)
		return (1);
	while (ft_isspace(str[*i]))
		(*i)++;
	if (check_float(str, i) == 1)
		return (1);
	return (0);
}

int	check_float(char *str, int *i)
{
	if (ft_isdigit(str[*i]) == 0 && str[*i] != '-' && str[*i] != '+')
		return (1);
	if (str[*i] == '-' || str[*i] == '+')
		(*i)++;
	while (ft_isdigit(str[*i]) == 1)
		(*i)++;
	if (str[*i] == '\0' || ft_isspace(str[*i]) == 1 || str[*i] == ','
		|| str[*i] == ',')
		return (0);
	if (str[*i] != '.' || ft_isdigit(str[*i + 1]) == 0)
		return (1);
	(*i)++;
	while (ft_isdigit(str[*i]))
		(*i)++;
	if (str[*i] != '\0' && ft_isspace(str[*i]) == 0 && str[*i] != ','
		&& str[*i] != '.')
		return (1);
	return (0);
}

int	check_triple_int(char *str, int *i)
{
	if (ft_isdigit(str[*i]) == 0)
		return (1);
	while (ft_isdigit(str[*i]) == 1)
		(*i)++;
	if (str[*i] != ',' || ft_isdigit(str[*i + 1]) == 0)
		return (1);
	(*i)++;
	while (ft_isdigit(str[*i]))
		(*i)++;
	if (str[*i] != ',' || ft_isdigit(str[*i + 1]) == 0)
		return (1);
	(*i)++;
	while (ft_isdigit(str[*i]))
		(*i)++;
	if (str[*i] == '\0' || ft_isspace(str[*i]) == 1)
		return (0);
	return (1);
}

int	check_int(char *str, int *i)
{
	if (ft_isdigit(str[*i]) == 0 && str[*i] != '-' && str[*i] != '+')
		return (1);
	if (str[*i] == '-' || str[*i] == '+')
		(*i)++;
	while (str[*i] && ft_isdigit(str[*i]))
		(*i)++;
	if (str[*i] == '\0' || ft_isspace(str[*i]) == 1 || str[*i] == '.'
		|| str[*i] == ',')
		return (0);
	return (1);
}

int	check_triple_float(char *str, int *i)
{
	if (check_float(str, i) == 1)
		return (1);
	if (str[*i] != ',' || str[*i + 1] == ',')
		return (1);
	(*i)++;
	if (check_float(str, i) == 1)
		return (1);
	if (str[*i] != ',' || str[*i + 1] == ',')
		return (1);
	(*i)++;
	if (check_float(str, i) == 1)
		return (1);
	if (str[*i] == '\0' || ft_isspace(str[*i]) == 1)
		return (0);
	return (1);
}
