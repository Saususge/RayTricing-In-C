/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:12:52 by chakim            #+#    #+#             */
/*   Updated: 2025/07/07 23:18:16 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"
#include "unistd.h"
#include "vector.h"
#include <stdlib.h>
#include "rotate.h"

static t_object_ops	g_plane_ops = {
	.intersect = plane_intersect,
	.get_color = plane_get_color,
};

// Assume that the plane normal is 0,0,1 and the plane is at the origin in
// local space. The point is the position of the plane in world space.
// The normal is the direction of the plane in world space.
t_object	create_plane(t_point point, t_vec3 normal, t_vec3 color)
{
	t_object	pl;
	t_mat		temp;
	t_vec3		axis;
	float		theta;

	pl.type = PLANE;
	pl.ops = &g_plane_ops;
	pl.color = color;
	pl.checkerboard = 0;
	pl.t = (t_mat){{{1, 0, 0, point.x},
	{0, 1, 0, point.y},
	{0, 0, 1, point.z},
	{0, 0, 0, 1}}};
	axis = vec3_cross((t_vec3){0, 0, 1}, normal);
	if (vec3_length(axis) < EPSILON)
	{
		if (normal.z > 0.0f)
			pl.r = (t_mat){{
				{1.0f, 0.0f, 0.0f, 0.0f},
				{0.0f, 1.0f, 0.0f, 0.0f},
				{0.0f, 0.0f, 1.0f, 0.0f},
				{0.0f, 0.0f, 0.0f, 1.0f}}};
		else
			pl.r = (t_mat){{
				{1.0f, 0.0f, 0.0f, 0.0f},
				{0.0f, -1.0f, 0.0f, 0.0f},
				{0.0f, 0.0f, -1.0f, 0.0f},
				{0.0f, 0.0f, 0.0f, 1.0f}}};
	}
	else
	{
		axis = vec3_normalize(axis);
		theta = acosf(normal.z);
		rodrigues_to_mat4(axis, theta, &pl.r);
	}
	pl.s = (t_mat){{{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1}}};
	mat_mul_mat(&pl.r, &pl.s, &temp);
	mat_mul_mat(&pl.t, &temp, &pl.m);
	mat_inverse(&pl.m, &pl.m_inv);
	return (pl);
}

int	plane_intersect(const t_object *obj, const t_ray *ray_world, t_intersect *record, t_interval t_bound)
{
	t_ray	ray_local;
	float	t;

	ray_local.o = mat_mul_vec4(&obj->m_inv, ray_world->o);
	ray_local.d = mat_mul_vec4(&obj->m_inv, ray_world->d);
	if (fabs(ray_local.d.v[2]) < EPSILON)
		return (0);
	t = - ray_local.o.v[2] / ray_local.d.v[2];
	if (t < t_bound.min || t > t_bound.max)
		return (0);
	record->t = t;
	record->p_local = vec4_add(ray_local.o, vec4_mul(ray_local.d, t));
	record->n_world = mat_mul_vec4(&obj->m, plane_get_normal(obj, record->p_local));
	record->n_world = vec4_mul(record->n_world, 1.0f / sqrt(vec4_dot(record->n_world, record->n_world)));
	if (vec4_dot(record->n_world, ray_world->d) > 0.0f)
		record->n_world = vec4_neg(record->n_world);
	record->obj = (t_object *)obj;
	return (1);
}

