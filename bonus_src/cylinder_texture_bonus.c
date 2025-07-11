/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:05:15 by chakim            #+#    #+#             */
/*   Updated: 2025/07/10 22:08:57 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include <math.h>

void	get_tbn_cylinder_lateral(float u, t_vec4 n_local, t_mat *tbn)
{
	float	theta;
	t_vec3	tangent;

	theta = (u - 0.5f) * 2.0f * (float)M_PI;
	tangent = (t_vec3){-2.0f * (float)M_PI * sinf(theta),
		2.0f * (float)M_PI * cosf(theta), 0.0f};
	tangent = vec3_normalize(tangent);
	tbn->m[0][0] = tangent.x;
	tbn->m[1][0] = tangent.y;
	tbn->m[2][0] = tangent.z;
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

void	get_uv_cylinder(t_vec4 p_local, float *u, float *v)
{
	float	theta;

	theta = atan2f(p_local.v[1], p_local.v[0]);
	*u = 0.5f + theta / (2.0f * (float)M_PI);
	if (fabsf(p_local.v[2] - 0.5f) < EPSILON || \
fabsf(p_local.v[2] + 0.5f) < EPSILON)
		*v = sqrtf(p_local.v[0] * p_local.v[0] + p_local.v[1] * p_local.v[1]);
	else
		*v = p_local.v[2] + 0.5f;
}

t_vec4	get_bumped_normal_cylinder(t_vec4 p_local)
{
	float	u;
	float	v;
	t_mat	tbn;

	get_uv_cylinder(p_local, &u, &v);
	if (fabsf(p_local.v[2] - 0.5f) < EPSILON)
		tbn = (t_mat){{
		{1.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 0.0f}}};
	else if (fabsf(p_local.v[2] + 0.5f) < EPSILON)
		tbn = (t_mat){{
		{1.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, -1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, -1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 0.0f}}};
	else
		get_tbn_cylinder_lateral(u,
			(t_vec4){{p_local.v[0], p_local.v[1], 0.0f, 0.0f}}, &tbn);
	return (mat_mul_vec4(&tbn, get_bumpmap_normal(u, v)));
}

t_vec3	cylinder_get_color(const t_intersect *record)
{
	float	u;
	float	v;

	if (!record->obj->checkerboard)
		return (record->obj->color);
	get_uv_cylinder(record->p_local, &u, &v);
	return (checkerboard_color_at(u, v));
}
