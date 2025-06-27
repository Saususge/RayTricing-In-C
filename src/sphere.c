/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:07:30 by chakim            #+#    #+#             */
/*   Updated: 2025/06/27 18:09:59 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "vector.h"
#include <unistd.h>
#include <stdlib.h>

static t_object_ops	g_sphere_ops = {
	.intersect = &sphere_intersect,
	.get_normal = NULL,
	.rotate = NULL,
	.translate = NULL,
	.get_color = NULL,
	.free = NULL
};

t_object	create_sphere(t_point center, float radius, t_color color)
{
	return ((t_object){
		.type = SPHERE,
		.ops = &g_sphere_ops,
		.data.sphere = (t_sphere){
			.center = center,
			.radius = radius,
			.color = color
		}
	});
}

static void	calculate_sphere_equation(t_quad_eq *eq, const t_sphere *sph, const t_ray *ray)
{
	t_vec3	oc;

	oc = vec3_sub(ray->origin, sph->center);
	eq->a = vec3_dot(ray->direction, ray->direction);
	eq->b = vec3_dot(oc, ray->direction);
	eq->c = vec3_dot(oc, oc) - (sph->radius * sph->radius);
	eq->disc = (eq->b * eq->b) - (eq->a * eq->c);
}

// static float	choose_valid_root(t_quad_eq *eq)
// {
// 	float	t1;
// 	float	t2;
// 	float	sqrt_disc;

// 	sqrt_disc = sqrtf(eq->disc);
// 	t1 = (-eq->b - sqrt_disc) / (eq->a);
// 	t2 = (-eq->b + sqrt_disc) / (eq->a);
// 	if (t1 > EPSILON && (t1 < t2 || t2 < EPSILON))
// 		return (t1);
// 	if (t2 > EPSILON)
// 		return (t2);
// 	return (-1.0f);
// }

static void	populate_hit_record(t_hit *hit, float t, const t_ray *ray, const t_sphere *sph)
{
	hit->t = t;
	hit->point = vec3_to_point(vec3_add(ray->origin, vec3_mul(ray->direction, t)));
	hit->normal = vec3_mul(vec3_sub(hit->point, sph->center), 1.0f / sph->radius);
	hit->color = sph->color;
	hit->is_front_face = vec3_dot(ray->direction, hit->normal) < 0;
	if (!hit->is_front_face)
		hit->normal = vec3_neg(hit->normal);
}

int	sphere_intersect(const t_object *this, const t_ray *ray, t_hit *hit, t_t_bound bound)
{
	t_sphere	sph;
	t_quad_eq	eq;
	float		t;
	float		sqrt_disc;

	sph = this->data.sphere;
	calculate_sphere_equation(&eq, &sph, ray);
	if (eq.disc < 0)
		return (0);
	sqrt_disc = sqrtf(eq.disc);
	t = -eq.b - sqrt_disc / eq.a;
	if (t < bound.min || t > bound.max)
	{
		t = -eq.b + sqrt_disc / eq.a;
		if (t < bound.min || t > bound.max)
			return (0);
	}
	populate_hit_record(hit, t, ray, &sph);
	return (1);
}
