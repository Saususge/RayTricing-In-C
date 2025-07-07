/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:34:32 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/07 16:37:02 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

static void	init_viewport(void)
{
	t_viewport	*viewport;
	static int	initialized;

	viewport = &g()->viewport;
	viewport->aspect_ratio = 21.0f / 9.0f;
	if (!initialized)
	{
		viewport->width = 1680;
		viewport->height = (int)(viewport->width / viewport->aspect_ratio);
		viewport->focal_length = 1.0f;
		viewport->view_w = 2.0f * viewport->focal_length
			* tanf(g()->cam.fov * (float)M_PI / 360.0f);
		viewport->view_h = viewport->view_w / viewport->aspect_ratio;
		viewport->vup.y = 1.0f;
		initialized = 1;
	}
}

void	set_viewport(void)
{
	t_viewport	*viewport;

	init_viewport();
	viewport = &g()->viewport;
	viewport->view_u = vec3_mul(
			vec3_normalize(vec3_cross(g()->cam.dir, viewport->vup)),
			viewport->view_w);
	viewport->view_v = vec3_mul(
			vec3_normalize(vec3_cross(viewport->view_u, g()->cam.dir)),
			-viewport->view_h);
	viewport->view_u_per_pixel = vec3_mul(viewport->view_u,
			1.0f / (float)viewport->width);
	viewport->view_v_per_pixel = vec3_mul(viewport->view_v,
			1.0f / (float)viewport->height);
	viewport->view_upper_left = vec3_sub(g()->cam.pos,
			vec3_add(
				vec3_mul(g()->cam.dir, -viewport->focal_length),
				vec3_add(
					vec3_mul(viewport->view_u, 0.5f),
					vec3_mul(viewport->view_v, 0.5f))));
	viewport->pixel_origin = vec3_add(viewport->view_upper_left,
			vec3_mul(
				vec3_add(
					viewport->view_v_per_pixel,
					viewport->view_u_per_pixel), 0.5f));
}
