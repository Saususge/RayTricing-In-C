/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_checkerboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:00:00 by chakim            #+#    #+#             */
/*   Updated: 2025/07/09 17:17:17 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"
#include <math.h>

t_vec3	cone_get_color(const t_intersect *record)
{
	float	u;
	float	v;

	if (!record->obj->checkerboard)
		return (record->obj->color);
	if (fabsf(record->p_local.v[2] - 1.0f) < EPSILON)
	{
		u = atan2f(record->p_local.v[1], record->p_local.v[0]) / (2.0f * (float)M_PI) + 0.5f;
		v = sqrtf(record->p_local.v[0] * record->p_local.v[0] + \
			record->p_local.v[1] * record->p_local.v[1]);
	}
	else
	{
		u = atan2f(record->p_local.v[1], record->p_local.v[0]) / (2.0f * (float)M_PI) + 0.5f;
		v = record->p_local.v[2];
	}
	return (checkerboard_color_at(u, v));
}
