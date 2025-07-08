/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:56:47 by chakim            #+#    #+#             */
/*   Updated: 2025/07/08 16:22:06 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "vector.h"
#include "rotate.h"
#include <unistd.h>

static t_object_ops	g_cylinder_ops = {
	.intersect = cylinder_intersect,
	.get_color = cylinder_get_color,
};

static void	init_cylinder_basic(t_object *cyl, struct s_cyl_data data)
{
	cyl->type = CYLINDER;
	cyl->ops = &g_cylinder_ops;
	cyl->color = data.color;
	cyl->checkerboard = 0;
}

static void	init_transform_matrices(t_object *cyl, \
	t_point center, float radius, float height)
{
	cyl->t = (t_mat){{
	{1.0f, 0.0f, 0.0f, center.x},
	{0.0f, 1.0f, 0.0f, center.y},
	{0.0f, 0.0f, 1.0f, center.z},
	{0.0f, 0.0f, 0.0f, 1.0f}}};
	cyl->s = (t_mat){{
	{radius, 0.0f, 0.0f, 0.0f},
	{0.0f, radius, 0.0f, 0.0f},
	{0.0f, 0.0f, height, 0.0f},
	{0.0f, 0.0f, 0.0f, 1.0f}}};
}

static void	init_rotation_matrix(t_mat *r, t_vec3 axis)
{
	t_vec3	rotation_axis;
	float	angle;

	rotation_axis = vec3_cross((t_vec3){0, 0, 1}, axis);
	if (vec3_length(rotation_axis) < EPSILON)
	{
		if (axis.z > 0.0f)
			*r = (t_mat){{
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}}};
		else
			*r = (t_mat){{
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, -1.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, -1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}}};
	}
	else
	{
		rotation_axis = vec3_normalize(rotation_axis);
		angle = acosf(axis.z);
		rodrigues_to_mat4(rotation_axis, angle, r);
	}
}

static void	cy_compute_final_matrices(t_object *cyl)
{
	t_mat	temp;

	mat_mul_mat(&cyl->r, &cyl->s, &temp);
	mat_mul_mat(&cyl->t, &temp, &cyl->m);
	mat_inverse(&cyl->m, &cyl->m_inv);
	mat_transpose(&cyl->m_inv, &cyl->n);
}

t_object	create_cylinder(struct s_cyl_data data)
{
	t_object	cyl;

	init_cylinder_basic(&cyl, data);
	init_transform_matrices(&cyl, data.center, data.radius, data.height);
	init_rotation_matrix(&cyl.r, data.axis);
	cy_compute_final_matrices(&cyl);
	return (cyl);
}
