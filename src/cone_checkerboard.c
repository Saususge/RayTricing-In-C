/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_checkerboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:00:00 by chakim            #+#    #+#             */
/*   Updated: 2025/07/08 14:56:36 by chakim           ###   ########.fr       */
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
	if (fabs(record->p_local.v[2] - 1.0f) < EPSILON)
	{
		u = atan2f(record->p_local.v[1], record->p_local.v[0]) / (float)M_PI;
		v = sqrtf(record->p_local.v[0] * record->p_local.v[0] + \
			record->p_local.v[1] * record->p_local.v[1]);
	}
	else
	{
		u = atan2f(record->p_local.v[1], \
			record->p_local.v[0]) / (float)M_PI;
		v = record->p_local.v[2];
	}
	return (checkerboard_color_at(u, v));
}
