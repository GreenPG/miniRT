/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:23:28 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/15 09:57:58 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	free_triangle(t_triangle **triangle_ptr)
{
	t_triangle	*triangle;

	triangle = *triangle_ptr;
	if (!triangle_ptr || !*triangle_ptr)
		return ;
	if (triangle->a)
		free(triangle->a);
	if (triangle->b)
		free(triangle->b);
	if (triangle->c)
		free(triangle->c);
	if (triangle->normal)
		free(triangle->normal);
	free(triangle);
	triangle = NULL;
	return ;
}

static int	check_triangle(char *input)
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
	while (ft_isspace(input[i]))
		i++;
	if (input[i] == '\0')
		return (0);
	if (ft_strncmp("checkerboard", &input[i], ft_strlen("checkerboard")) == 0)
		pass_to_next_element(input, &i);
	if (ft_strncmp("specular", &input[i], ft_strlen("specular")) == 0)
		if (check_specular(input, &i) == 1)
			return (1);
	if (input[i] != '\0')
		return (1);
	return (0);
}

t_vector	*get_triangle_normal(t_vector *a, t_vector *b, t_vector *c)
{
	t_vector	*normal;
	t_vector	ab;
	t_vector	ac;
	
	if (!a || !b || !c)
		return (NULL);
	normal = malloc(sizeof(t_vector));
	if (!normal)
		return (NULL);
	ab.x = b->x - a->x;
	ab.y = b->y - a->y;
	ab.z = b->z - a->z;
	ac.x = c->x - a->x;
	ac.y = c->y - a->y;
	ac.z = c->z - a->z;
	*normal = vector_cross(ab, ac);
	vector_norm(normal);
	return (normal);
}

t_triangle	*init_triangle(char	*input)
{
	int			i;
	int			*rgb;
	t_triangle	*triangle;

	if (!input || check_triangle(input) == 1)
		return (NULL);
	triangle = malloc(sizeof(t_triangle));
	if (!triangle)
		return (NULL);
	i = 2;
	while (ft_isspace(input[i]) == 1)
		i++;
	triangle->a = init_vector(input + i);
	if (!triangle->a)
	{
		free_triangle(&triangle);
		return (NULL);
	}
	pass_to_next_element(input, &i);
	triangle->b = init_vector(input + i);
	if (!triangle->b)
	{
		free_triangle(&triangle);
		return (NULL);
	}
	pass_to_next_element(input, &i);
	triangle->c = init_vector(input + i);
	if (!triangle->c)
	{
		free_triangle(&triangle);
		return (NULL);
	}
	triangle->normal = get_triangle_normal(triangle->a, triangle->b, triangle->c);
	pass_to_next_element(input, &i);
	rgb = get_color_values(input + i);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255
		|| rgb[2] < 0 || rgb[2] > 255)
	{
		free(rgb);
		free_triangle(&triangle);
		return (NULL);
	}
	triangle->color = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	free(rgb);
	return (triangle);
}
