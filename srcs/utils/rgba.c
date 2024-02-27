/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgba.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:36:28 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/02 15:00:09 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_r(int rgba)
{
	return ((rgba >> 24) & 0xFF);
}

int	get_g(int rgba)
{
	return ((rgba >> 16) & 0xFF);
}

int	get_b(int rgba)
{
	return ((rgba >> 8) & 0xFF);
}

int	get_a(int rgba)
{
	return (rgba & 0xFF);
}
