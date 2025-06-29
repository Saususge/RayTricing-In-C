/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:56:47 by chakim            #+#    #+#             */
/*   Updated: 2025/06/30 04:10:29 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "vector.h"
#include <unistd.h>

static void calculate_cylinder_equation(t_quad_eq *eq, const t_cylinder *cyl, const t_ray *ray);
static int check_height_bounds(const t_cylinder *cyl, t_point hit_point);
static int intersect_cap(const t_cylinder *cyl, const t_ray *ray, t_point cap_center, float *t, t_t_bound bound);
int cylinder_intersect(const t_object *this, const t_ray *ray, t_hit *hit, t_t_bound bound);
int cylinder_shadow_intersect(const t_object *this, const t_ray *ray, t_t_bound bound);
t_vec3 cylinder_get_normal(const t_object *this, t_point *hit_point);

static t_object_ops	g_cylinder_ops = {
	.intersect = cylinder_intersect,
	.shadow_intersect = cylinder_shadow_intersect,
	.get_normal = cylinder_get_normal,
	.rotate = NULL,
	.translate = NULL,
};

t_object	create_cylinder(t_point p1, t_point p2, float radius, t_vec3 color)
{
	return ((t_object){
		.type = CYLINDER,
		.ops = &g_cylinder_ops,
		.color = color,
		.data.cylinder = (t_cylinder){
		.p1 = p1,
		.p2 = p2,
		.axis = vec3_normalize(vec3_sub(p2, p1)),
		.radius = radius,
		.height = vec3_length(vec3_sub(p2, p1)),
	}
	});
}

static void calculate_cylinder_equation(t_quad_eq *eq, const t_cylinder *cyl, const t_ray *ray)
{
	t_vec3 delta_p = vec3_sub(ray->origin, cyl->p1);
	t_vec3 v_cross_axis = vec3_cross(ray->direction, cyl->axis);
	t_vec3 dp_cross_axis = vec3_cross(delta_p, cyl->axis);
	
	eq->a = vec3_dot(v_cross_axis, v_cross_axis);
	eq->b = 2.0f * vec3_dot(v_cross_axis, dp_cross_axis);
	eq->c = vec3_dot(dp_cross_axis, dp_cross_axis) - (cyl->radius * cyl->radius);
	eq->disc = eq->b * eq->b - 4.0f * eq->a * eq->c;
}

static int check_height_bounds(const t_cylinder *cyl, t_point hit_point)
{
	t_vec3 p1_to_hit = vec3_sub(hit_point, cyl->p1);
	float projection = vec3_dot(p1_to_hit, cyl->axis);
	return (projection >= 0.0f && projection <= cyl->height);
}

static int intersect_cap(const t_cylinder *cyl, const t_ray *ray, t_point cap_center, float *t, t_t_bound bound)
{
	float denom = vec3_dot(ray->direction, cyl->axis);
	if (fabs(denom) < EPSILON)
		return (0);
	t_vec3 oc = vec3_sub(cap_center, ray->origin);
	*t = vec3_dot(oc, cyl->axis) / denom;
	
	if (*t < bound.min || *t > bound.max)
		return (0);
	t_point hit_point = vec3_add(ray->origin, vec3_mul(ray->direction, *t));
	t_vec3 cap_to_hit = vec3_sub(hit_point, cap_center);
	float dist_sq = vec3_dot(cap_to_hit, cap_to_hit);
	
	return (dist_sq <= cyl->radius * cyl->radius);
}

int cylinder_intersect(const t_object *this, const t_ray *ray, t_hit *hit, t_t_bound bound)
{
	t_cylinder cyl = this->data.cylinder;
	t_quad_eq eq;
	float t_min = INFINITY;
	float t_candidates[4];
	int candidate_count = 0;

	calculate_cylinder_equation(&eq, &cyl, ray);
	if (eq.disc >= 0)
	{
		float sqrt_disc = sqrtf(eq.disc);
		float t1 = (-eq.b - sqrt_disc) / (2.0f * eq.a);
		float t2 = (-eq.b + sqrt_disc) / (2.0f * eq.a);
		if (t1 >= bound.min && t1 <= bound.max)
		{
			t_point hit_point = vec3_add(ray->origin, vec3_mul(ray->direction, t1));
			if (check_height_bounds(&cyl, hit_point))
				t_candidates[candidate_count++] = t1;
		}
		if (t2 >= bound.min && t2 <= bound.max)
		{
			t_point hit_point = vec3_add(ray->origin, vec3_mul(ray->direction, t2));
			if (check_height_bounds(&cyl, hit_point))
				t_candidates[candidate_count++] = t2;
		}
	}
	float t_cap;
	if (intersect_cap(&cyl, ray, cyl.p1, &t_cap, bound))
		t_candidates[candidate_count++] = t_cap;
	if (intersect_cap(&cyl, ray, cyl.p2, &t_cap, bound))
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

int cylinder_shadow_intersect(const t_object *this, const t_ray *ray, t_t_bound bound)
{
	t_cylinder cyl = this->data.cylinder;
	t_quad_eq eq;

	calculate_cylinder_equation(&eq, &cyl, ray);
	if (eq.disc >= 0)
	{
		float sqrt_disc = sqrtf(eq.disc);
		float t1 = (-eq.b - sqrt_disc) / (2.0f * eq.a);
		float t2 = (-eq.b + sqrt_disc) / (2.0f * eq.a);
		if (t1 >= bound.min && t1 <= bound.max)
		{
			t_point hit_point = vec3_add(ray->origin, vec3_mul(ray->direction, t1));
			if (check_height_bounds(&cyl, hit_point))
				return (1);
		}
		if (t2 >= bound.min && t2 <= bound.max)
		{
			t_point hit_point = vec3_add(ray->origin, vec3_mul(ray->direction, t2));
			if (check_height_bounds(&cyl, hit_point))
				return (1);
		}
	}
	float t_cap;
	if (intersect_cap(&cyl, ray, cyl.p1, &t_cap, bound))
		return (1);
	if (intersect_cap(&cyl, ray, cyl.p2, &t_cap, bound))
		return (1);
	return (0);
}

t_vec3 cylinder_get_normal(const t_object *this, t_point *hit_point)
{
	t_cylinder cyl = this->data.cylinder;
	t_vec3 p1_to_hit = vec3_sub(*hit_point, cyl.p1);
	float projection = vec3_dot(p1_to_hit, cyl.axis);
	if (fabs(projection) < EPSILON)
		return (vec3_neg(cyl.axis));
	if (fabs(projection - cyl.height) < EPSILON)
		return (cyl.axis);
	t_vec3 projection_point = vec3_add(cyl.p1, vec3_mul(cyl.axis, projection));
	t_vec3 normal = vec3_sub(*hit_point, projection_point);
	return (vec3_normalize(normal));
}
