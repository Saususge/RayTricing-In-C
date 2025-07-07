/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:00:00 by chakim            #+#    #+#             */
/*   Updated: 2025/07/01 15:00:00 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "vector.h"
#include "object.h"
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

t_vec4	sphere_get_normal(t_vec4 p_local)
{
	p_local.v[3] = 0.0f;
	return (p_local);
}

static t_object_ops	g_sphere_ops = {
	.intersect = sphere_intersect,
	.get_color = sphere_get_color,
};

t_object	create_sphere(t_point center, float radius, t_vec3 color)
{
	t_object	sph;
	t_mat		temp;

	sph.type = SPHERE;
	sph.ops = &g_sphere_ops;
	sph.color = color;
	sph.checkerboard = 0;
	sph.t = (t_mat){{{1, 0, 0, center.x},
	{0, 1, 0, center.y},
	{0, 0, 1, center.z},
	{0, 0, 0, 1}}};
	sph.r = (t_mat){{{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1}}};
	sph.s = (t_mat){{{radius, 0, 0, 0},
	{0, radius, 0, 0},
	{0, 0, radius, 0},
	{0, 0, 0, 1}}};
	mat_mul_mat(&sph.r, &sph.s, &temp);
	mat_mul_mat(&sph.t, &temp, &sph.m);
	mat_inverse(&sph.m, &sph.m_inv);
	return (sph);
}

// Assume that sphere is unit sphere centered at the origin,
// and the ray is converted (M^-1 * ray)
void	calculate_sphere_equation(t_quad_eq *eq, const t_ray *ray)
{
	eq->a = vec4_dot(ray->d, ray->d);
	eq->b = vec4_dot(ray->o, ray->d);
	eq->c = vec4_dot(ray->o, ray->o) - ray->o.v[3] * ray->o.v[3] - 1;
	eq->disc = (eq->b * eq->b) - (eq->a * eq->c);
}
