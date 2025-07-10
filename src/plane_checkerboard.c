/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_checkerboard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:33:11 by chakim            #+#    #+#             */
/*   Updated: 2025/07/10 20:21:23 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"
#include <math.h>

static t_vec3	plane_checkerboard_color_at(float u, float v)
{
	int	checker;

	checker = (int)(floorf(u * 0.23) + floorf(v * 0.23));
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

void	get_tbn_plane(t_mat *tbn)
{
	*tbn = (t_mat){{
	{1.0f, 0.0f, 0.0f, 0.0f},
	{0.0f, 1.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 1.0f, 0.0f},
	{0.0f, 0.0f, 0.0f, 0.0f}}};
}
