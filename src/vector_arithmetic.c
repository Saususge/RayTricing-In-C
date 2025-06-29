/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_arithmetic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:12:39 by chakim            #+#    #+#             */
/*   Updated: 2025/06/29 19:40:24 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	return (vec3_create(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2)
{
	return (vec3_create(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

t_vec3	vec3_mul(t_vec3 v, float s)
{
	return (vec3_create(v.x * s, v.y * s, v.z * s));
}

t_vec3	vec3_div(t_vec3 v, float s)
{
	return (vec3_create(v.x / s, v.y / s, v.z / s));
}

t_vec3	vec3_neg(t_vec3 v)
{
	return (vec3_create(-v.x, -v.y, -v.z));
}

t_vec3	vec3_hadamard(t_vec3 v1, t_vec3 v2)
{
	return (vec3_create(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z));
}
