/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 07:45:59 by gtouzali          #+#    #+#             */
/*   Updated: 2023/04/13 09:09:50 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static mlx_t *ft_mlx_create(void)
{
	mlx_t*			mlx;
	mlx_texture_t*	icon;

	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
	if (!mlx)
		exit(write(2, "MLX: ERROR\n", 11));
	icon = mlx_load_png("./src/gpasquet.png");
	(void)icon;
    mlx_set_icon(mlx, icon);
	mlx_delete_texture(icon);
    return (mlx);
}

static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	(void)mlx;
}

int main(int argc, char **argv)
{
    mlx_t* mlx;

	if (argc != 2)
		return (write(2, "Expected only 1 argument\n", 25));
    (void)argc;
    (void)argv;
    mlx = ft_mlx_create();
	mlx_loop_hook(mlx, ft_hook, mlx);
    mlx_loop(mlx);
	mlx_terminate(mlx);
    return (0);
}
