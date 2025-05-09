/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:52:06 by chakim            #+#    #+#             */
/*   Updated: 2025/05/09 16:55:46 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

float	point_distance_squared(t_point p1, t_point p2)
{
	return (powf(p2.x - p1.x, 2) + \
powf(p2.y - p1.y, 2) + powf(p2.z - p1.z, 2));
}

float	point_distance(t_point p1, t_point p2)
{
	return (sqrtf(point_distance_squared(p1, p2)));
}

t_point	point_add_vec(t_point p, t_vec3 v)
{
	t_point	result;

	result.x = p.x + v.x;
	result.y = p.y + v.y;
	result.z = p.z + v.z;
	return (result);
}
