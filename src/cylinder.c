/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:56:47 by chakim            #+#    #+#             */
/*   Updated: 2025/07/04 21:59:42 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "vector.h"
#include "rotate.h"
#include <unistd.h>

int			cylinder_intersect(
				const t_object *this,
				const t_ray *ray,
				t_hit *hit,
				t_t_bound bound);
int			cylinder_shadow_intersect(
				const t_object *this,
				const t_ray *ray,
				t_t_bound bound);
t_vec3		cylinder_get_normal(
				const t_object *this,
				const t_point *hit_point);
void		cylinder_translate(t_object *this, t_vec3 offset);
void		cylinder_rotate(t_object *this, t_vec3 axis, float angle);

static t_object_ops	g_cylinder_ops = {
	.intersect = cylinder_intersect,
	.shadow_intersect = cylinder_shadow_intersect,
	.get_normal = cylinder_get_normal,
	.get_color = cylinder_get_color,
};

t_object	create_cylinder(struct s_cyl_data data)
{
	return ((t_object){
		.type = CYLINDER,
		.ops = &g_cylinder_ops,
		.color = data.color,
		.checkerboard = 0,
	});
}
