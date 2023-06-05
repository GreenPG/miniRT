/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:35:45 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/01 15:01:39 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	free_ellipsoid(t_ellipsoid **ellipsoid)
{
	if (!ellipsoid || !*ellipsoid)
		return ;
	if ((*ellipsoid)->origin)
		free((*ellipsoid)->origin);
	if ((*ellipsoid)->direction)
		free((*ellipsoid)->direction);
	free(*ellipsoid);
	*ellipsoid = NULL;
	return ;
}

static int	check_ellipsoid(char *str)
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
	if (check_int(str, &i) == 1)
		return (1);
	pass_to_next_element(str, &i);
	if (check_triple_int(str, &i) == 1)
		return (1);
	return (0);
}

static	t_ellipsoid	*init_ellipsoid_part3(t_ellipsoid *ellipsoid)
{
	ellipsoid->alpha = get_alpha(*ellipsoid->direction);
	ellipsoid->beta = get_beta(*ellipsoid->direction);
	return (ellipsoid);
}

static t_ellipsoid	*init_ellipsoid_part2(t_ellipsoid *ellipsoid, char *str, int i)
{
	int			*rgb;

	ellipsoid->a = 1. / (ft_atof(str + i) * ft_atof(str + i)); //division par 0 lololol ca va casser
	pass_to_next_element(str, &i);
	ellipsoid->b = 1. / (ft_atof(str + i) * ft_atof(str + i));
	pass_to_next_element(str, &i);
	ellipsoid->c = 1. / (ft_atof(str + i) * ft_atof(str + i));
	pass_to_next_element(str, &i);
	rgb = get_color_values(str + i);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[2] < 0
		|| rgb[2] > 255)
	{
		free(rgb);
		free_ellipsoid(&ellipsoid);
		return (NULL);
	}
	ellipsoid->color = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	free(rgb);
	pass_to_next_element(str, &i);
	ellipsoid->pattern = plain;
	if (!ft_strncmp("checkerboard", &str[i], ft_strlen("checkerboard")))
		ellipsoid->pattern = checkerboard;
	ellipsoid = init_ellipsoid_part3(ellipsoid);
	return (ellipsoid);
}

t_ellipsoid	*init_ellipsoid(char *str)
{
	t_ellipsoid	*ellipsoid;
	int			i;

	if (!str || check_ellipsoid(str) == 1)
		return (NULL);
	ellipsoid = malloc(sizeof(t_ellipsoid));
	if (!ellipsoid)
		return (NULL);
	i = 2;
	while (ft_isspace(str[i]))
		i++;
	ellipsoid->origin = init_vector(str + i);
	pass_to_next_element(str, &i);
	ellipsoid->direction = init_vector(str + i);
	if (!ellipsoid->origin || ellipsoid->direction->x < -1.0
		|| ellipsoid->direction->x > 1.0 || ellipsoid->direction->y
		< -1.0 || ellipsoid->direction->y > 1.0 || ellipsoid->direction->z
		< -1.0 || ellipsoid->direction->z > 1.0 || !ellipsoid->origin)
	{
		free_ellipsoid(&ellipsoid);
		return (NULL);
	}
	pass_to_next_element(str, &i);
	ellipsoid = init_ellipsoid_part2(ellipsoid, str, i);
	return (ellipsoid);
}