/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_length.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:25:13 by chakim            #+#    #+#             */
/*   Updated: 2025/05/05 15:31:34 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "test.h"

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
	t_vec3	vec;
	float	mag;

	mag = vec3_length(v);
	if (mag < 0.00001f)
		return (vec3_create(0.0f, 0.0f, 0.0f));
	vec.x = v.x / mag;
	vec.y = v.y / mag;
	vec.z = v.z / mag;

	return (vec);
}
