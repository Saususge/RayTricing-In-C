/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_checkerboard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:07:12 by chakim            #+#    #+#             */
/*   Updated: 2025/07/09 18:38:12 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "vector.h"
#include <math.h>

void	get_tbn_sphere(float theta, float phi, t_vec4 n_local, t_mat *tbn)
{
	tbn->m[0][0] = -2.0f * (float)M_PI * sinf(theta) * cosf(phi);
	tbn->m[1][0] = 0.0f;
	tbn->m[2][0] = 2.0f * (float)M_PI * cosf(theta) * cosf(phi);
	tbn->m[3][0] = 0.0f;
	tbn->m[0][1] = -(float)M_PI * cosf(theta) * sinf(phi);
	tbn->m[1][1] = (float)M_PI * cosf(phi);
	tbn->m[2][1] = (float)M_PI * sinf(theta) * cosf(phi);
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

void	get_tbn_plane(t_mat *tbn)
{
	*tbn = (t_mat){{
		{1.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 0.0f}
	}};
}

void	get_theta_and_phi(t_vec4 p_local, float *theta, float *phi)
{
	*theta = atan2f(p_local.v[2], p_local.v[0]);
	*phi = asinf(p_local.v[1]);
}

t_vec3	sphere_get_color(const t_intersect *record)
{
	float	u;
	float	v;
	float	theta;
	float	phi;

	if (!record->obj->checkerboard)
		return (record->obj->color);
	get_theta_and_phi(record->p_local, &theta, &phi);
	u = 0.5f + theta / (2.0f * (float)M_PI);
	v = 0.5f + phi / (float)M_PI;
	return (checkerboard_color_at(u, v));
}
