/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 07:45:59 by gtouzali          #+#    #+#             */
/*   Updated: 2023/04/19 10:05:41 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static mlx_t	*ft_mlx_create(void)
{
	mlx_t			*mlx;
	mlx_texture_t	*icon;

	mlx_set_setting(0, true);
	mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
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
	unsigned int	x;
	unsigned int	y;

	img = (mlx_image_t *)img_v;
	x = 0;
	while(x < img->width)
	{
		y = 0;
		while (y < img->height)
		{
			//mlx_put_pixel(img, x, y, get_rgba(x / (img->width / 240), y / (img->height / 200), 0, 255));
			y++;
		}
		x++;
	}
}
void	show_main_menu(mlx_image_t *img, mlx_t *mlx)
{
	(void)img;
	mlx_image_t *test_img;	

	test_img = mlx_put_string(mlx, "MAIN MENU", mlx->width / 2 - 100, 0);
	mlx_resize_image(test_img, 200, 40);
}

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_camera	camera;
	t_vector	pos;
	
	if (argc != 2)
		return (ft_error("Error: expected usage is ./miniRT <path to .rt file>\n"));
	(void)argv;
	mlx = ft_mlx_create();
	//parsing
	//rendering
	//
	pos.x_o = 0;
	pos.y_o = 0;
	pos.z_o = 0;
	pos.x_d = 0;
	pos.y_d = 0;
	pos.z_d = 1;
	camera.fov = 2.08;
	camera.pos = pos;
	//
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, img, 0, 0);
	ray_launcher(mlx, img, camera);
	mlx_loop_hook(mlx, ft_hook, img);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
