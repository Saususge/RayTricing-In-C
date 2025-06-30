/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:56:03 by chakim            #+#    #+#             */
/*   Updated: 2025/06/30 14:03:12 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"
#include "vector.h"
#include "rotate.h"
#include <math.h>
#include <unistd.h>

static t_object_ops g_cone_ops = {
	.intersect = cone_intersect,
	.shadow_intersect = cone_shadow_intersect,
	.get_normal = cone_get_normal,
	.rotate = cone_rotate,
	.translate = cone_translate,
};

static void calculate_cone_equation(t_quad_eq *eq, const t_cone *cone, const t_ray *ray)
{
	t_vec3 co = vec3_sub(ray->origin, cone->center);
	float cos2 = (cone->radius / cone->height) * (cone->radius / cone->height);
	float dv = vec3_dot(ray->dir, cone->axis);
	float cov = vec3_dot(co, cone->axis);

	eq->a = vec3_dot(ray->dir, ray->dir) - (1 + cos2) * dv * dv;
	eq->b = vec3_dot(ray->dir, co) - (1 + cos2) * dv * cov;
	eq->c = vec3_dot(co, co) - (1 + cos2) * cov * cov;
	eq->disc = eq->b * eq->b - eq->a * eq->c;
}

static int check_height_bounds(const t_cone *cone, t_point hit_point)
{
	t_vec3	center_to_hit = vec3_sub(hit_point, cone->center);
	float	projection = vec3_dot(center_to_hit, cone->axis);
	return (projection >= 0.0f && projection <= cone->height);
}

static int intersect_cap(const t_cone *cone, const t_ray *ray, t_point cap_center, float *t, t_t_bound bound)
{
	float denom = vec3_dot(ray->dir, cone->axis);
	if (fabs(denom) < EPSILON)
		return (0);
	t_vec3 oc = vec3_sub(cap_center, ray->origin);
	*t = vec3_dot(oc, cone->axis) / denom;
	if (*t < bound.min || *t > bound.max)
		return (0);
	t_point hit_point = vec3_add(ray->origin, vec3_mul(ray->dir, *t));
	t_vec3 cap_to_hit = vec3_sub(hit_point, cap_center);
	float dist_sq = vec3_dot(cap_to_hit, cap_to_hit);
	return (dist_sq <= cone->radius * cone->radius);
}

void cone_translate(t_object *this, t_vec3 offset)
{
	this->data.cone.center = vec3_add(this->data.cone.center, offset);
}

void cone_rotate(t_object *this, t_vec3 angle)
{
	this->data.cone.axis = rotate_vector(this->data.cone.axis, angle);
}

t_object create_cone(t_point center, t_vec3 axis, float radius, float height, t_vec3 color)
{
	return ((t_object){
		.type = 3,
		.ops = &g_cone_ops,
		.color = color,
		.data.cone = (t_cone){
			.center = center,
			.axis = axis,
			.radius = radius,
			.height = height,
		}
	});
}

int cone_intersect(const t_object *this, const t_ray *ray, t_hit *hit, t_t_bound bound)
{
	t_cone cone = this->data.cone;
	t_quad_eq eq;
	float t_min = INFINITY;
	float t_candidates[2];
	int candidate_count = 0;

	calculate_cone_equation(&eq, &cone, ray);
	if (eq.disc >= 0)
	{
		float sqrt_disc = sqrtf(eq.disc);
		float t1 = (-eq.b - sqrt_disc) / eq.a;
		float t2 = (-eq.b + sqrt_disc) / eq.a;
		t_point hit1 = vec3_add(ray->origin, vec3_mul(ray->dir, t1));
		t_point hit2 = vec3_add(ray->origin, vec3_mul(ray->dir, t2));
		if (t1 > bound.min && t1 < bound.max && check_height_bounds(&cone, hit1))
			t_candidates[candidate_count++] = t1;
		if (t2 > bound.min && t2 < bound.max && check_height_bounds(&cone, hit2))
			t_candidates[candidate_count++] = t2;
	}
	float t_cap;
	t_point cap_center = vec3_add(cone.center, vec3_mul(cone.axis, cone.height));
	if (intersect_cap(&cone, ray, cap_center, &t_cap, bound))
		t_candidates[candidate_count++] = t_cap;
	if (candidate_count == 0)
		return (0);
	for (int i = 0; i < candidate_count; i++)
	{
		if (t_candidates[i] < t_min)
			t_min = t_candidates[i];
	}
	populate_hit_record(hit, t_min, ray, this);
	return (1);
}

int cone_shadow_intersect(const t_object *this, const t_ray *ray, t_t_bound bound)
{
	t_cone cone = this->data.cone;
	t_quad_eq eq;

	calculate_cone_equation(&eq, &cone, ray);
	if (eq.disc >= 0)
	{
		float sqrt_disc = sqrtf(eq.disc);
		float t1 = (-eq.b - sqrt_disc) / eq.a;
		float t2 = (-eq.b + sqrt_disc) / eq.a;
		t_point hit1 = vec3_add(ray->origin, vec3_mul(ray->dir, t1));
		t_point hit2 = vec3_add(ray->origin, vec3_mul(ray->dir, t2));
		if (t1 > bound.min && t1 < bound.max && check_height_bounds(&cone, hit1))
			return (1);
		if (t2 > bound.min && t2 < bound.max && check_height_bounds(&cone, hit2))
			return (1);
	}
	float t_cap;
	t_point cap_center = vec3_add(cone.center, vec3_mul(cone.axis, cone.height));
	if (intersect_cap(&cone, ray, cap_center, &t_cap, bound))
		return (1);
	return (0);
}

t_vec3 cone_get_normal(const t_object *this, t_point *hit_point)
{
	t_cone cone = this->data.cone;
	t_vec3 center_to_hit = vec3_sub(*hit_point, cone.center);
	float projection = vec3_dot(center_to_hit, cone.axis);
	if (fabs(projection - cone.height) < EPSILON)
		return (cone.axis);
	t_vec3 axis_point = vec3_add(cone.center, vec3_mul(cone.axis, projection));
	t_vec3 normal = vec3_sub(*hit_point, axis_point);
	float m = cone.radius / cone.height;
	normal = vec3_sub(normal, vec3_mul(cone.axis, m * vec3_length(normal)));
	return vec3_normalize(normal);
}
