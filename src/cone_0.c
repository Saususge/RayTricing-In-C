/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:56:03 by chakim            #+#    #+#             */
/*   Updated: 2025/07/08 15:52:35 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"
#include "vector.h"
#include "rotate.h"
#include <math.h>
#include <unistd.h>

static t_object_ops	g_cone_ops = {
	.intersect = cone_intersect,
	.get_color = cone_get_color,
};

static void	init_cone_basic(t_object *cn, struct s_cone_data data)
{
	cn->type = CONE;
	cn->ops = &g_cone_ops;
	cn->color = data.color;
	cn->checkerboard = 0;
}

static void	init_transform_matrices(t_object *cn, \
	t_point center, float radius, float height)
{
	cn->t = (t_mat){{
	{1.0f, 0.0f, 0.0f, center.x},
	{0.0f, 1.0f, 0.0f, center.y},
	{0.0f, 0.0f, 1.0f, center.z},
	{0.0f, 0.0f, 0.0f, 1.0f}}};
	cn->s = (t_mat){{
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

static void	co_compute_final_matrices(t_object *cn)
{
	t_mat	temp;

	mat_mul_mat(&cn->r, &cn->s, &temp);
	mat_mul_mat(&cn->t, &temp, &cn->m);
	mat_inverse(&cn->m, &cn->m_inv);
	mat_transpose(&cn->m_inv, &cn->n);
}

t_object	create_cone(struct s_cone_data data)
{
	t_object	cn;

	init_cone_basic(&cn, data);
	init_transform_matrices(&cn, data.center, data.radius, data.height);
	init_rotation_matrix(&cn.r, data.axis);
	co_compute_final_matrices(&cn);
	return (cn);
}
