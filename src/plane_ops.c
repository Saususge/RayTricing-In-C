/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:23:09 by chakim            #+#    #+#             */
/*   Updated: 2025/07/06 22:20:27 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"
#include "vector.h"
#include "rotate.h"
#include <stdlib.h>
#include <stdio.h>

t_vec4	plane_get_normal(const t_object *obj, t_vec4 p_local)
{
	(void)obj;
	(void)p_local;
	return ((t_vec4){{0.0f, 0.0f, 1.0f, 0.0f}});
}
