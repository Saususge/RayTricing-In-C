/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:07:30 by chakim            #+#    #+#             */
/*   Updated: 2025/05/26 14:06:18 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "vector.h"
#include <unistd.h>

static t_object_ops	g_sphere_ops = {
	.intersect = &sphere_intersect,
	.get_normal = NULL,
	.rotate = NULL,
	.translate = NULL,
	.get_color = NULL,
	.free = NULL
};

t_object	*create_sphere(t_point center, float radius, t_vec3 color)
{
	t_object	*obj;
	t_sphere	*sph;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	sph = malloc(sizeof(t_sphere));
	if (!sph)
	{
		free(obj);
		return (NULL);
	}
	sph->center = center;
	sph->radius = radius;
	sph->color = color;
	obj->type = SPHERE;
	obj->data = sph;
	obj->ops = &g_sphere_ops;
	return (obj);
}

static void	calculate_sphere_equation(t_quad_eq *eq, t_sphere *sph, t_ray *ray)
{
	t_vec3	oc;

	oc = vec3_sub(ray->origin, sph->center);
	eq->a = vec3_dot(ray->direction, ray->direction);
	eq->b = 2.0f * vec3_dot(oc, ray->direction);
	eq->c = vec3_dot(oc, oc) - (sph->radius * sph->radius);
	eq->disc = (eq->b * eq->b) - (4 * eq->a * eq->c);
}

static float	choose_valid_root(t_quad_eq *eq)
{
	float	t1;
	float	t2;

	t1 = (-eq->b - sqrtf(eq->disc)) / (2.0f * eq->a);
	t2 = (-eq->b + sqrtf(eq->disc)) / (2.0f * eq->a);
	if (t1 > EPSILON && (t1 < t2 || t2 < EPSILON))
		return (t1);
	if (t2 > EPSILON)
		return (t2);
	return (-1.0f);
}

static void	populate_hit_record(t_hit *hit, float t, t_ray *ray, t_sphere *sph)
{
	hit->t = t;
	hit->point = vec3_to_point(vec3_add(ray->origin, \
		vec3_mul(ray->direction, t)));
	hit->normal = vec3_normalize(vec3_sub(point_to_vec3(hit->point), \
		sph->center));
	hit->color = (t_color){sph->color.x, sph->color.y, sph->color.z, 1.0f};
	hit->is_front_face = vec3_dot(ray->direction, hit->normal) < 0;
	if (!hit->is_front_face)
		hit->normal = vec3_neg(hit->normal);
}

int	sphere_intersect(t_object *this, t_ray *ray, t_hit *hit)
{
	t_sphere	*sph;
	t_quad_eq	eq;
	float		t;

	sph = (t_sphere *)this->data;
	calculate_sphere_equation(&eq, sph, ray);
	if (eq.disc < 0)
		return (0);
	t = choose_valid_root(&eq);
	if (t < 0)
		return (0);
	populate_hit_record(hit, t, ray, sph);
	hit->object = this;
	return (1);
}
