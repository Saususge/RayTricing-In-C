/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:12:52 by chakim            #+#    #+#             */
/*   Updated: 2025/07/06 20:55:59 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"
#include "unistd.h"
#include "vector.h"
#include <stdlib.h>
#include "rotate.h"

static t_object_ops	g_plane_ops = {
	.intersect = plane_intersect,
	.get_normal = plane_get_normal,
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
		axis = (t_vec3){0, 0, 1};
	axis = vec3_normalize(axis);
	theta = acosf(axis.z);
	rodrigues_to_mat4(axis, theta, &pl.r);
	pl.s = (t_mat){{{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1}}};
	mat_mul_mat(&pl.r, &pl.s, &temp);
	mat_mul_mat(&pl.t, &temp, &pl.m);
	mat_inverse(&pl.m, &pl.m_inv);
	return (pl);
}

int	sphere_intersect(const t_object *obj, const t_ray *ray_world, t_intersect *record, t_interval t_world_bound)
{
	t_quad_eq	eq;
	t_ray		local_ray;
	float		t1;
	float		t2;
	int			t1_valid;
	int			t2_valid;
	float		sqrt_disc;

	local_ray.o = mat_mul_vec4(&obj->m_inv, ray_world->o);
	local_ray.d = mat_mul_vec4(&obj->m_inv, ray_world->d);
	calculate_sphere_equation(&eq, &local_ray);
	if (eq.disc < 0)
		return (0);
	sqrt_disc = sqrtf(eq.disc);
	t1 = (-eq.b - sqrt_disc) / eq.a;
	t2 = (-eq.b + sqrt_disc) / eq.a;
	t1_valid = (t1 >= t_world_bound.min && t1 <= t_world_bound.max);
	t2_valid = (t2 >= t_world_bound.min && t2 <= t_world_bound.max);
	if (t1_valid && (!t2_valid || t1 < t2))
	{
		record->t = t1;
		record->p_local = vec4_add(local_ray.o, vec4_mul(local_ray.d, t1));
	}
	else if (t2_valid)
	{
		record->t = t2;
		record->p_local = vec4_add(local_ray.o, vec4_mul(local_ray.d, t2));
	}
	else
		return (0);
	record->obj = (t_object *)obj;
	return (1);
}

int	plane_intersect(const t_object *obj, const t_ray *ray_world, t_intersect *intersect_record, t_interval t_world_bound)
{
	t_ray	ray_local;
	float	t;

	ray_local.o = mat_mul_vec4(&obj->m_inv, ray_world->o);
	ray_local.d = mat_mul_vec4(&obj->m_inv, ray_world->d);
	if (fabs(ray_local.d.v[2]) < EPSILON)
	return (1);
}

int	plane_shadow_intersect(const t_object *this, \
	const t_ray *ray, t_interval bound)
{
	t_plane	pl;	
	float	denominator;
	float	t;
	t_vec3	p0_to_l0;

	pl = this->data.plane;
	p0_to_l0 = vec3_sub(pl.point, ray->o);
	denominator = vec3_dot(ray->d, pl.normal);
	if (fabs(denominator) < EPSILON)
		return (0);
	t = vec3_dot(p0_to_l0, pl.normal) / denominator;
	if (t < bound.min || t > bound.max)
		return (0);
	return (1);
}
