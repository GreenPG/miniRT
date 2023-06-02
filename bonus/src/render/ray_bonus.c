/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:22:26 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/02 08:59:26 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vector	calculate_ray_direction(unsigned int x, unsigned int y,
		t_camera *camera)
{
	t_vector	ray;

	ray.x = -tan(camera->fov / 2) + x * 2 * (tan(camera->fov / 2)
			/ (WIDTH - 1));
	ray.z = tan(camera->fov / 2) * (9. / 16.) - y * 2
		* (tan(camera->fov / 2) / (WIDTH - 1));
	ray.y = 1.;
	return (ray);
}

t_vector	ray_direction(unsigned int x, unsigned int y, t_camera camera)
{
	double		alpha;
	double		beta;
	t_vector	ray;

	alpha = (camera.fov / 2.) - x * (camera.fov / (WIDTH - 1));
	beta = (camera.fov / 2.) * (9. / 16.) - y * (camera.fov / (WIDTH - 1));
	ray.x = -sin(alpha) * cos(beta);
	ray.y = cos(alpha) * cos(beta);
	ray.z = sin(beta);
	return (ray);
}

void	free_rays(t_rays *ray_list)
{
	int	x;

	if (!ray_list || !ray_list->rays)
		return ;
	x = 0;
	while (x < WIDTH)
	{
		if (ray_list->rays[x])
			free(ray_list->rays[x]);
		x++;
	}
	free(ray_list->rays);
	free(ray_list);
}

static t_rays	*ray_loop(t_rays *ray_list, t_scene *scene)
{
	unsigned int	x;
	unsigned int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		ray_list->rays[x] = malloc(HEIGHT * sizeof(t_vector));
		if (!ray_list->rays[x])
		{
			free_rays(ray_list);
			return (0);
		}
		while (y < HEIGHT)
		{
			if (scene->camera->fov > 150 * (M_PI / 180))
				ray_list->rays[x][y] = ray_direction(x, y, *scene->camera);
			else
				ray_list->rays[x][y] = calculate_ray_direction(x, y,
						scene->camera);
			y++;
		}
		x++;
	}
	return (ray_list);
}

int	init_rays(t_scene *scene)
{
	t_rays			*ray_list;

	ray_list = malloc(sizeof(t_rays));
	if (!ray_list)
		return (0);
	ray_list->rays = malloc(WIDTH * sizeof(t_vector *));
	if (!ray_list->rays)
	{
		free(ray_list);
		return (0);
	}
	ray_list = ray_loop(ray_list, scene);
	scene->camera->rays = ray_list;
	return (1);
}
