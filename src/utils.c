/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 07:14:51 by gtouzali          #+#    #+#             */
/*   Updated: 2023/04/19 14:02:03 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int	ft_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	return (i);
}

static double	atof_decimal_part(char *str)
{
	double	result;
	double	scale;
	int		i;

	i = 0;
	result = 0;
	scale = 10;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			break ;
		result = result + (str[i] - '0') / scale;
		scale *= 10;
		i++;
	}
	return (result);
}

double	ft_atof(char *str)
{
	double	result;
	double	sign;
	int		i;

	if (!str)
		return (0);
	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			break ;
		result = (result * 10) + str[i] - '0';
		i++;
	}
	if (str[i] == '.')
		result += atof_decimal_part(str + i + 1);
	return (result * sign);
}
