/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:38:05 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/02 10:19:12 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	pass_to_next_element(char *str, int *i)
{
	while (ft_isspace(str[*i]) == 0)
		(*i)++;
	while (ft_isspace(str[*i]))
		(*i)++;
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
