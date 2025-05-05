/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_product.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:22:05 by chakim            #+#    #+#             */
/*   Updated: 2025/05/05 14:25:04 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

float	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	float	dot;

	dot = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);

	return (dot);
}

t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3	vec;

	vec.x = (v1.y * v2.z) - (v1.z * v2.y);
	vec.y = (v1.z * v2.x) - (v1.x * v2.z);
	vec.z = (v1.x * v2.y) - (v1.y * v2.x);

	return (vec);
}
