/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:56:03 by chakim            #+#    #+#             */
/*   Updated: 2025/07/03 18:05:31 by wchoe            ###   ########.fr       */
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
	.scale = cone_scale,
};

void	calculate_cone_equation(
				t_quad_eq *eq,
				const t_cone *cone,
				const t_ray *ray)
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

int	cone_check_height(
				const t_cone *cone,
				t_point hit_point)
{
	t_vec3	center_to_hit;
	float	projection;

	center_to_hit = vec3_sub(hit_point, cone->center);
	projection = vec3_dot(center_to_hit, cone->axis);
	return (projection >= 0.0f && projection <= cone->height);
}

static int	cone_lateral_check(const t_cone *cone, \
	const t_ray *ray, float t, t_t_bound bound)
{
	t_point	hit;

	hit = vec3_add(ray->origin, vec3_mul(ray->dir, t));
	return (t > bound.min && t < bound.max && cone_check_height(cone, hit));
}

int	cone_lateral_intersect(
				const t_cone *cone,
				const t_ray *ray,
				float *t,
				t_t_bound bound)
{
	t_quad_eq	eq;
	float		sqrt_disc;
	float		t_temp;

	calculate_cone_equation(&eq, cone, ray);
	if (eq.disc < 0)
		return (0);
	sqrt_disc = sqrtf(eq.disc);
	t_temp = (-eq.b - sqrt_disc) / eq.a;
	if (cone_lateral_check(cone, ray, t_temp, bound))
	{
		*t = t_temp;
		return (1);
	}
	t_temp = (-eq.b + sqrt_disc) / eq.a;
	if (cone_lateral_check(cone, ray, t_temp, bound))
	{
		*t = t_temp;
		return (1);
	}
	return (0);
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
	}});
}
