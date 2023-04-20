/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiant_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:12:24 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/20 11:08:44 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static int	check_ambiant_l_def(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]) == 1)
		i++;
	if (check_float(str, &i) == 1)
		return (1);
	while (ft_isspace(str[i]) == 1)
		i++;
	if (check_triple_int(str, &i) == 1)
		return (1);
	return (0);
}

t_ambiant_l	*init_ambiant_l_part2(t_ambiant_l *ambiant_l, char *input, int i)
{
	int			*rgb;

	pass_to_next_element(input, &i);
	rgb = get_color_values(input + i);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[2] < 0
		|| rgb[2] > 255)
	{
		free(rgb);
		free(ambiant_l);
		return (NULL);
	}
	ambiant_l->colors = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	free(rgb);
	return (ambiant_l);
}

t_ambiant_l	*init_ambiant_l(char *input)
{
	t_ambiant_l	*ambiant_l;
	int			i;

	if (!input || check_ambiant_l_def(input + 1) == 1)
		return (NULL);
	ambiant_l = malloc(sizeof(t_ambiant_l));
	if (!ambiant_l)
	{
		ft_error("Error: fatal\n");
		return (NULL);
	}
	i = 1;
	while (ft_isspace(input[i == 1]))
		i++;
	ambiant_l->light_ratio = ft_atof(input + i);
	if (ambiant_l->light_ratio < 0 || ambiant_l->light_ratio > 1)
	{
		ft_error("Light ratio should be within the range of 0 to 1\n");
		free(ambiant_l);
		return (NULL);
	}
	ambiant_l = init_ambiant_l_part2(ambiant_l, input, i);
	return (ambiant_l);
}
