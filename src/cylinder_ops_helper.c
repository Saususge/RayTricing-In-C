/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_ops_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:01:46 by chakim            #+#    #+#             */
/*   Updated: 2025/07/04 18:08:55 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "vector.h"
#include "rotate.h"
#include <unistd.h>

void	calculate_cylinder_equation(t_quad_eq *eq, \
	const t_cylinder *cyl, const t_ray *ray)
{
	t_point	p1;
	t_vec3	delta_p;
	t_vec3	v_cross_axis;
	t_vec3	dp_cross_axis;

	p1 = vec3_sub(cyl->center, vec3_mul(cyl->axis, cyl->height * 0.5f));
	delta_p = vec3_sub(ray->origin, p1);
	v_cross_axis = vec3_cross(ray->dir, cyl->axis);
	dp_cross_axis = vec3_cross(delta_p, cyl->axis);
	eq->a = vec3_dot(v_cross_axis, v_cross_axis);
	eq->b = vec3_dot(v_cross_axis, dp_cross_axis);
	eq->c = vec3_dot(dp_cross_axis, dp_cross_axis) - \
	(cyl->radius * cyl->radius);
	eq->disc = eq->b * eq->b - eq->a * eq->c;
}

int	check_in_circle(const t_cylinder *cyl, \
	const t_ray *ray, t_point cap_center, float t)
{
	t_point	hit_point;
	t_vec3	cap_to_hit;
	float	dist_sq;

	hit_point = vec3_add(ray->origin, vec3_mul(ray->dir, t));
	cap_to_hit = vec3_sub(hit_point, cap_center);
	dist_sq = vec3_dot(cap_to_hit, cap_to_hit);
	return (dist_sq <= cyl->radius * cyl->radius);
}

int	intersect_cap(const t_cylinder *cyl, const t_ray *ray, \
	float *t, t_t_bound bound)
{
	float	t1;
	float	t2;
	float	denom;
	int		valid1;
	int		valid2;

	t1 = 0.0f;
	t2 = 0.0f;
	denom = vec3_dot(ray->dir, cyl->axis);
	if (fabs(denom) < EPSILON)
		return (0);
	t1 = vec3_dot(vec3_sub(cyl->p1, ray->origin), cyl->axis) / denom;
	t2 = vec3_dot(vec3_sub(cyl->p2, ray->origin), cyl->axis) / denom;
	valid1 = (t1 >= bound.min && t1 <= bound.max && \
		check_in_circle(cyl, ray, cyl->p1, t1));
	valid2 = (t2 >= bound.min && t2 <= bound.max && \
		check_in_circle(cyl, ray, cyl->p2, t2));
	if (!valid1 && !valid2)
		return (0);
	if (valid1 && (!valid2 || t1 < t2))
		*t = t1;
	else
		*t = t2;
	return (1);
}

int	check_height(const t_cylinder *cyl, t_point hit_point)
{
	t_vec3	p1_to_hit;
	float	projection;

	p1_to_hit = vec3_sub(hit_point, cyl->p1);
	projection = vec3_dot(p1_to_hit, cyl->axis);
	return (projection >= 0.0f && projection <= cyl->height);
}

int	intersect_lateral(const t_cylinder *cyl, \
	const t_ray *ray, float *t, t_t_bound bound)
{
	t_quad_eq	eq;
	float		t_temp;
	float		sqrt_disc;
	t_point		hit_point;

	calculate_cylinder_equation(&eq, cyl, ray);
	if (eq.disc < 0)
		return (0);
	sqrt_disc = sqrtf(eq.disc);
	t_temp = (-eq.b - sqrt_disc) / (eq.a);
	hit_point = vec3_add(ray->origin, vec3_mul(ray->dir, t_temp));
	if (t_temp < bound.min || t_temp > bound.max || \
		!check_height(cyl, hit_point))
	{
		t_temp = (-eq.b + sqrt_disc) / (eq.a);
		hit_point = vec3_add(ray->origin, vec3_mul(ray->dir, t_temp));
		if (t_temp < bound.min || t_temp > bound.max || \
			!check_height(cyl, hit_point))
			return (0);
	}
	*t = t_temp;
	return (1);
}
