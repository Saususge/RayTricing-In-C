/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:25:53 by chakim            #+#    #+#             */
/*   Updated: 2025/06/26 19:02:46 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	vec3_create(float x, float y, float z)
{
	return ((t_vec3){x, y, z});
}

t_point	point_create(float x, float y, float z)
{
	return ((t_point){x, y, z});
}
