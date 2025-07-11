/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:33:11 by chakim            #+#    #+#             */
/*   Updated: 2025/07/10 22:19:46 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"
#include <math.h>

static void	get_tbn_plane(t_mat *tbn)
{
	*tbn = (t_mat){{
	{1.0f, 0.0f, 0.0f, 0.0f},
	{0.0f, 1.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 1.0f, 0.0f},
	{0.0f, 0.0f, 0.0f, 0.0f}}};
}

static void	get_uv_plane(t_vec4 p_local, float *u, float *v)
{
	*u = p_local.v[0] - floorf(p_local.v[0]);
	*v = p_local.v[1] - floorf(p_local.v[1]);
}

t_vec4	get_bumpmap_normal(float u, float v);

t_vec4	get_bumped_normal_plane(t_vec4	p_local)
{
	float	u;
	float	v;
	t_mat	tbn;

	get_uv_plane(p_local, &u, &v);
	get_tbn_plane(&tbn);
	return (mat_mul_vec4(&tbn, get_bumpmap_normal(u, v)));
}

static t_vec3	plane_checkerboard_color_at(float u, float v)
{
	int	checker;

	checker = (int)(floorf(u * 2) + floorf(v * 2));
	if (checker % 2 == 0)
		return ((t_vec3){0, 0, 0});
	return ((t_vec3){255, 255, 255});
}

t_vec3	plane_get_color(const t_intersect *record)
{
	float	u;
	float	v;

	if (!record->obj->checkerboard)
		return (record->obj->color);
	u = record->p_local.v[0];
	v = record->p_local.v[1];
	return (plane_checkerboard_color_at(u, v));
}
