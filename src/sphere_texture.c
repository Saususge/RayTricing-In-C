/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:07:12 by chakim            #+#    #+#             */
/*   Updated: 2025/07/10 20:20:48 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "vector.h"
#include <math.h>

static void	get_t_sphere(float theta, float phi, t_vec3 *t)
{
	*t = (t_vec3){
		-2.0f * (float)M_PI * sinf(theta) * cosf(phi),
		0.0f,
		2.0f * (float)M_PI * cosf(theta) * cosf(phi)};
	*t = vec3_normalize(*t);
}

static void	get_tbn_sphere(float u, float v, t_vec4 n_local, t_mat *tbn)
{
	t_vec3	tangent_v;
	t_vec3	bitangent_v;

	get_t_sphere((u - 0.5f) * 2.0f * (float)M_PI,
		(v - 0.5f) * (float)M_PI, &tangent_v);
	tbn->m[0][0] = tangent_v.x;
	tbn->m[1][0] = tangent_v.y;
	tbn->m[2][0] = tangent_v.z;
	tbn->m[3][0] = 0.0f;
	bitangent_v = vec3_cross((t_vec3){n_local.v[0], n_local.v[1], n_local.v[2]},
			tangent_v);
	tbn->m[0][1] = bitangent_v.x;
	tbn->m[1][1] = bitangent_v.y;
	tbn->m[2][1] = bitangent_v.z;
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

void	get_uv_sphere(t_vec4 p_local, float *u, float *v)
{
	float	theta;
	float	phi;

	theta = atan2f(p_local.v[2], p_local.v[0]);
	phi = asinf(p_local.v[1]);
	*u = 0.5f + theta / (2.0f * (float)M_PI);
	*v = 0.5f + phi / (float)M_PI;
}

t_vec4	get_bumped_normal_sphere(t_vec4	p_local)
{
	float	u;
	float	v;
	t_mat	tbn;

	get_uv_sphere(p_local, &u, &v);
	get_tbn_sphere(u, v, sphere_get_normal(p_local), &tbn);
	return (mat_mul_vec4(&tbn, get_bumpmap_normal(u, v)));
}

t_vec3	sphere_get_color(const t_intersect *record)
{
	float	u;
	float	v;

	if (!record->obj->checkerboard)
		return (record->obj->color);
	get_uv_sphere(record->p_local, &u, &v);
	return (checkerboard_color_at(u, v));
}
