/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 07:45:59 by gtouzali          #+#    #+#             */
/*   Updated: 2023/05/13 18:21:55 by gtouzali         ###   ########.fr       */
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

static void    sphere_translate(t_sphere *sphere, double x, double y, double z)
{
    sphere->origin->x += x;
    sphere->origin->y += y;
    sphere->origin->z += z;
}

static void    plane_translate(t_plane *plane, double x, double y, double z)
{
    plane->origin->x += x;
    plane->origin->y += y;
    plane->origin->z += z;
}

static void    cylinder_translate(t_cylinder *cylinder, double x, double y, double z)
{
    cylinder->origin->x += x;
    cylinder->origin->y += y;
    cylinder->origin->z += z;
}


void	move_one(t_obj_list *nearest, double x, double y, double z)
{
	if (!nearest)
		return ;
	if (nearest->type == sphere)
		sphere_translate(nearest->sphere, x, y, z);
	else if (nearest->type == cylinder)
		cylinder_translate(nearest->cylinder, x, y, z);
	else if (nearest->type == plane)
		plane_translate(nearest->plane, x, y, z);
}

void handle_keypress(mlx_key_data_t keydata, void* ptr)
{
	t_data	*data;

	data = ptr;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		world_rotate(data->scene, -7.2, 0);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		world_rotate(data->scene, 7.2, 0);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_RELEASE)
		world_rotate(data->scene, 0, 7.2);
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_RELEASE)
		world_rotate(data->scene, 0, -7.2);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		world_translate(data->scene, 0, -1, 0);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		world_translate(data->scene, 1, 0, 0);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		world_translate(data->scene, 0, 1, 0);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		world_translate(data->scene, -1, 0, 0);
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_RELEASE)
		world_translate(data->scene, 0, 0, -1);
	if (keydata.key == MLX_KEY_LEFT_SHIFT && keydata.action == MLX_RELEASE)
		world_translate(data->scene, 0, 0, 1);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
	{
		mlx_close_window(data->mlx);
		return ;
	}
	if (keydata.key == MLX_KEY_KP_8 && keydata.action == MLX_RELEASE)
		move_one(data->scene->obj_selected, 0, 1, 0);
	if (keydata.key == MLX_KEY_KP_2 && keydata.action == MLX_RELEASE)
		move_one(data->scene->obj_selected, 0, -1, 0);
	if (keydata.key == MLX_KEY_KP_6 && keydata.action == MLX_RELEASE)
		move_one(data->scene->obj_selected, 1, 0, 0);
	if (keydata.key == MLX_KEY_KP_4 && keydata.action == MLX_RELEASE)
		move_one(data->scene->obj_selected, -1, 0, 0);
	if (keydata.key == MLX_KEY_KP_SUBTRACT && keydata.action == MLX_RELEASE)
		move_one(data->scene->obj_selected, 0, 0, 1);
	if (keydata.key == MLX_KEY_KP_ADD && keydata.action == MLX_RELEASE)
		move_one(data->scene->obj_selected, 0, 0, -1);
	render(data->scene->img, data->scene);
}

t_obj_list	*get_click_obj(t_vector ray, t_scene *scene)
{
	t_obj_list	*cursor;
	t_obj_list	*nearest;
	double		nearest_distance;
	double		current_distance;

	nearest = NULL;
	nearest_distance = INFINITY;
	cursor = scene->obj_list;
	scene->obj_selected = NULL;
	while (cursor)
	{
		current_distance = INFINITY;
		if (cursor->type == sphere)
			current_distance = sphere_hit(cursor->sphere, ray);
		else if (cursor->type == cylinder)
			current_distance = cylinder_hit(cursor->cylinder, ray);
		else if (cursor->type == plane)
			current_distance = plane_hit(cursor->plane, ray);
		if (current_distance < nearest_distance)
		{
			nearest = cursor;	
			nearest_distance = current_distance;
		}
		cursor = cursor->next;
	}
	if (nearest == NULL)
		return (scene->obj_selected);
	return (nearest);
}

void	mouse_handle(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	int x;
	int	y;
	t_data	*data;

	data = param;
	if(button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
	{
		mlx_get_mouse_pos(data->mlx, &x, &y);
		x = x * ((double)WIDTH / (double)data->mlx->width);
		y = y * ((double)HEIGHT / (double)data->mlx->height);
		data->scene->obj_selected = get_click_obj(data->scene->camera->rays->rays[x][y], data->scene);
	}
	(void)button;
	(void)action;
	(void)mods;
	(void)param;


}

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		*scene;
	t_data		*data;
	
	if (argc != 2)
		return (ft_error("Error: expected usage is ./miniRT <path to .rt file>\n"));
	(void)argv;
	scene = parsing(argv[1]);
	if (!scene)
	{
		ft_error("ERROR\n");
		return (0);
	}
	mlx = ft_mlx_create();
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	init_rays(scene);
	world_translate(scene, -scene->camera->origin->x, -scene->camera->origin->y, -scene->camera->origin->z);
	world_rotate(scene, scene->camera->alpha, scene->camera->beta);
	render(img, scene);
	scene->img = img;
	data = malloc(sizeof(t_data));
	if (!data)
	{
		ft_error("ERROR\n");
		return (1);
	}
	data->mlx = mlx;
	data->scene = scene;
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_mouse_hook(data->mlx, mouse_handle, data);
	mlx_key_hook(mlx, &handle_keypress, data);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_scene(&scene);
	free(data);
	return (0);
}