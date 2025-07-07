/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:56:47 by chakim            #+#    #+#             */
/*   Updated: 2025/07/07 14:32:24 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "vector.h"
#include "rotate.h"
#include <unistd.h>

int		cylinder_intersect(const t_object *obj, const t_ray *ray_world, t_intersect *record, t_interval t_world_bound);
t_vec4		cylinder_get_normal(
				const t_object *cyl,
				t_vec4 p_local);

static t_object_ops	g_cylinder_ops = {
	.intersect = cylinder_intersect,
	.get_color = cylinder_get_color,
};

// Assume that the cylinder is centered at the origin in local space, and
// the axis is aligned with the z-axis. The height is 1 and the radius is 1.
// The `data` struct contains 
t_object	create_cylinder(struct s_cyl_data data)
{
	return ((t_object){
		.type = CYLINDER,
		.ops = &g_cylinder_ops,
		.color = data.color,
		.checkerboard = 0,
	});
}
