/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_checkerboard.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:05:15 by chakim            #+#    #+#             */
/*   Updated: 2025/07/08 14:56:31 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include <math.h>

t_vec3	cylinder_get_color(const t_intersect *record)
{
	float	u;
	float	v;

	if (!record->obj->checkerboard)
		return (record->obj->color);
	if (fabs(record->p_local.v[2] - 0.5f) < EPSILON || \
	fabs(record->p_local.v[2] + 0.5f) < EPSILON)
	{
		u = atan2f(record->p_local.v[1], record->p_local.v[0]) / (float)M_PI;
		v = sqrtf(record->p_local.v[0] * record->p_local.v[0] + \
			record->p_local.v[1] * record->p_local.v[1]);
	}
	else
	{
		u = asinf(record->p_local.v[1]) / (float)M_PI;
		v = 0.5f + record->p_local.v[2];
	}
	return (checkerboard_color_at(u, v));
}
