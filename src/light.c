/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:51:01 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/11 17:09:35 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	free_light(t_light **light)
{
	if (!light || !*light)
		return ;
	if (((*light)->pos))
		free((*light)->pos);
	free(*light);
	*light = NULL;
	return ;
}

int	get_diffuse_ratio(t_light *light, t_vector normal)
{
	double		diffuse_ratio;
	double		light_dir_len;
	t_vector	light_dir;
	int			r;
	int			g;
	int			b;

	light_dir.x_o = normal.x_o;
	light_dir.y_o = normal.y_o;
	light_dir.z_o = normal.z_o;
	light_dir.x_d = light->pos->x - normal.x_o;
	light_dir.y_d = light->pos->y - normal.y_o;
	light_dir.z_d = light->pos->z - normal.z_o;
	light_dir_len = sqrt(dot_product(light_dir, light_dir));
	light_dir.x_d /= light_dir_len;
	light_dir.y_d /= light_dir_len;
	light_dir.z_d /= light_dir_len;
	diffuse_ratio = dot_product(normal, light_dir);
	diffuse_ratio = fmax(0.0, diffuse_ratio);
	diffuse_ratio *= light->brightness;
	r = get_r(light->colors) * diffuse_ratio;
	g = get_g(light->colors) * diffuse_ratio;
	b = get_b(light->colors) * diffuse_ratio;
	return (get_rgba(r, g, b, 255));
}

static int	check_light(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 1;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (check_triple_float(str, &i) == 1)
		return (1);
	while (ft_isspace(str[i]) == 1)
		i++;
	if (check_float(str, &i) == 1)
		return (1);
	while (ft_isspace(str[i]) == 1)
		i++;
	if (check_triple_int(str, &i) == 1)
		return (1);
	return (0);
}

t_light	*init_light_part2(t_light *light, char *str, int i)
{
	int		*rgb;

	pass_to_next_element(str, &i);
	light->brightness = ft_atof(str + i);
	if (light->brightness < 0 || light->brightness > 1)
	{
		ft_error("Light brightness must be within the range of 0 to 1\n");
		free_light(&light);
		return (NULL);
	}
	pass_to_next_element(str, &i);
	rgb = get_color_values(str + i);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[2] < 0
		|| rgb[2] > 255)
	{
		free(rgb);
		free_light(&light);
		return (NULL);
	}
	light->colors = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	free(rgb);
	return (light);
}

t_light	*init_light(char *str)
{
	t_light	*light;
	int		i;

	if (!str || check_light(str) == 1)
		return (NULL);
	light = malloc(sizeof(t_light));
	if (!light)
	{
		ft_error("Error: fatal\n");
		return (NULL);
	}
	i = 1;
	while (ft_isspace(str[i]))
		i++;
	light->pos = get_coords(str + i);
	if (!light->pos)
	{
		free_light(&light);
		return (NULL);
	}
	light = init_light_part2(light, str, i);
	return (light);
}
