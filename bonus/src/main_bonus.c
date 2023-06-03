/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: gtouzali <gtouzali@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/04/13 07:45:59 by gtouzali		  #+#	#+#			 */
/*   Updated: 2023/06/01 16:51:33 by gpasquet         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minirt_bonus.h>

static mlx_t	*ft_mlx_create(void)
{
	mlx_t			*mlx;
	mlx_texture_t	*icon;

	mlx_set_setting(0, true);
	mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
	if (!mlx)
		exit(ft_error("MLX: ERROR\n"));
	icon = mlx_load_png("./bonus/src/gpasquet.png");
	(void)icon;
	mlx_set_icon(mlx, icon);
	mlx_delete_texture(icon);
	return (mlx);
}

static t_data	*init_image(mlx_t *mlx, t_scene *scene)
{
	t_data		*data;

	scene->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	init_rays(scene);
	if (!scene->camera->rays)
		return (NULL);
	world_translate(scene, -scene->camera->origin->x,
		-scene->camera->origin->y, -scene->camera->origin->z);
	world_rotate(scene, scene->camera->alpha, scene->camera->beta);
	render(scene->img, scene);
	data = malloc(sizeof(t_data));
	if (!data)
	{
		ft_error("ERROR\n");
		return (NULL);
	}
	data->mlx = mlx;
	data->scene = scene;
	return (data);
}

static void	loop(t_data *data, mlx_t *mlx)
{
	mlx_mouse_hook(data->mlx, mouse_handle, data);
	mlx_key_hook(mlx, &handle_keypress, data);
	mlx_loop(mlx);
}

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	t_scene		*scene;
	t_data		*data;

	if (argc != 2)
		return (ft_error
			("Error: expected usage is ./miniRT <path to.rt file>\n"));
	(void)argv;
	scene = parsing(argv[1]);
	scene->obj_selected = NULL;
	if (!scene)
	{
		ft_error("ERROR\n");
		return (0);
	}
	mlx = ft_mlx_create();
	data = init_image(mlx, scene);
	if (data)
	{
		mlx_image_to_window(mlx, scene->img, 0, 0);
		loop(data, data->mlx);
	}
	mlx_terminate(mlx);
	free_all(data, scene);
	return (0);
}
