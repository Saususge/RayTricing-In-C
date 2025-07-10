/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_checkerboard.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:05:15 by chakim            #+#    #+#             */
/*   Updated: 2025/07/10 20:21:36 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include <math.h>

void	get_tbn_cylinder_lateral(float theta, t_vec4 n_local, t_mat *tbn)
{
	tbn->m[0][0] = -2.0f * (float)M_PI * sinf(theta);
	tbn->m[1][0] = 2.0f * (float)M_PI * cosf(theta);
	tbn->m[2][0] = 0.0f;
	tbn->m[3][0] = 0.0f;
	tbn->m[0][1] = 0.0f;
	tbn->m[1][1] = 0.0f;
	tbn->m[2][1] = 1.0f;
	tbn->m[3][1] = 0.0f;
	tbn->m[0][2] = n_local.v[0];
	tbn->m[1][2] = n_local.v[1];
	tbn->m[2][2] = n_local.v[2];
	tbn->m[3][2] = 0.0f;
	tbn->m[0][3] = 0.0f;
	tbn->m[1][3] = 0.0f;
	tbn->m[2][3] = 0.0f;
	tbn->m[3][3] = 0.0f;
}

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
		v = sqrtf(record->p_local.v[0] * record->p_local.v[0] + \
			record->p_local.v[1] * record->p_local.v[1]);
	else
		v = 0.5f + record->p_local.v[2];
	return (checkerboard_color_at(u, v));
}
