/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:20:25 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/04 17:20:25 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"
#include "object.h"
#include <math.h>

// t_vec4	get_light_dir(const t_light *light, const t_hit *hit)
// {
// 	t_vec4	v = vec4_sub(light->position, hit->point);
// 	return (vec4_mul(v, 1.0f / sqrtf(vec4_dot(v, v))));
// }

// int	hit_ray_without_color(const t_ray *ray_world, t_interval bound_world, t_object **obj)
// {
// 	int			hit_anything;
// 	int			i;
// 	t_intersect	current_intersect;

// 	hit_anything = 0;
// 	i = 0;
// 	while (i < g()->object_count)
// 	{
// 		if (g()->objects[i].ops->intersect(g()->objects + i, ray_world,
// 				&current_intersect, bound_world))
// 		{
// 			hit_anything = 1;
// 			bound_world.max = convert_t_local_to_world(current_intersect.object, current_intersect.t_local);
// 			*obj = current_intersect.object;
// 		}
// 		++i;
// 	}
// 	return (hit_anything);
// }

int	shoot_ray_from_viewport(int x, int y, t_object **obj, t_vec3 *color)
{
	t_vec3		pixel_pos;
	t_ray		ray;
	t_intersect	intersect_record;
	int			ret;

	pixel_pos = vec3_add(
			g()->viewport.pixel_origin,
			vec3_add(vec3_mul(g()->viewport.view_u_per_pixel, (float)x),
				vec3_mul(g()->viewport.view_v_per_pixel, (float)y)));
	ray = (t_ray){
		.o = vec3_to_vec4(g()->cam.pos, 1.0f),
		.d = vec3_to_vec4(
			vec3_normalize(vec3_sub(pixel_pos, g()->cam.pos)), 0.0f)};
	ret = hit_ray(&ray, (t_interval){0.0f, INFINITY}, &intersect_record, color);
	*obj = intersect_record.obj;
	return (ret);
}
