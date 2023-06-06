/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_handle_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtouzali <gtouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 09:08:47 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/05 17:39:01 by gtouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	handle_rotation(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		world_rotate(data->scene, -7.2, 0);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		world_rotate(data->scene, 7.2, 0);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_RELEASE)
		world_rotate(data->scene, 0, 7.2);
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_RELEASE)
		world_rotate(data->scene, 0, -7.2);
}

static void	handle_translate(mlx_key_data_t keydata, t_data *data)
{
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
}

void	handle_keypress(mlx_key_data_t keydata, void *ptr)
{
	t_data	*data;

	data = ptr;
	handle_rotation(keydata, data);
	handle_translate(keydata, data);
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
	if (keydata.action == MLX_RELEASE)
		render(data->scene->img, data->scene);
}
