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

float convert_t_local_to_world(const t_object *obj, t_vec4 p_local, const t_ray *ray_world);

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

// int	shpere_shadow_intersect(const t_object *this, \
// 	const t_ray *ray, t_interval bound)
// {
// 	t_ray		local_ray;
// 	t_quad_eq	eq;
// 	float		t;
// 	float		sqrt_disc;

// 	local_ray.o = mat_mul_vec4(&this->m_inv, ray->o);
// 	local_ray.d = mat_mul_vec4(&this->m_inv, ray->d);
// 	calculate_sphere_equation(&eq, &local_ray);
// 	if (eq.disc < 0)
// 		return (0);
// 	sqrt_disc = sqrtf(eq.disc);
// 	t = -eq.b - sqrt_disc / eq.a;
// 	if (t < bound.min || t > bound.max)
// 	{
// 		t = -eq.b + sqrt_disc / eq.a;
// 		if (t < bound.min || t > bound.max)
// 			return (0);
// 	}
// 	return (1);
// }
