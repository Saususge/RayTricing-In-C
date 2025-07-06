/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_def.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:20:25 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/04 17:20:25 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"
#include "object.h"
#define	K_AMBIENT 0.2f
#define K_DIFFUSE 1.0f
#define K_SPECULAR 1.0f
#define SHININESS 64.0f

float convert_t_local_to_world(const t_object *obj, t_vec4 p_local, const t_ray *ray_world)
{
	t_vec4	p_world;

	p_world = mat_mul_vec4(&obj->m, p_local);
	return (vec4_dot(vec4_sub(p_world, ray_world->o), ray_world->d));	// Assume ray_world->d is normalized
}

t_vec3	clamp_color(t_vec3 color)
{
	color = vec3_max(color, (t_vec3){0, 0, 0});
	color = vec3_min(color, (t_vec3){255, 255, 255});
	return (color);
}

t_vec3	get_color(const t_intersect *record)
{
	t_vec3	ambient;
	t_vec3	diffuse;
	t_vec3	specular;
	int		i;
	t_vec4	hit_point_world;
	t_vec4	light_v_world;
	float	dist_sq_world;
	float	attenuation;
	t_ray	shadow_ray_world;

	ambient = vec3_hadamard(vec3_mul(g()->amb_light.intensity, K_AMBIENT), record->obj->color);
	diffuse = (t_vec3){0, 0, 0};
	specular = (t_vec3){0, 0, 0};
	i = 0;
	hit_point_world = mat_mul_vec4(&record->obj->m, record->p_local);
	while (i < g()->light_count)
	{
		light_v_world = vec4_sub(g()->lights[i].position, hit_point_world);
		dist_sq_world = vec4_dot(light_v_world, light_v_world);
		light_v_world = vec4_mul(light_v_world, 1.0f / sqrtf(dist_sq_world));
		shadow_ray_world = (t_ray){.o = hit_point_world, .d = light_v_world};
		if (!hit_shadow_ray(&shadow_ray_world, (t_interval){EPSILON, sqrtf(dist_sq_world) - EPSILON}))
		{
			t_vec4	light_v_local = vec4_sub(record->obj->local_light_pos[i], record->p_local);
			light_v_local = vec4_mul(light_v_local, 1.0f / sqrtf(vec4_dot(light_v_local, light_v_local)));
			t_vec4	normal_local = record->obj->ops->get_normal(record->obj, record->p_local);
			attenuation = 1.0f / (1.0f + 0.05 * dist_sq_world);
			float	diffusion_dot = fmaxf(vec4_dot(normal_local, light_v_local), 0.0f);
			t_vec3	diffusion_light_intensity = vec3_mul(g()->lights[i].intensity, K_DIFFUSE * diffusion_dot * attenuation);
			diffuse = vec3_add(diffuse, vec3_hadamard(diffusion_light_intensity, record->obj->color));
			t_vec4	view_local = vec4_sub(vec3_to_vec4(g()->cam.pos, 1.0f), hit_point_world);
			t_vec4	reflect_local = vec4_sub(vec4_neg(light_v_local), vec4_mul(normal_local, 2.0f * vec4_dot(vec4_neg(light_v_local), normal_local)));
			reflect_local.v[3] = 0.0f;	
			float	specular_dot = fmaxf(vec4_dot(view_local, reflect_local) / (sqrtf(vec4_dot(view_local, view_local)) * sqrtf(vec4_dot(reflect_local, reflect_local))), 0.0f);
			float	specular_factor = powf(specular_dot, SHININESS) * K_SPECULAR * attenuation * g()->specular;
			specular = vec3_add(specular, vec3_mul(g()->lights[i].intensity, specular_factor * 255.0f));
		}
		++i;
	}
	return (clamp_color(vec3_add(vec3_add(ambient, diffuse), specular)));
}

int	hit_ray(const t_ray *ray_world, t_interval bound_world, t_intersect *intersect_record, t_vec3 *color)
{
	int			hit_anything;
	int			i;
	t_intersect	current_intersect;

	hit_anything = 0;
	i = 0;
	while (i < g()->object_count)
	{
		if (g()->objects[i].ops->intersect(g()->objects + i, ray_world,
				&current_intersect, bound_world))
		{
			hit_anything = 1;
			bound_world.max = convert_t_local_to_world(g()->objects + i, intersect_record->p_local, ray_world);
			*intersect_record = current_intersect;
		}
		++i;
	}
	if (hit_anything)
		*color = get_color(intersect_record);
	return (hit_anything);
}

int	hit_shadow_ray(const t_ray *shadow_ray_world, t_interval bound_world)
{
	t_intersect	dump;
	int			i;

	i = 0;
	while (i < g()->object_count)
	{
		if (g()->objects[i].ops->intersect(g()->objects + i,
				shadow_ray_world, &dump, bound_world))
			return (1);
		++i;
	}
	return (0);
}
