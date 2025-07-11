/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:00:00 by chakim            #+#    #+#             */
/*   Updated: 2025/07/01 15:00:00 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "vector.h"
#include "object.h"
#include <math.h>

static int	calculate_intersection_t(const t_ray *local_ray, \
	t_interval t_bound, float *t)
{
	t_quad_eq	eq;
	float		sqrt_disc;
	float		t1;
	float		t2;

	calculate_sphere_equation(&eq, local_ray);
	if (eq.disc < 0)
		return (0);
	sqrt_disc = sqrtf(eq.disc);
	t1 = (-eq.b - sqrt_disc) / eq.a;
	t2 = (-eq.b + sqrt_disc) / eq.a;
	if (t1 >= t_bound.min && t1 <= t_bound.max)
	{
		*t = t1;
		return (1);
	}
	if (t2 >= t_bound.min && t2 <= t_bound.max)
	{
		*t = t2;
		return (1);
	}
	return (0);
}

static void	fill_record(t_intersect *record, const t_object *obj,
	const t_ray *local_ray, float t)
{
	t_vec4	n_local;

	record->t = t;
	record->p_local = vec4_add(local_ray->o, vec4_mul(local_ray->d, t));
	n_local = sphere_get_normal(record->p_local);
	record->n_world = mat_mul_vec4(&obj->n, n_local);
	record->n_world.v[3] = 0.0f;
	record->n_world = vec4_mul(record->n_world, \
		1.0f / sqrtf(vec4_dot(record->n_world, record->n_world)));
	record->obj = (t_object *)obj;
}

int	sphere_intersect(const t_object *obj, const t_ray *ray_world, \
	t_intersect *record, t_interval t_bound)
{
	t_ray	local_ray;
	float	t;

	local_ray.o = mat_mul_vec4(&obj->m_inv, ray_world->o);
	local_ray.d = mat_mul_vec4(&obj->m_inv, ray_world->d);
	if (!calculate_intersection_t(&local_ray, t_bound, &t))
		return (0);
	fill_record(record, obj, &local_ray, t);
	if (vec4_dot(record->n_world, ray_world->d) > 0.0f)
		record->n_world = vec4_neg(record->n_world);
	return (1);
}
