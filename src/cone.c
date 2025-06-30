/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:56:03 by chakim            #+#    #+#             */
/*   Updated: 2025/06/30 15:12:35 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"
#include "vector.h"
#include "rotate.h"
#include <math.h>
#include <unistd.h>

static t_object_ops	g_cone_ops = {
	.intersect = cone_intersect,
	.shadow_intersect = cone_shadow_intersect,
	.get_normal = cone_get_normal,
	.rotate = cone_rotate,
	.translate = cone_translate,
};

static void	calculate_cone_equation(t_quad_eq *eq, const t_cone *cone, const t_ray *ray)
{
	t_vec3	co;
	float	cos2;
	float	dv;
	float	cov;

	co = vec3_sub(ray->origin, cone->center);
	cos2 = (cone->radius / cone->height) * (cone->radius / cone->height);
	dv = vec3_dot(ray->dir, cone->axis);
	cov = vec3_dot(co, cone->axis);
	eq->a = vec3_dot(ray->dir, ray->dir) - (1 + cos2) * dv * dv;
	eq->b = vec3_dot(ray->dir, co) - (1 + cos2) * dv * cov;
	eq->c = vec3_dot(co, co) - (1 + cos2) * cov * cov;
	eq->disc = eq->b * eq->b - eq->a * eq->c;
}

static int	check_height_bounds(const t_cone *cone, t_point hit_point)
{
	t_vec3	center_to_hit;
	float	projection;

	center_to_hit = vec3_sub(hit_point, cone->center);
	projection = vec3_dot(center_to_hit, cone->axis);
	return (projection >= 0.0f && projection <= cone->height);
}

static int	intersect_cap(const t_cone *cone, const t_ray *ray, float *t, t_t_bound bound)
{
	float	temp_t;
	float	denom;
	t_vec3	oc;
	t_point	hit_point;
	t_vec3	cap_to_hit;
	float	dist_sq;

	denom = vec3_dot(ray->dir, cone->axis);
	if (fabs(denom) < EPSILON)
		return (0);
	oc = vec3_sub(vec3_add(cone->center, vec3_mul(cone->axis, cone->height)), ray->origin);
	temp_t = vec3_dot(oc, cone->axis) / denom;
	if (temp_t < bound.min || temp_t > bound.max)
		return (0);
	hit_point = vec3_add(ray->origin, vec3_mul(ray->dir, temp_t));
	cap_to_hit = vec3_sub(hit_point, vec3_add(cone->center, vec3_mul(cone->axis, cone->height)));
	dist_sq = vec3_dot(cap_to_hit, cap_to_hit);
	if (dist_sq > cone->radius * cone->radius)
		return (0);
	*t = temp_t;
	return (1);
}

static int	cone_lateral_intersect(const t_cone *cone, const t_ray *ray, float *t, t_t_bound bound)
{
	t_quad_eq	eq;
	float		sqrt_disc;
	float		t_temp;
	t_point		hit;

	calculate_cone_equation(&eq, cone, ray);
	if (eq.disc < 0)
		return (0);
	sqrt_disc = sqrtf(eq.disc);
	t_temp = (-eq.b - sqrt_disc) / eq.a;
	hit = vec3_add(ray->origin, vec3_mul(ray->dir, t_temp));
	if (t_temp > bound.min && t_temp < bound.max && check_height_bounds(cone, hit))
	{
		*t = t_temp;
		return (1);
	}
	t_temp = (-eq.b + sqrt_disc) / eq.a;
	hit = vec3_add(ray->origin, vec3_mul(ray->dir, t_temp));
	if (t_temp > bound.min && t_temp < bound.max && check_height_bounds(cone, hit))
	{
		*t = t_temp;
		return (1);
	}
	return (0);
}

void	cone_translate(t_object *this, t_vec3 offset)
{
	this->data.cone.center = vec3_add(this->data.cone.center, offset);
}

void	cone_rotate(t_object *this, t_vec3 angle)
{
	this->data.cone.axis = rotate_vector(this->data.cone.axis, angle);
}

t_object	create_cone(struct s_cone_data data)
{
	return ((t_object){
		.type = CONE,
		.ops = &g_cone_ops,
		.color = data.color,
		.data.cone = (t_cone){
			.center = data.center,
			.axis = data.axis,
			.radius = data.radius,
			.height = data.height,
		}
	});
}

int	cone_intersect(const t_object *this, const t_ray *ray, t_hit *hit, t_t_bound bound)
{
	float			t;
	int			lateral_hit;
	int			cap_hit;

	t = 0.0f;
	lateral_hit = cone_lateral_intersect(&this->data.cone, ray, &t, bound);
	if (lateral_hit)
		cap_hit = intersect_cap(&this->data.cone, ray, &t, (t_t_bound){bound.min, t});
	else
		cap_hit = intersect_cap(&this->data.cone, ray, &t, bound);
	if (!lateral_hit && !cap_hit)
		return (0);
	populate_hit_record(hit, t, ray, this);
	return (1);
}

int	cone_shadow_intersect(const t_object *this, const t_ray *ray, t_t_bound bound)
{
	const t_cone	*cone;
	float			t;
	int			lateral_hit;
	int			cap_hit;

	t = 0.0f;
	cone = &this->data.cone;
	lateral_hit = cone_lateral_intersect(cone, ray, &t, bound);
	if (lateral_hit)
		cap_hit = intersect_cap(cone, ray, &t, (t_t_bound){bound.min, t});
	else
		cap_hit = intersect_cap(cone, ray, &t, bound);
	if (lateral_hit || cap_hit)
		return (1);
	return (0);
}

t_vec3	cone_get_normal(const t_object *this, t_point *hit_point)
{
	t_cone	cone;
	t_vec3	center_to_hit;
	float	projection;
	t_vec3	axis_point;
	t_vec3	normal;

	cone = this->data.cone;
	center_to_hit = vec3_sub(*hit_point, cone.center);
	projection = vec3_dot(center_to_hit, cone.axis);
	if (fabs(projection - cone.height) < EPSILON)
		return (cone.axis);
	axis_point = vec3_add(cone.center, vec3_mul(cone.axis, projection));
	normal = vec3_sub(*hit_point, axis_point);
	normal = vec3_sub(
		normal,
		vec3_mul(cone.axis, cone.radius / cone.height * vec3_length(normal)));
	return (vec3_normalize(normal));
}
