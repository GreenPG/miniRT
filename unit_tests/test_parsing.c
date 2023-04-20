/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:34:03 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/20 13:37:58 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../greatest/greatest.h"
#include "../includes/minirt.h"

TEST	ASSERT_VECTOR_EQ(t_vector *actual, t_vector *expected)
{
	ASSERT_EQ_FMT(expected->x_o, actual->x_o, "%f");
	ASSERT_EQ_FMT(expected->y_o, actual->y_o, "%f");
	ASSERT_EQ_FMT(expected->z_o, actual->z_o, "%f");
	ASSERT_EQ_FMT(expected->x_d, actual->x_d, "%f");
	ASSERT_EQ_FMT(expected->y_d, actual->y_d, "%f");
	ASSERT_EQ_FMT(expected->z_d, actual->z_d, "%f");
	PASS();
}

TEST	ASSERT_CAM_EQ(t_camera *actual, t_camera *expected)
{
	ASSERT_EQ_FMT(expected->fov, actual->fov, "%f");
	CHECK_CALL(ASSERT_VECTOR_EQ(actual->vector, expected->vector));
	PASS();
}

TEST	ASSERT_SPHERE_EQ(t_sphere *actual, t_sphere *expected)
{
	ASSERT_EQ_FMT(expected->pos->x, actual->pos->x, "%f");
	ASSERT_EQ_FMT(expected->pos->y, actual->pos->y, "%f");
	ASSERT_EQ_FMT(expected->pos->z, actual->pos->z, "%f");
	ASSERT_EQ_FMT(expected->diameter, actual->diameter, "%f");
	ASSERT_EQ_FMT(expected->color, actual->color, "%i");
	PASS();
}

TEST	ASSERT_PLANE_EQ(t_plane *actual, t_plane *expected)
{
	CHECK_CALL(ASSERT_VECTOR_EQ(actual->vector, expected->vector));
	ASSERT_EQ_FMT(expected->colors, actual->colors, "%i");
	PASS();
}

TEST	ASSERT_AMB_L_EQ(t_ambiant_l	*actual, t_ambiant_l *expected)
{
	ASSERT_EQ_FMT(expected->light_ratio, actual->light_ratio, "%f");
	ASSERT_EQ_FMT(expected->colors, actual->colors, "%i");
	PASS();
}

TEST	ASSERT_CYLINDER_EQ(t_cylinder *actual, t_cylinder *expected)
{
	CHECK_CALL(ASSERT_VECTOR_EQ(actual->vector, expected->vector));
	ASSERT_EQ_FMT(expected->diameter, actual->diameter, "%f");
	ASSERT_EQ_FMT(expected->height, actual->height, "%f");
	ASSERT_EQ_FMT(expected->color, actual->color, "%i");
	PASS();
}

TEST	ASSERT_SCENE_EQ(t_scene *actual, t_scene *expected)
{
	CHECK_CALL(ASSERT_AMB_L_EQ(actual->ambiant_l, expected->ambiant_l));
	CHECK_CALL(ASSERT_CAM_EQ(actual->camera, expected->camera));
	while (actual->obj_list)
	{
		ASSERT_EQ_FMT(expected->obj_list->type, actual->obj_list->type, "%i");
		if (actual->obj_list->type == sphere)
			CHECK_CALL(ASSERT_SPHERE_EQ((t_sphere *)actual->obj_list->obj, (t_sphere *)expected->obj_list->obj));
		else if (actual->obj_list->type == plane)
			CHECK_CALL(ASSERT_PLANE_EQ((t_plane *)actual->obj_list->obj, (t_plane *)expected->obj_list->obj));
		else if (actual->obj_list->type == cylinder)
			CHECK_CALL(ASSERT_CYLINDER_EQ((t_cylinder *)actual->obj_list->obj, (t_cylinder *)expected->obj_list->obj));
		actual->obj_list = actual->obj_list->next;
		expected->obj_list = expected->obj_list->next;
	}
	PASS();
}

TEST	correct_input(void) {
	t_scene	*scene1 = parsing("scenes/basic.rt");
	t_scene	*scene2 = parsing("scenes/unnecessary_lines.rt");
	t_scene	*expected = malloc(sizeof(t_scene));
	expected->ambiant_l = init_ambiant_l("A 0.2 255,255,255");
	expected->camera = init_camera("C -50,0,20 0,0,0 70");
	expected->obj_list = malloc(sizeof(t_obj_list));
	expected->obj_list->type = plane;
	expected->obj_list->obj = init_plane("pl 0,0,0 0,1.0,0 255,0,225");
	t_obj_list *tmp1 = malloc(sizeof(t_obj_list));
	tmp1->type = sphere;
	tmp1->obj = init_sphere("sp 0,0,20 20 255,0,0");
	expected->obj_list->next = tmp1;
	t_obj_list *tmp2 = malloc(sizeof(t_obj_list));
	tmp2->type = cylinder;
	tmp2->obj = init_cylinder("cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255");
	tmp2->next = NULL;
	tmp1->next = tmp2;


	CHECK_CALL(ASSERT_SCENE_EQ(scene1, expected));
	
	expected->obj_list = malloc(sizeof(t_obj_list));
	expected->obj_list->type = plane;
	expected->obj_list->obj = init_plane("pl 0,0,0 0,1.0,0 255,0,225");
	tmp1->type = sphere;
	tmp1->obj = init_sphere("sp 0,0,20 20 255,0,0");
	expected->obj_list->next = tmp1;
	tmp2->type = cylinder;
	tmp2->obj = init_cylinder("cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255");
	tmp2->next = NULL;
	tmp1->next = tmp2;
	CHECK_CALL(ASSERT_SCENE_EQ(scene2, expected));
	PASS();
}

TEST	wrong_path(void) {
	t_scene	*scene1 = parsing("test");
	t_scene	*scene2 = parsing(NULL);
	t_scene	*scene3 = parsing("test.yooooo");
	t_scene	*scene4 = parsing("test.rttt");

	ASSERT_EQ_FMT(NULL, scene1, "%p");
	ASSERT_EQ_FMT(NULL, scene2, "%p");
	ASSERT_EQ_FMT(NULL, scene3, "%p");
	ASSERT_EQ_FMT(NULL, scene4, "%p");
	PASS();
}

TEST	no_cam(void) {
	t_scene	*scene1 = parsing("scenes/wrong_scenes/no_camera.rt");

	ASSERT_EQ_FMT(NULL, scene1, "%p");
	PASS();
}

TEST	no_ambiant(void) {
	t_scene	*scene1 = parsing("scenes/wrong_scenes/no_ambiant.rt");

	ASSERT_EQ_FMT(NULL, scene1, "%p");
	PASS();
}

TEST	no_light(void) {
	t_scene	*scene1 = parsing("scenes/wrong_scenes/no_light.rt");

	ASSERT_EQ_FMT(NULL, scene1, "%p");
	PASS();
}

SUITE(test_parsing) {
	RUN_TEST(correct_input);
	RUN_TEST(wrong_path);
	RUN_TEST(no_cam);
	RUN_TEST(no_ambiant);
	RUN_TEST(no_light);
}
