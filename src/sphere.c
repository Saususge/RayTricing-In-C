/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:07:30 by chakim            #+#    #+#             */
/*   Updated: 2025/05/17 13:51:54 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "vector.h"
#include <unistd.h>

t_object	*create_sphere(t_point center)
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
}

static float	calc_disc(t_vec3 oc, t_vec3 dir, float radius)
{
	float	a;
	float	b;
	float	c;

	a = vec3_dot(dir, dir);
	b = 2.0f * vec3_dot(oc, dir);
	c = vec3_dot(oc, oc) - radius * radius;
	return (b * b - 4 * a * c);
}

static int	choose_t(float b, float disc, float a)
{
	float	t1;
	float	t2;

	t1 = (-b - sqrtf(disc)) / (2.0f * a);
	t2 = (-b + sqrtf(disc)) / (2.0f * a);
	if (t1 > 0)
		return (t1);
	if (t2 > 0)
		return (t2);
	return (-1);
}

float	get_disc(t_sphere *sph, t_ray *ray)
{
	t_vec3		oc;
	float		a;
	float		b;
	float		disc;

	oc = vec3_sub(ray->origin, sph->center);
	a = vec3_dot(ray->direction, ray->direction);
	b = 2.0f * vec3_dot(oc, ray->direction);
	disc = calc_disc(oc, ray->direction, sph->radius);
	return (disc);
}

int	sphere_intersect(t_object *this, t_ray *ray, t_hit *hit)
{
	t_sphere	*sph;
	float		a;
	float		b;
	float		disc;
	float		t;

	sph = (t_sphere *)this->data;
	disc = get_disc(sph, ray);
	if (disc < 0)
		return (0);
	t = choose_t(b, disc, a);
	if (t < 0)
		return (0);
	hit->t = t;
	hit->point = vec3_to_point(vec3_add(ray->origin, \
vec3_mul(ray->direction, t)));
	hit->normal = vec3_normalize(vec3_sub(point_to_vec3(hit->point), \
sph->center));
	hit->color = (t_color){sph->color.x, sph->color.y, sph->color.z, 1.0f};
	hit->object = this;
	hit->is_front_face = vec3_dot(ray->direction, hit->normal) < 0;
	if (!hit->is_front_face)
		hit->normal = vec3_neg(hit->normal);
	return (1);
}
