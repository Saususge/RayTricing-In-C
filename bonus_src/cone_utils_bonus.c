/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:00:00 by chakim            #+#    #+#             */
/*   Updated: 2025/07/08 16:36:38 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"
#include <math.h>

static void	calculate_cone_equation(const t_ray *ray, t_quad_eq_c *eq)
{
	eq->a = ray->d.v[0] * ray->d.v[0] + \
	ray->d.v[1] * ray->d.v[1] - ray->d.v[2] * ray->d.v[2];
	eq->b = ray->o.v[0] * ray->d.v[0] + \
	ray->o.v[1] * ray->d.v[1] - ray->o.v[2] * ray->d.v[2];
	eq->c = ray->o.v[0] * ray->o.v[0] + \
	ray->o.v[1] * ray->o.v[1] - ray->o.v[2] * ray->o.v[2];
	eq->disc = eq->b * eq->b - eq->a * eq->c;
}

static int	is_valid_t_value(float t, float z, t_interval t_bound)
{
	if (t >= t_bound.min && t <= t_bound.max && z >= 0.0f && z <= 1.0f)
		return (1);
	return (0);
}

static int	select_intersection(const t_ray *ray, const t_quad_eq_c *eq, \
	float *t, t_interval t_bound)
{
	float	sqrt_disc;
	float	t1;
	float	t2;
	float	z1;
	float	z2;

	sqrt_disc = sqrtf(eq->disc);
	t1 = (-eq->b - sqrt_disc) / eq->a;
	t2 = (-eq->b + sqrt_disc) / eq->a;
	z1 = ray->o.v[2] + ray->d.v[2] * t1;
	z2 = ray->o.v[2] + ray->d.v[2] * t2;
	if (is_valid_t_value(t1, z1, t_bound))
	{
		if (!is_valid_t_value(t2, z2, t_bound) || t1 < t2)
		{
			*t = t1;
			return (1);
		}
	}
	if (is_valid_t_value(t2, z2, t_bound))
	{
		*t = t2;
		return (1);
	}
	return (0);
}

int	cone_lateral_intersect(const t_ray *ray, float *t, t_interval t_bound)
{
	t_quad_eq_c	eq;

	calculate_cone_equation(ray, &eq);
	if (eq.disc < 0)
		return (0);
	return (select_intersection(ray, &eq, t, t_bound));
}

int	cone_intersect_cap(const t_ray *ray, float *t, t_interval t_bound)
{
	float	t_cap;
	t_vec4	p_cap;

	if (fabsf(ray->d.v[2]) < EPSILON)
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
