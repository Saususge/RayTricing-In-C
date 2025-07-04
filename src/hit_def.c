/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_def.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:20:25 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/04 17:20:25 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"
#include "object.h"

int	hit_objects(const t_ray *ray, float t_min, float t_max, t_hit *hit)
{
	t_hit	current_hit;
	int		hit_anything;
	float	closest_so_far;
	int		i;

	closest_so_far = t_max;
	hit_anything = 0;
	i = 0;
	while (i < g()->object_count)
	{
		if (g()->objects[i].ops->intersect(g()->objects + i, ray,
				&current_hit, (t_t_bound){t_min, closest_so_far}))
		{
			hit_anything = 1;
			closest_so_far = current_hit.t;
			*hit = current_hit;
		}
		++i;
	}
	return (hit_anything);
}

int	hit_shadow(const t_ray *ray, float t_min, float t_max)
{
	int	i;

	i = 0;
	while (i < g()->object_count)
	{
		if (g()->objects[i].ops->shadow_intersect(g()->objects + i,
				ray, (t_t_bound){t_min, t_max}))
			return (1);
		i++;
	}
	return (0);
}
