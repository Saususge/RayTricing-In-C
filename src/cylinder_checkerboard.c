/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_checkerboard.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:05:15 by chakim            #+#    #+#             */
/*   Updated: 2025/07/09 18:01:40 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include <math.h>

static float	get_theta(t_vec4 p_local)
{
	return (atan2f(p_local.v[1], p_local.v[0]));
}

t_vec3	cylinder_get_color(const t_intersect *record)
{
	float	u;
	float	v;
	float	theta;

	if (!record->obj->checkerboard)
		return (record->obj->color);
	theta = get_theta(record->p_local);
	u = theta / (2.0f * (float)M_PI) + 0.5f;
	if (fabsf(record->p_local.v[2] - 0.5f) < EPSILON || \
	fabsf(record->p_local.v[2] + 0.5f) < EPSILON)
		v = sqrtf(record->p_local.v[0] * record->p_local.v[0] + record->p_local.v[1] * record->p_local.v[1]);
	else
		v = 0.5f + record->p_local.v[2];
	return (checkerboard_color_at(u, v));
}
