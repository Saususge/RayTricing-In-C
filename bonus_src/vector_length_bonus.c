/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_length.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:25:13 by chakim            #+#    #+#             */
/*   Updated: 2025/07/04 16:00:49 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

float	vec3_length_squared(t_vec3 v)
{
	return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

float	vec3_length(t_vec3 v)
{
	return (sqrtf(vec3_length_squared(v)));
}

t_vec3	vec3_normalize(t_vec3 v)
{
	float	mag;

	mag = vec3_length(v);
	if (mag < EPSILON)
		return (vec3_create(0.0f, 0.0f, 0.0f));
	return (vec3_create(v.x / mag, v.y / mag, v.z / mag));
}
