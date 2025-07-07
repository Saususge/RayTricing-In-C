/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:56:47 by chakim            #+#    #+#             */
/*   Updated: 2025/07/07 15:51:17 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "vector.h"
#include "rotate.h"
#include <unistd.h>

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

static int	intersect_lateral(const t_ray *local_ray, t_interval bound, float *t)
{
	t_quad_eq	eq;
	float		t1;
	float		t2;
	int			t1_valid;
	int			t2_valid;
	float		sqrt_disc;

	calculate_lateral_equation(&eq, local_ray);
	if (eq.disc < 0)
		return (0);
	sqrt_disc = sqrtf(eq.disc);
	t1 = (-eq.b - sqrt_disc) / eq.a;
	t2 = (-eq.b + sqrt_disc) / eq.a;
	t1_valid = (t1 >= bound.min && t1 <= bound.max && fabs(vec4_add(local_ray->o, vec4_mul(local_ray->d, t1)).v[2]) <= 0.5f);
	t2_valid = (t2 >= bound.min && t2 <= bound.max && fabs(vec4_add(local_ray->o, vec4_mul(local_ray->d, t2)).v[2]) <= 0.5f);
	if (t1_valid && (!t2_valid || t1 < t2))
		*t = t1;
	else if (t2_valid)
		*t = t2;
	else
		return (0);
	return (1);
}

static int	intersect_cap(const t_ray *local_ray, t_interval bound, float *t)
{
	float	t1;
	float	t2;
	int		valid1;
	int		valid2;
	t_vec4	p1;
	t_vec4	p2;

	if (fabs(local_ray->d.v[2]) < EPSILON)
		return (0);
	t1 = (-0.5 - local_ray->o.v[2]) / local_ray->d.v[2];
	t2 = (0.5 - local_ray->o.v[2]) / local_ray->d.v[2];
	p1 = vec4_add(local_ray->o, vec4_mul(local_ray->d, t1));
	p2 = vec4_add(local_ray->o, vec4_mul(local_ray->d, t2));
	valid1 = (t1 >= bound.min && t1 <= bound.max && p1.v[0] * p1.v[0] + p1.v[1] * p1.v[1] <= 1.0f);
	valid2 = (t2 >= bound.min && t2 <= bound.max && p2.v[0] * p2.v[0] + p2.v[1] * p2.v[1] <= 1.0f);
	if (valid1 && (!valid2 || t1 < t2))
		*t = t1;
	else if (valid2)
		*t = t2;
	else
		return (0);
	return (1);
}

static t_vec4	cylinder_get_normal(t_vec4 p_local)
{
	if (fabs(p_local.v[2] - 0.5f) < EPSILON)
		return ((t_vec4){{0.0f, 0.0f, 1.0f, 0.0f}});
	else if (fabs(p_local.v[2] + 0.5f) < EPSILON)
		return ((t_vec4){{0.0f, 0.0f, -1.0f, 0.0f}});
	else
		return ((t_vec4){{p_local.v[0], p_local.v[1], 0.0f, 0.0f}});
}

int	cylinder_intersect(const t_object *obj, const t_ray *ray_world, t_intersect *record, t_interval t_bound)
{
	t_ray	local_ray;
	int		lateral_hit;
	int		cap_hit;
	float	t;

	local_ray.o = mat_mul_vec4(&obj->m_inv, ray_world->o);
	local_ray.d = mat_mul_vec4(&obj->m_inv, ray_world->d);
	lateral_hit = intersect_lateral(&local_ray, t_bound, &t);
	if (lateral_hit)
		cap_hit = intersect_cap(&local_ray, (t_interval){t_bound.min, t}, &t);
	else
		cap_hit = intersect_cap(&local_ray, t_bound, &t);
	if (!lateral_hit && !cap_hit)
		return (0);
	record->t = t;
	record->p_local = vec4_add(local_ray.o, vec4_mul(local_ray.d, t));
	record->n_local = cylinder_get_normal(record->p_local);
	if (vec4_dot(record->n_local, local_ray.d) > 0.0f)
		record->n_local = vec4_neg(record->n_local);
	record->obj = (t_object *)obj;
	return (1);
}
