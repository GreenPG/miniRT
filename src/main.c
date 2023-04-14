/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 07:45:59 by gtouzali          #+#    #+#             */
/*   Updated: 2023/04/14 13:46:03 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static mlx_t	*ft_mlx_create(void)
{
	mlx_t			*mlx;
	mlx_texture_t	*icon;

	mlx_set_setting(0, true);
	mlx = mlx_init(1700, 900, "MiniRT", true);
	if (!mlx)
		exit(ft_error("MLX: ERROR\n"));
	icon = mlx_load_png("./src/gpasquet.png");
	(void)icon;
	mlx_set_icon(mlx, icon);
	mlx_delete_texture(icon);
	return (mlx);
}

static void	ft_hook(void *img)
{
	(void)img;
}

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	if (argc != 2)
		return (ft_error("Error: expected usage is ./miniRT <path to .rt file>\n"));
	(void)argv;
	mlx = ft_mlx_create();
	//parsing
	//rendering
	img = mlx_new_image(mlx, mlx->width, mlx->height);
	mlx_image_to_window(mlx, img, 0, 0);
	//
	t_camera camera;
	
	camera.fov = 90;
	camera.vector.x_o = 0;
	camera.vector.y_o = 0;
	camera.vector.z_o = 0;
	camera.vector.x_d = 1;
	camera.vector.y_d = 0;
	camera.vector.z_d = 0;
	//
	ray_launcher(mlx, img, camera);
	mlx_loop_hook(mlx, ft_hook, img);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
