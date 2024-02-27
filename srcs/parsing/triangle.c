/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:23:28 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/27 09:00:26 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	null_all_triangle(t_triangle *triangle)
{
	triangle->a = NULL;
	triangle->b = NULL;
	triangle->c = NULL;
	triangle->normal = NULL;
	triangle->up = NULL;
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
	*normal = vector_cross_tr(ab, ac);
	*normal = vector_norm(*normal);
	return (normal);
}

static t_triangle	*init_triangle3(t_triangle *triangle, char *input, int i)
{
	int			*rgb;

	rgb = get_color_values(input + i);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255
		|| rgb[2] < 0 || rgb[2] > 255)
	{
		ft_error("Error\nWrong color\n");
		free(rgb);
		free_triangle(&triangle);
		return (NULL);
	}
	triangle->color = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	free(rgb);
	triangle->up = get_up(triangle->normal);
	return (triangle);
}

static t_triangle	*init_triangle2(t_triangle *triangle, char *input, int i)
{
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
	triangle->normal = get_triangle_normal(triangle->a, triangle->b,
			triangle->c);
	pass_to_next_element(input, &i);
	triangle = init_triangle3(triangle, input, i);
	return (triangle);
}

t_triangle	*init_triangle(char	*input)
{
	int			i;
	t_triangle	*triangle;

	if (!input || check_triangle(input) == 1)
		return (NULL);
	triangle = malloc(sizeof(t_triangle));
	if (!triangle)
	{
		ft_error("Error\nMalloc error\n");
		return (NULL);
	}
	triangle->up = NULL;
	null_all_triangle(triangle);
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
	triangle = init_triangle2(triangle, input, i);
	return (triangle);
}
