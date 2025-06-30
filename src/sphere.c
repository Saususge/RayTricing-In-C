/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:07:30 by chakim            #+#    #+#             */
/*   Updated: 2025/06/30 16:58:45 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "vector.h"
#include "object.h"
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

t_vec3	sphere_get_normal(const t_object *this, t_point *hit_point)
{
	return (vec3_mul(vec3_sub(*hit_point, this->data.sphere.center), 1.0f / this->data.sphere.radius));
}

static t_object_ops	g_sphere_ops = {
	.intersect = sphere_intersect,
	.shadow_intersect = shpere_shadow_intersect,
	.get_normal = sphere_get_normal,
	.rotate = sphere_rotate,
	.translate = sphere_translate,
	// .free = NULL
};

t_object	create_sphere(t_point center, float radius, t_vec3 color)
{
	return ((t_object){
		.type = SPHERE,
		.ops = &g_sphere_ops,
		.color = color,
		.data.sphere = (t_sphere){
			.center = center,
			.radius = radius,
		}
	});
}

static void	calculate_sphere_equation(t_quad_eq *eq, const t_sphere *sph, const t_ray *ray)
{
	t_vec3	oc;

	oc = vec3_sub(ray->origin, sph->center);
	eq->a = vec3_dot(ray->dir, ray->dir);
	eq->b = vec3_dot(oc, ray->dir);
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

int	hit_shadow(const t_ray *ray, float t_min, float t_max)
{
	for (int i = 0; i < g()->object_count; ++i)
		if (g()->objects[i].ops->shadow_intersect(g()->objects + i, ray, (t_t_bound){t_min, t_max}))
			return (1);
	return (0);
}

// static int clamp_color(int value)
// {
// 	if (value < 0)
// 		return 0;
// 	if (value > 255)
// 		return 255;
// 	return value;
// }

void	populate_hit_record(t_hit *hit, float t, const t_ray *ray, const t_object *this)
{
	hit->t = t;
	hit->point = vec3_add(ray->origin, vec3_mul(ray->dir, t));
	hit->normal = this->ops->get_normal(this, &hit->point);
	hit->is_front_face = vec3_dot(ray->dir, hit->normal) < 0;
	if (!hit->is_front_face)
		hit->normal = vec3_neg(hit->normal);
	hit->object = (t_object *)this;

	// Lambertian shading with multiple lights + Phong specular
	t_vec3 color = this->color;
	t_vec3 amb = vec3_hadamard(vec3_mul(g()->amb_light.intensity, g()->k_a), color);
	t_vec3 diff = {0, 0, 0};
	t_vec3 spec = {0, 0, 0};
	const float shininess = 64.0f;
	// View direction (from hit point to camera)
	for (int i = 0; i < g()->light_count; ++i)
	{
		t_light	*light = g()->lights + i;
		t_vec3	light_dir = vec3_normalize(vec3_sub(light->position, hit->point));
		t_ray	shadow_ray = { hit->point, light_dir };
		int		hit_shadow_flag = !hit_shadow(&shadow_ray, 0.001f, vec3_length(vec3_sub(light->position, hit->point)) - 0.001f);
		if (hit_shadow_flag)
		{
			float	diff_dot = fmaxf(vec3_dot(hit->normal, light_dir), 0.0f);
			float	distance_sq = point_distance_squared(hit->point, light->position);
			float	attenuation = 1.0f / (distance_sq + 1.0f);
			t_vec3	light_intensity = vec3_mul(light->intensity, g()->k_d * diff_dot * attenuation);
			diff = vec3_add(diff, vec3_hadamard(light_intensity, color));
			// Phong specular (replace Blinn-Phong)
			t_vec3 reflect_dir = vec3_normalize(vec3_reflect(vec3_neg(light_dir), hit->normal));
			t_vec3 view_dir = vec3_normalize(vec3_sub(g()->cam.pos, hit->point));
			float spec_dot = fmaxf(vec3_dot(view_dir, reflect_dir), 0.0f);
			float spec_factor = powf(spec_dot, shininess) * g()->k_s * attenuation;
			t_vec3 spec_color = {255.0f, 255.0f, 255.0f};
			t_vec3 spec_light_intensity = vec3_mul(light->intensity, spec_factor);
			spec = vec3_add(spec, vec3_hadamard(spec_color, spec_light_intensity));
		}
	}
	t_vec3 result = vec3_add(vec3_add(amb, diff), spec);
	result = vec3_max(result, (t_vec3){0, 0, 0});
	result = vec3_min(result, (t_vec3){255, 255, 255});
	hit->color = result;
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
	populate_hit_record(hit, t, ray, this);
	return (1);
}

int	shpere_shadow_intersect(const t_object *this, const t_ray *ray, t_t_bound bound)
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
	return (1);
}
