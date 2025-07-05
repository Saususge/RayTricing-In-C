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

int	sphere_intersect(const t_object *this, \
	const t_ray *ray, t_hit *hit, t_interval bound)
{
	t_quad_eq	eq;
	t_ray		local_ray;
	float		t;
	float		sqrt_disc;

	mat_mul_vec4(&this->m_inv, &ray->o, &local_ray.o);
	mat_mul_vec4(&this->m_inv, &ray->d, &local_ray.d);
	calculate_sphere_equation(&eq, &local_ray);
	if (eq.disc < 0)
		return (0);
	sqrt_disc = sqrtf(eq.disc);
	t = -eq.b - sqrt_disc / eq.a;
	if (t < bound.min || t > bound.max)
	{
		t = -eq.b + sqrt_disc / eq.a;
		if (t < bound.min || t > bound.max)
			return (0);
	}
	populate_hit_record(hit, t, ray, this);
	return (1);
}

int	shpere_shadow_intersect(const t_object *this, \
	const t_ray *ray, t_interval bound)
{
	t_ray		local_ray;
	t_quad_eq	eq;
	float		t;
	float		sqrt_disc;

	mat_mul_vec4(&this->m_inv, &ray->o, &local_ray.o);
	mat_mul_vec4(&this->m_inv, &ray->d, &local_ray.d);
	calculate_sphere_equation(&eq, &local_ray);
	if (eq.disc < 0)
		return (0);
	sqrt_disc = sqrtf(eq.disc);
	t = -eq.b - sqrt_disc / eq.a;
	if (t < bound.min || t > bound.max)
	{
		t = -eq.b + sqrt_disc / eq.a;
		if (t < bound.min || t > bound.max)
			return (0);
	}
	return (1);
}
