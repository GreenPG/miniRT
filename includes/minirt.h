/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 07:46:56 by gtouzali          #+#    #+#             */
/*   Updated: 2023/04/19 09:00:42 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>

#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"

#include "./config.h"
#include "structs_utils.h"
#include "sphere.h"
#include "camera.h"

int	ft_error(char *str);
double	dot_product(const t_vector v, const t_vector u);
int get_rgba(int r, int g, int b, int a);
int	ray_launcher(mlx_t *mlx, mlx_image_t *img, t_camera camera);

#endif