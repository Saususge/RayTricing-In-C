/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:12:52 by chakim            #+#    #+#             */
/*   Updated: 2025/06/30 01:39:40 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"
#include "unistd.h"
#include "vector.h"
#include <stdlib.h>
#include "rotate.h"

static t_object_ops	g_plane_ops = {
	.intersect = plane_intersect,
	.shadow_intersect = plane_shadow_intersect, // Plane does not cast shadows in this implementation
	.get_normal = plane_get_normal,
	.rotate = plane_rotate,
	.translate = plane_translate,
	.get_color = plane_get_color,
};

t_object	create_plane(t_point point, t_vec3 normal, t_color color)
{
	return ((t_object){
		.type = PLANE,
		.ops = &g_plane_ops,
		.data.plane = (t_plane){
			.point = point,
			.normal = normal,
			.color = color
		}
	});
}

int	hit_shadow(const t_ray *ray, float t_min, float t_max);

static void	populate_hit_record(t_hit *hit, float t, const t_ray *ray, const t_plane *pl)
{
	hit->t = t;
	hit->point = vec3_lerp(ray->origin, ray->direction, t);
	hit->normal = pl->normal;
	if (vec3_dot(ray->direction, hit->normal) < 0)
		hit->normal = vec3_neg(hit->normal);
	hit->is_front_face = vec3_dot(ray->direction, hit->normal) < 0;
	if (!hit->is_front_face)
		hit->normal = vec3_neg(hit->normal);

	// Lambertian shading with multiple lights + Blinn-Phong specular
	t_vec3 color = { pl->color.r, pl->color.g, pl->color.b };
	t_vec3 amb = vec3_hadamard(vec3_mul(g_ambient_light.intensity, g_k_a), color);
	t_vec3 diff = {0, 0, 0};
	t_vec3 spec = {0, 0, 0};
	const float shininess = 64.0f;
	// View direction (from hit point to camera)
	t_vec3 view_dir = vec3_normalize(vec3_sub(g_camera.position, hit->point));
	for (int i = 0; i < g_light_count; ++i)
	{
		t_light	*light = g_lights + i;
		t_vec3	light_dir = vec3_normalize(vec3_sub(light->position, hit->point));
		t_ray	shadow_ray = { hit->point, light_dir };
		int		hit_shadow_flag = !hit_shadow(&shadow_ray, 0.001f, vec3_length(vec3_sub(light->position, hit->point)));
		if (hit_shadow_flag)
		{
			float	diff_dot = fmaxf(vec3_dot(hit->normal, light_dir), 0.0f);
			float	distance_sq = point_distance_squared(hit->point, light->position);
			float	attenuation = 1.0f / (distance_sq + 1.0f);
			t_vec3	light_intensity = vec3_mul(light->intensity, g_k_d * diff_dot * attenuation);
			diff = vec3_add(diff, vec3_hadamard(light_intensity, color));
			// Blinn-Phong specular
			t_vec3 half_vec = vec3_normalize(vec3_add(light_dir, view_dir));
			float spec_dot = fmaxf(vec3_dot(hit->normal, half_vec), 0.0f);
			float spec_factor = powf(spec_dot, shininess) * g_k_s * attenuation;
			t_vec3 spec_color = {255.0f, 255.0f, 255.0f};
			spec = vec3_add(spec, vec3_mul(spec_color, spec_factor));
		}
	}
	t_vec3 result = vec3_add(vec3_add(amb, diff), spec);
	result = vec3_min(result, (t_vec3){255, 255, 255});
	hit->color = (t_color){
		.r = (int)result.x,
		.g = (int)result.y,
		.b = (int)result.z
	};
}

int	plane_intersect(const t_object *this, const t_ray *ray, t_hit *hit, t_t_bound bound)
{
	t_plane	pl;	
	float	denominator;
	float	t;
	t_vec3	p0_to_l0;

	pl = this->data.plane;
	denominator = vec3_dot(ray->direction, pl.normal);
	if (fabs(denominator) < EPSILON)
		return (0);
	p0_to_l0 = vec3_sub(pl.point, ray->origin);
	t = vec3_dot(p0_to_l0, pl.normal) / denominator;
	if (t < bound.min || t > bound.max)
		return (0);
	populate_hit_record(hit, t, ray, &pl);
	return (1);
}

int	plane_shadow_intersect(const t_object *this, const t_ray *ray, t_t_bound bound)
{
	t_plane	pl;	
	float	denominator;
	float	t;
	t_vec3	p0_to_l0;

	pl = this->data.plane;
	p0_to_l0 = vec3_sub(pl.point, ray->origin);
	denominator = vec3_dot(ray->direction, pl.normal);
	if (fabs(denominator) < EPSILON)
		return (0);
	t = vec3_dot(p0_to_l0, pl.normal) / denominator;
	if (t < bound.min || t > bound.max)
		return (0);
	return (1);
}
