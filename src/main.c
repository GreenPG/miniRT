/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 07:45:59 by gtouzali          #+#    #+#             */
/*   Updated: 2023/04/15 09:46:59 by gtouzali         ###   ########.fr       */
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

static void	ft_hook(void *img_v)
{
	mlx_image_t	*img;

	img = (mlx_image_t *)img_v;
	unsigned int	x;
	unsigned int	y;
	static unsigned int k;
	unsigned int g;

	x = 0;
	k++;
	if (k == 512)
		k = 0;
	if (k > 255)
		g = 511 - k;
	else
		g = k;
	
	while(x < img->width)
	{
		y = 0;
		while (y < img->height)
		{
			mlx_put_pixel(img, x, y, get_rgba(x / (img->width / 240), y / (img->height / 200), g, 255));
			y++;
		}
		x++;
	}
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
	camera.pos.x_o = 0;
	camera.pos.y_o = 0;
	camera.pos.z_o = 0;
	camera.pos.x_d = 1;
	camera.pos.y_d = 0;
	camera.pos.z_d = 0;
	//
	ray_launcher(mlx, img, camera);
	mlx_loop_hook(mlx, ft_hook, img);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
