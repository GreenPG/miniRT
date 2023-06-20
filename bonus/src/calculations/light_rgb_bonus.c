/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_rgb_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:02:30 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/20 16:44:43 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	increment_color(int *rgb, int color, double ratio, double ks)
{
	rgb[0] += get_r(color) * ratio * ks;
	rgb[1] += get_g(color) * ratio * ks;
	rgb[2] += get_b(color) * ratio * ks;
}

void	clamp_rgb(int *rgb)
{
	if (rgb[0] > 255)
		rgb[0] = 255;
	if (rgb[1] > 255)
		rgb[1] = 255;
	if (rgb[2] > 255)
		rgb[2] = 255;
}

int	*init_rgb_tab(void)
{
	int	*rgb;

	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
		return (NULL);
	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	return (rgb);
}
