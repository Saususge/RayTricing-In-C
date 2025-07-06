/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_checkerboard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:07:12 by chakim            #+#    #+#             */
/*   Updated: 2025/07/06 18:30:45 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "vector.h"
#include <math.h>

t_vec3	sphere_get_color(const t_intersect *record)
{
	float	u;
	float	v;

	if (!record->obj->checkerboard)
		return (record->obj->color);
	u = 0.5f + atan2f(record->p_local.v[2], record->p_local.v[0]) / (2.0f * (float)M_PI);
	v = 0.5f - asinf(record->p_local.v[1]) / (float)M_PI;
	return (checkerboard_color_at(u, v));
}
