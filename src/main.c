/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 07:45:59 by gtouzali          #+#    #+#             */
/*   Updated: 2023/04/13 16:30:37 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static mlx_t *ft_mlx_create(void)
{
	mlx_t*			mlx;
	mlx_texture_t*	icon;

	mlx_set_setting(0, true);
	mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
	if (!mlx)
		exit(write(2, "MLX: ERROR\n", 11));
	icon = mlx_load_png("./src/gpasquet.png");
	(void)icon;
    mlx_set_icon(mlx, icon);
	mlx_delete_texture(icon);
    return (mlx);
}

static void ft_hook(void* img)
{
	
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			mlx_put_pixel(img, x, y, rand() % RAND_MAX);
			y++;
		}
		x++;
	}	
}

int main(int argc, char **argv)
{
    mlx_t		*mlx;
	mlx_image_t	*img;

	if (argc != 2)
		return (write(2, "Expected only 1 argument\n", 25));
    (void)argv;
    mlx = ft_mlx_create();
	img = mlx_new_image(mlx, mlx->width, mlx->height);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop_hook(mlx, ft_hook, img);
    mlx_loop(mlx);
	mlx_terminate(mlx);
    return (0);
}
