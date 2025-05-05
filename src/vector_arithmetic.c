/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_arithmetic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:12:39 by chakim            #+#    #+#             */
/*   Updated: 2025/05/05 14:49:51 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3	vec;

	vec.x = v1.x + v2.x;
	vec.y = v1.y + v2.y;
	vec.z = v1.z + v2.z;

	return (vec);
}

t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3	vec;

	vec.x = v1.x - v2.x;
	vec.y = v1.y - v2.y;
	vec.z = v1.z - v2.z;

	return (vec);
}

t_vec3	vec3_mul(t_vec3 v, float s)
{
	t_vec3	vec;

	vec.x = v.x * s;
	vec.y = v.y * s;
	vec.z = v.z * s;

	return (vec);
}

t_vec3	vec3_div(t_vec3 v, float s)
{
	t_vec3	vec;

	vec.x = v.x / s;
	vec.y = v.y / s;
	vec.z = v.z / s;

	return (vec);
}

t_vec3	vec3_neg(t_vec3 v)
{
	t_vec3	vec;

	vec.x = -v.x;
	vec.y = -v.y;
	vec.z = -v.z;

	return (vec);
}
