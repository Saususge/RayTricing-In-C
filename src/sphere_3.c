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

void	populate_hit_record(t_hit *hit, float t, \
	const t_ray *ray, const t_object *this)
{
	t_vec3	amb;
	t_vec3	diff;
	t_vec3	spec;
	t_vec3	result;

	set_hit_geometry(hit, t, ray, this);
	amb = calc_ambient(this);
	diff.x = 0;
	diff.y = 0;
	diff.z = 0;
	spec.x = 0;
	spec.y = 0;
	spec.z = 0;
	calc_diff_spec(hit, &diff, &spec, this);
	result = vec3_add(vec3_add(amb, diff), spec);
	hit->color = clamp_color_vec3(result);
}

int	sphere_intersect(const t_object *this, \
	const t_ray *ray, t_hit *hit, t_t_bound bound)
{
	t_sphere	sph;
	t_quad_eq	eq;
	float		t;
	float		sqrt_disc;

	sph = this->data.sphere;
	calculate_sphere_equation(&eq, &sph, ray);
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
	const t_ray *ray, t_t_bound bound)
{
	t_sphere	sph;
	t_quad_eq	eq;
	float		t;
	float		sqrt_disc;

	sph = this->data.sphere;
	calculate_sphere_equation(&eq, &sph, ray);
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
