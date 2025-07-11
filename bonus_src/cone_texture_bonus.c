/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:00:00 by chakim            #+#    #+#             */
/*   Updated: 2025/07/10 21:58:10 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"
#include <math.h>

void	get_tbn_cone_lateral(float theta, float z, t_vec4 n_local, t_mat *tbn)
{
	t_vec3	tangent;
	t_vec3	bitangent;

	tangent = (t_vec3){-2.0f * (float)M_PI * (1.0f - z) * sinf(theta),
		2.0f * (float)M_PI * (1.0f - z) * cosf(theta), 0.0f};
	tangent = vec3_normalize(tangent);
	tbn->m[0][0] = tangent.x;
	tbn->m[1][0] = tangent.y;
	tbn->m[2][0] = tangent.z;
	tbn->m[3][0] = 0.0f;
	bitangent = vec3_cross((t_vec3){n_local.v[0], n_local.v[1], n_local.v[2]},
			tangent);
	tbn->m[0][1] = bitangent.x;
	tbn->m[1][1] = bitangent.y;
	tbn->m[2][1] = bitangent.z;
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

void	get_uv_cone(t_vec4 p_local, float *u, float *v)
{
	float	theta;

	theta = atan2f(p_local.v[1], p_local.v[0]);
	*u = 0.5f + theta / (2.0f * (float)M_PI);
	if (fabsf(p_local.v[2] - 1.0f) < EPSILON)
		*v = sqrtf(p_local.v[0] * p_local.v[0] + p_local.v[1] * p_local.v[1]);
	else
		*v = p_local.v[2];
}

t_vec4	get_bumped_normal_cone(t_vec4 p_local)
{
	float	u;
	float	v;
	t_mat	tbn;
	t_vec4	normal;

	get_uv_cone(p_local, &u, &v);
	if (fabsf(p_local.v[2] - 1.0f) < EPSILON)
		tbn = (t_mat){{
		{1.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 0.0f}}};
	else
	{
		normal = (t_vec4){{p_local.v[0], p_local.v[1], -p_local.v[2], 0}};
		normal = vec4_mul(normal, 1.0f / sqrtf(vec4_dot(normal, normal)));
		get_tbn_cone_lateral((u - 0.5f) * 2.0f * (float)M_PI,
			p_local.v[2], normal, &tbn);
	}
	return (mat_mul_vec4(&tbn, get_bumpmap_normal(u, v)));
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

t_vec3	cone_get_color(const t_intersect *record)
{
	float	u;
	float	v;

	if (!record->obj->checkerboard)
		return (record->obj->color);
	get_uv_cone(record->p_local, &u, &v);
	return (checkerboard_color_at(u, v));
}
