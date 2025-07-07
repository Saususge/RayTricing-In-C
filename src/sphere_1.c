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

int	sphere_intersect(const t_object *obj, const t_ray *ray_world, t_intersect *record, t_interval t_bound)
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
	t1_valid = (t1 >= t_bound.min && t1 <= t_bound.max);
	t2_valid = (t2 >= t_bound.min && t2 <= t_bound.max);
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
	record->n_world = mat_mul_vec4(&obj->m, sphere_get_normal(record->p_local));
	record->n_world = vec4_mul(record->n_world, 1.0f / sqrt(vec4_dot(record->n_world, record->n_world)));
	if (vec4_dot(record->n_world, ray_world->d) > 0.0f)
		record->n_world = vec4_neg(record->n_world);
	record->obj = (t_object *)obj;
	return (1);
}
