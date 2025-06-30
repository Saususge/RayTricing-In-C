/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:56:47 by chakim            #+#    #+#             */
/*   Updated: 2025/06/30 15:56:50 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "vector.h"
#include "rotate.h"
#include <unistd.h>

void	cylinder_translate(t_object *this, t_vec3 offset)
{
	this->data.cylinder.p1 = vec3_add(this->data.cylinder.p1, offset);
	this->data.cylinder.p2 = vec3_add(this->data.cylinder.p2, offset);
	this->data.cylinder.center = vec3_add(this->data.cylinder.center, offset);
}

void	cylinder_rotate(t_object *this, t_vec3 angle)
{
	this->data.cylinder.axis = rotate_vector(this->data.cylinder.axis, angle);
	this->data.cylinder.p1 = vec3_add(
			this->data.cylinder.center,
			vec3_mul(this->data.cylinder.axis,
				-this->data.cylinder.height * 0.5f));
	this->data.cylinder.p2 = vec3_add(
			this->data.cylinder.center,
			vec3_mul(this->data.cylinder.axis,
				this->data.cylinder.height * 0.5f));
}

static void calculate_cylinder_equation(t_quad_eq *eq, const t_cylinder *cyl, const t_ray *ray)
{
    t_point p1 = vec3_sub(cyl->center, vec3_mul(cyl->axis, cyl->height * 0.5f));
    t_vec3 delta_p = vec3_sub(ray->origin, p1);
    t_vec3 v_cross_axis = vec3_cross(ray->dir, cyl->axis);
    t_vec3 dp_cross_axis = vec3_cross(delta_p, cyl->axis);

    eq->a = vec3_dot(v_cross_axis, v_cross_axis);
    eq->b = vec3_dot(v_cross_axis, dp_cross_axis);
    eq->c = vec3_dot(dp_cross_axis, dp_cross_axis) - (cyl->radius * cyl->radius);
    eq->disc = eq->b * eq->b - eq->a * eq->c;
}

static int check_height(const t_cylinder *cyl, t_point hit_point)
{
    t_vec3 p1_to_hit = vec3_sub(hit_point, cyl->p1);
    float projection = vec3_dot(p1_to_hit, cyl->axis);
    return (projection >= 0.0f && projection <= cyl->height);
}

static int check_in_circle(const t_cylinder *cyl, const t_ray *ray, t_point cap_center, float t)
{
	t_point	hit_point;
	t_vec3	cap_to_hit;
	float	dist_sq;
	
	hit_point = vec3_add(ray->origin, vec3_mul(ray->dir, t));
	cap_to_hit = vec3_sub(hit_point, cap_center);
	dist_sq = vec3_dot(cap_to_hit, cap_to_hit);
	return (dist_sq <= cyl->radius * cyl->radius);
}

static int intersect_cap(const t_cylinder *cyl, const t_ray *ray, float *t, t_t_bound bound)
{
	float	t_temp;
	float	denom = vec3_dot(ray->dir, cyl->axis);
	if (fabs(denom) < EPSILON)
		return (0);
	t_vec3 oc = vec3_sub(cyl->p1, ray->origin);
	t_temp = vec3_dot(oc, cyl->axis) / denom;
	
	if (t_temp < bound.min || t_temp > bound.max || !check_in_circle(cyl, ray, cyl->p1, t_temp))
	{
		t_temp = vec3_dot(vec3_sub(cyl->p2, ray->origin), cyl->axis) / denom;
		if (t_temp < bound.min || t_temp > bound.max || !check_in_circle(cyl, ray, cyl->p2, t_temp))
			return (0);
	}
	*t = t_temp;
	return (1);
}

static int intersect_lateral(const t_cylinder *cyl, const t_ray *ray, float *t, t_t_bound bound)
{
	t_quad_eq	eq;
	float		t_temp;
	calculate_cylinder_equation(&eq, cyl, ray);
	if (eq.disc < 0)
		return (0);
	float sqrt_disc = sqrtf(eq.disc);
	t_temp = (-eq.b - sqrt_disc) / (eq.a);
	t_point hit_point = vec3_add(ray->origin, vec3_mul(ray->dir, t_temp));
	if (t_temp < bound.min || t_temp > bound.max || !check_height(cyl, hit_point))
	{
		t_temp = (-eq.b + sqrt_disc) / (eq.a);
		hit_point = vec3_add(ray->origin, vec3_mul(ray->dir, t_temp));
		if (t_temp < bound.min || t_temp > bound.max || !check_height(cyl, hit_point))
			return (0);
	}
	*t = t_temp;
	return (1);
}

int	cylinder_intersect(const t_object *this,
						const t_ray *ray,
						t_hit *hit,
						t_t_bound bound)
{
	int			lateral_hit;
	int			cap_hit;
	float		t;

	lateral_hit = intersect_lateral(&this->data.cylinder, ray, &t, bound);
	if (lateral_hit)
		cap_hit = intersect_cap(&this->data.cylinder, ray, &t, (t_t_bound){bound.min, t});
	else
		cap_hit = intersect_cap(&this->data.cylinder, ray, &t, bound);
	if (!lateral_hit && !cap_hit)
		return (0);
	populate_hit_record(hit, t, ray, this);
	return (1);
}

int	cylinder_shadow_intersect(const t_object *this,
						const t_ray *ray,
						t_t_bound bound)
{
	int			lateral_hit;
	int			cap_hit;
	float		t;

	lateral_hit = intersect_lateral(&this->data.cylinder, ray, &t, bound);
	if (lateral_hit)
		cap_hit = intersect_cap(&this->data.cylinder, ray, &t, (t_t_bound){bound.min, t});
	else
		cap_hit = intersect_cap(&this->data.cylinder, ray, &t, bound);
	if (!lateral_hit && !cap_hit)
		return (0);
	return (1);
}

t_vec3 cylinder_get_normal(const t_object *this, t_point *hit_point)
{
    t_cylinder cyl = this->data.cylinder;
    t_vec3 p1_to_hit = vec3_sub(*hit_point, this->data.cylinder.p1);
    float projection = vec3_dot(p1_to_hit, cyl.axis);
    if (fabs(projection) < EPSILON)
        return (vec3_neg(cyl.axis));
    if (fabs(projection - cyl.height) < EPSILON)
        return (cyl.axis);
    t_vec3 projection_point = vec3_add(this->data.cylinder.p1, vec3_mul(cyl.axis, projection));
    t_vec3 normal = vec3_mul(vec3_sub(*hit_point, projection_point), 1.0f / cyl.radius);
    return (normal);
}
