/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:48:33 by chakim            #+#    #+#             */
/*   Updated: 2025/05/09 17:01:45 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	point_to_vec3(t_point p)
{
	return (vec3_create(p.x, p.y, p.z));
}

t_point	vec3_to_point(t_vec3 v)
{
	return (point_create(v.x, v.y, v.z));
}
