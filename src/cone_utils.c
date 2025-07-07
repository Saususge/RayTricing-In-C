/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:00:00 by chakim            #+#    #+#             */
/*   Updated: 2025/07/07 20:04:34 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"
#include <math.h>

int	cone_lateral_intersect(const t_ray *ray, float *t, t_interval t_bound)
{
	t_quad_eq	eq;
	float		t1;
	float		t2;
	int			t1_valid;
	int			t2_valid;
	float		sqrt_disc;
	float		z1;
	float		z2;

	eq.a = ray->d.v[0] * ray->d.v[0] + ray->d.v[1] \
	* ray->d.v[1] - ray->d.v[2] * ray->d.v[2];
	eq.b = ray->o.v[0] * ray->d.v[0] + ray->o.v[1] \
	* ray->d.v[1] - ray->o.v[2] * ray->d.v[2];
	eq.c = ray->o.v[0] * ray->o.v[0] + ray->o.v[1] \
	* ray->o.v[1] - ray->o.v[2] * ray->o.v[2];
	eq.disc = eq.b * eq.b - eq.a * eq.c;
	if (eq.disc < 0 || fabs(eq.a) < EPSILON)
		return (0);
	sqrt_disc = sqrtf(eq.disc);
	t1 = (-eq.b - sqrt_disc) / eq.a;
	t2 = (-eq.b + sqrt_disc) / eq.a;
	z1 = ray->o.v[2] + ray->d.v[2] * t1;
	z2 = ray->o.v[2] + ray->d.v[2] * t2;
	t1_valid = (t1 >= t_bound.min && t1 <= t_bound.max && \
				z1 >= 0.0f && z1 <= 1.0f);
	t2_valid = (t2 >= t_bound.min && t2 <= t_bound.max && \
				z2 >= 0.0f && z2 <= 1.0f);
	if (t1_valid && (!t2_valid || t1 < t2))
		*t = t1;
	else if (t2_valid)
		*t = t2;
	else
		return (0);
	return (1);
}

int	cone_intersect_cap(const t_ray *ray, float *t, t_interval t_bound)
{
	float	t_cap;
	t_vec4	p_cap;

	if (fabs(ray->d.v[2]) < EPSILON)
		return (0);
	t_cap = (1.0f - ray->o.v[2]) / ray->d.v[2];
	if (t_cap < t_bound.min || t_cap > t_bound.max)
		return (0);
	p_cap = vec4_add(ray->o, vec4_mul(ray->d, t_cap));
	if (p_cap.v[0] * p_cap.v[0] + p_cap.v[1] * p_cap.v[1] > 1.0f)
		return (0);
	*t = t_cap;
	return (1);
}
