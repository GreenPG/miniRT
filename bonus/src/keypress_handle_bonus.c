/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_handle_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 09:08:47 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/09 17:19:50 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static int	handle_rotation(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		world_rotate(data->scene, -7.2, 0, 0);
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		world_rotate(data->scene, 7.2, 0, 0);
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_RELEASE)
		world_rotate(data->scene, 0, 7.2, 0);
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_RELEASE)
		world_rotate(data->scene, 0, -7.2, 0);
	else if (keydata.key == MLX_KEY_Q && keydata.action == MLX_RELEASE)
		world_rotate(data->scene, 0, 0, 7.2);
	else if (keydata.key == MLX_KEY_E && keydata.action == MLX_RELEASE)
		world_rotate(data->scene, 0, 0, -7.2);
	else
		return (0);
	return (1);
}

static int	handle_translate(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		world_translate(data->scene, 0, -1, 0);
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		world_translate(data->scene, 1, 0, 0);
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		world_translate(data->scene, 0, 1, 0);
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		world_translate(data->scene, -1, 0, 0);
	else if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_RELEASE)
		world_translate(data->scene, 0, 0, -1);
	else if (keydata.key == MLX_KEY_LEFT_SHIFT && keydata.action == MLX_RELEASE)
		world_translate(data->scene, 0, 0, 1);
	else
		return (0);
	return (1);
}

static int	handle_object_rotate(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_I && keydata.action == MLX_RELEASE)
		rotate_one(data->scene->obj_selected, 0, 1, 0);
	else if (keydata.key == MLX_KEY_K && keydata.action == MLX_RELEASE)
		rotate_one(data->scene->obj_selected, 0, -1, 0);
	else if (keydata.key == MLX_KEY_J && keydata.action == MLX_RELEASE)
		rotate_one(data->scene->obj_selected, 1, 0, 0);
	else if (keydata.key == MLX_KEY_L && keydata.action == MLX_RELEASE)
		rotate_one(data->scene->obj_selected, -1, 0, 0);
	else if (keydata.key == MLX_KEY_U && keydata.action == MLX_RELEASE)
		rotate_one(data->scene->obj_selected, 0, 0, 1);
	else if (keydata.key == MLX_KEY_O && keydata.action == MLX_RELEASE)
		rotate_one(data->scene->obj_selected, 0, 0, -1);
	else
		return (0);
	return (1);
}

static int	handle_object_move(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_KP_8 && keydata.action == MLX_RELEASE)
		move_one(data->scene->obj_selected, 0, 1, 0);
	else if (keydata.key == MLX_KEY_KP_2 && keydata.action == MLX_RELEASE)
		move_one(data->scene->obj_selected, 0, -1, 0);
	else if (keydata.key == MLX_KEY_KP_6 && keydata.action == MLX_RELEASE)
		move_one(data->scene->obj_selected, 1, 0, 0);
	else if (keydata.key == MLX_KEY_KP_4 && keydata.action == MLX_RELEASE)
		move_one(data->scene->obj_selected, -1, 0, 0);
	else if (keydata.key == MLX_KEY_KP_SUBTRACT && keydata.action == MLX_RELEASE)
		move_one(data->scene->obj_selected, 0, 0, 1);
	else if (keydata.key == MLX_KEY_KP_ADD && keydata.action == MLX_RELEASE)
		move_one(data->scene->obj_selected, 0, 0, -1);
	else
		return (0);
	return (1);
}

void	handle_keypress(mlx_key_data_t keydata, void *ptr)
{
	t_data	*data;
	int		has_changed;

	has_changed = 0;
	data = ptr;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
	{
		mlx_close_window(data->mlx);
		return ;
	}
	has_changed += handle_rotation(keydata, data);
	has_changed += handle_translate(keydata, data);
	has_changed += handle_object_rotate(keydata, data);
	has_changed += handle_object_move(keydata, data);
	if (has_changed != 0)
		render(data->scene->img, data->scene);
}
