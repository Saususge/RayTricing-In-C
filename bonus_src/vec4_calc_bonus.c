/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 14:18:59 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/08 15:33:57 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec4	vec4_normalize(t_vec4 a)
{
	float	length;

	length = sqrtf(a.v[0] * a.v[0] + a.v[1] * a.v[1] + a.v[2] * a.v[2]);
	if (length < EPSILON)
		return ((t_vec4){{0, 0, 0, 0}});
	return (vec4_div(a, length));
}

float	vec4_dot(t_vec4 a, t_vec4 b)
{
	return (a.v[0] * b.v[0] + a.v[1] * \
		b.v[1] + a.v[2] * b.v[2] + a.v[3] * b.v[3]);
}
