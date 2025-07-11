/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_arithmetic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:12:39 by chakim            #+#    #+#             */
/*   Updated: 2025/07/01 09:16:56 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

t_vec3	vec3_mul(t_vec3 v, float s)
{
	return ((t_vec3){v.x * s, v.y * s, v.z * s});
}

t_vec3	vec3_div(t_vec3 v, float s)
{
	return ((t_vec3){v.x / s, v.y / s, v.z / s});
}

t_vec3	vec3_neg(t_vec3 v)
{
	return ((t_vec3){-v.x, -v.y, -v.z});
}
