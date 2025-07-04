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

t_vec3	get_light_dir(const t_light *light, const t_hit *hit)
{
	return (vec3_normalize(vec3_sub(light->position, hit->point)));
}

int	shoot_ray_from_viewport(int x, int y, t_hit *hit)
{
	t_vec3	pixel_pos;
	t_ray	ray;

	pixel_pos = vec3_add(
			g()->viewport.pixel_origin,
			vec3_add(vec3_mul(g()->viewport.view_u_per_pixel, (float)x),
				vec3_mul(g()->viewport.view_v_per_pixel, (float)y)));
	ray = (t_ray){
		.origin = g()->cam.pos,
		.dir = vec3_normalize(vec3_sub(pixel_pos, g()->cam.pos))};
	return (hit_objects(&ray, 0.0f, INFINITY, hit));
}
