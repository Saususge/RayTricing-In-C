/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_checkerboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:00:00 by chakim            #+#    #+#             */
/*   Updated: 2025/07/09 18:41:14 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"
#include <math.h>

void	get_tbn_cone_lateral(float theta, float z, t_vec4 n_local, t_mat *tbn)
{
	float	r;

	r = 1.0f - z;
	tbn->m[0][0] = -2.0f * (float)M_PI * r * sinf(theta);
	tbn->m[1][0] = 2.0f * (float)M_PI * r * cosf(theta);
	tbn->m[2][0] = 0.0f;
	tbn->m[3][0] = 0.0f;
	tbn->m[0][1] = -cosf(theta);
	tbn->m[1][1] = -sinf(theta);
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

t_vec4	cone_get_normal(t_vec4 p_local)
{
	t_vec4	n;
	float	norm;

	if (fabsf(p_local.v[2] - 1.0f) < EPSILON)
		return ((t_vec4){{0, 0, 1, 0}});
	n = (t_vec4){{p_local.v[0], p_local.v[1], -p_local.v[2], 0}};
	norm = sqrtf(n.v[0] * n.v[0] + n.v[1] * n.v[1] + n.v[2] * n.v[2]);
	if (norm > EPSILON)
		n = vec4_mul(n, 1.0f / norm);
	return (n);
}

static float	get_theta(t_vec4 p_local)
{
	return (atan2f(p_local.v[1], p_local.v[0]));
}

t_vec3	cone_get_color(const t_intersect *record)
{
	float	u;
	float	v;
	float	theta;

	if (!record->obj->checkerboard)
		return (record->obj->color);
	theta = get_theta(record->p_local);
	u = theta / (2.0f * (float)M_PI) + 0.5f;
	if (fabsf(record->p_local.v[2] - 1.0f) < EPSILON)
		v = sqrtf(record->p_local.v[0] * record->p_local.v[0] + \
			record->p_local.v[1] * record->p_local.v[1]);
	else
		v = record->p_local.v[2];
	return (checkerboard_color_at(u, v));
}
