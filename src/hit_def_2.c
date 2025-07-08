/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_def_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 00:00:00 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/08 00:00:00 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"
#include "object.h"

int	hit_ray(const t_ray *ray_world, t_interval bound_world, \
	t_intersect *intersect_record, t_vec3 *color)
{
	int			hit_anything;
	int			i;
	t_intersect	current_intersect;

	hit_anything = 0;
	i = 0;
	while (i < g()->object_count)
	{
		if (g()->objects[i].ops->intersect(g()->objects + i, ray_world,
				&current_intersect, bound_world))
		{
			hit_anything = 1;
			bound_world.max = current_intersect.t;
			*intersect_record = current_intersect;
		}
		++i;
	}
	if (hit_anything)
		*color = get_color(intersect_record);
	return (hit_anything);
}

int	hit_shadow_ray(const t_ray *shadow_ray_world, t_interval bound_world)
{
	t_intersect	dump;
	int			i;

	i = 0;
	while (i < g()->object_count)
	{
		if (g()->objects[i].ops->intersect(g()->objects + i,
				shadow_ray_world, &dump, bound_world))
			return (1);
		++i;
	}
	return (0);
}
