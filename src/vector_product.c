/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_product.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:22:05 by chakim            #+#    #+#             */
/*   Updated: 2025/05/19 11:55:26 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

float	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2)
{
	return (vec3_create((v1.y * v2.z) - \
	(v1.z * v2.y), (v1.z * v2.x) - (v1.x * v2.z), \
	(v1.x * v2.y) - (v1.y * v2.x)));
}
