/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:53:23 by chakim            #+#    #+#             */
/*   Updated: 2025/07/04 18:00:12 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "object.h"
#include "vector.h"
#include "plane.h"
#include "sphere.h"
#include "cone.h"
#include "cylinder.h"

t_vec3	checkerboard_color_at(float u, float v)
{
	int	checker;

	checker = (int)(floorf(u * 10) + floorf(v * 10));
	if (checker % 2 == 0)
		return ((t_vec3){0, 0, 0});
	return ((t_vec3){255, 255, 255});
}
