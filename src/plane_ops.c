/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:23:09 by chakim            #+#    #+#             */
/*   Updated: 2025/07/04 21:59:07 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"
#include "vector.h"
#include "rotate.h"
#include <stdlib.h>
#include <stdio.h>

t_vec3	plane_get_normal(const t_object *this, const t_point *hit_point)
{
	(void)hit_point;
	return (this->data.plane.normal);
}
