/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:32:35 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/02 15:00:09 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	*get_color_values(char	*str)
{
	int		*rgb;
	int		i;

	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
		return (NULL);
	i = 0;
	rgb[0] = ft_atoi(str);
	while (str[i] && ft_isdigit(str[i]) == 1)
		i++;
	if (str[i] == ',')
		i++;
	else
		return (NULL);
	rgb[1] = ft_atoi(str + i);
	while (str[i] && ft_isdigit(str[i]) == 1)
		i++;
	if (str[i] == ',')
		i++;
	else
		return (NULL);
	rgb[2] = ft_atoi(str + i);
	return (rgb);
}
