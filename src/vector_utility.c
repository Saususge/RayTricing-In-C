/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:55:31 by chakim            #+#    #+#             */
/*   Updated: 2025/05/09 16:56:47 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "test.h"

float	vec3_angle(t_vec3 v1, t_vec3 v2)
{
	float	dot;
	float	mag;
	float	cos_theta;

	dot = vec3_dot(v1, v2);
	mag = vec3_length(v1) * vec3_length(v2);
	if (mag < EPSILON)
		return (0.0f);
	cos_theta = dot / mag;
	return (acosf(cos_theta));
}

t_vec3	vec3_lerp(t_vec3 v1, t_vec3 v2, float t)
{
	t_vec3	vec;

	vec.x = v1.x + (v2.x - v1.x) * t;
	vec.y = v1.y + (v2.y - v1.y) * t;
	vec.z = v1.z + (v2.z - v1.z) * t;
	return (vec);
}

int	is_vec3_near_to_zero(t_vec3 v)
{
	if (vec3_length_squared(v) < EPSILON * EPSILON)
		return (1);
	return (0);
}

t_vec3	vec3_min(t_vec3 v1, t_vec3 v2)
{
	t_vec3	vec;

	vec.x = fminf(v1.x, v2.x);
	vec.y = fminf(v1.y, v2.y);
	vec.z = fminf(v1.z, v2.z);
	return (vec);
}

t_vec3	vec3_max(t_vec3 v1, t_vec3 v2)
{
	t_vec3	vec;

	vec.x = fmaxf(v1.x, v2.x);
	vec.y = fmaxf(v1.y, v2.y);
	vec.z = fmaxf(v1.z, v2.z);
	return (vec);
}
