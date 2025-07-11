/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:46:00 by chakim            #+#    #+#             */
/*   Updated: 2025/07/08 16:36:38 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "vector.h"
#include <math.h>

static void	calculate_lateral_equation(t_quad_eq *eq, const t_ray *local_ray)
{
	float	dx;
	float	dy;
	float	ox;
	float	oy;

	dx = local_ray->d.v[0];
	dy = local_ray->d.v[1];
	ox = local_ray->o.v[0];
	oy = local_ray->o.v[1];
	eq->a = dx * dx + dy * dy;
	eq->b = dx * ox + dy * oy;
	eq->c = ox * ox + oy * oy - 1.0f;
	eq->disc = eq->b * eq->b - eq->a * eq->c;
}

static int	is_valid_cap_intersection(const t_ray *ray, \
	float t, t_interval bound)
{
	t_vec4	p;

	if (t < bound.min || t > bound.max)
		return (0);
	p = vec4_add(ray->o, vec4_mul(ray->d, t));
	return (p.v[0] * p.v[0] + p.v[1] * p.v[1] <= 1.0f);
}

int	check_cylinder_height(const t_ray *ray, float t)
{
	t_vec4	point;

	point = vec4_add(ray->o, vec4_mul(ray->d, t));
	return (fabsf(point.v[2]) <= 0.5f);
}

int	intersect_lateral(const t_ray *local_ray, t_interval bound, float *t)
{
	t_quad_eq	eq;
	float		t1;
	float		t2;
	float		sqrt_disc;

	calculate_lateral_equation(&eq, local_ray);
	if (eq.disc < 0)
		return (0);
	sqrt_disc = sqrtf(eq.disc);
	t1 = (-eq.b - sqrt_disc) / eq.a;
	t2 = (-eq.b + sqrt_disc) / eq.a;
	if (t1 >= bound.min && t1 <= bound.max && \
		check_cylinder_height(local_ray, t1))
		*t = t1;
	else if (t2 >= bound.min && t2 <= bound.max && \
		check_cylinder_height(local_ray, t2))
		*t = t2;
	else
		return (0);
	return (1);
}

int	intersect_cap(const t_ray *local_ray, t_interval bound, float *t)
{
	float	t1;
	float	t2;
	int		valid1;
	int		valid2;

	if (fabsf(local_ray->d.v[2]) < EPSILON)
		return (0);
	t1 = (-0.5 - local_ray->o.v[2]) / local_ray->d.v[2];
	t2 = (0.5 - local_ray->o.v[2]) / local_ray->d.v[2];
	valid1 = is_valid_cap_intersection(local_ray, t1, bound);
	valid2 = is_valid_cap_intersection(local_ray, t2, bound);
	if (valid1 && (!valid2 || t1 < t2))
		*t = t1;
	else if (valid2)
		*t = t2;
	else
		return (0);
	return (1);
}
