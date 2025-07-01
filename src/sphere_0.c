/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:00:00 by chakim            #+#    #+#             */
/*   Updated: 2025/07/01 15:00:00 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "vector.h"
#include "object.h"
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

t_vec3	sphere_get_normal(const t_object *this, const t_point *hit_point)
{
	return (vec3_mul(vec3_sub(*hit_point, \
		this->data.sphere.center), 1.0f / this->data.sphere.radius));
}

static t_object_ops	g_sphere_ops = {
	.intersect = sphere_intersect,
	.shadow_intersect = shpere_shadow_intersect,
	.get_normal = sphere_get_normal,
	.rotate = sphere_rotate,
	.translate = sphere_translate,
};

t_object	create_sphere(t_point center, float radius, t_vec3 color)
{
	return ((t_object){
		.type = SPHERE,
		.ops = &g_sphere_ops,
		.color = color,
		.data.sphere = (t_sphere){
		.center = center,
		.radius = radius,
	}
	});
}

void	calculate_sphere_equation(t_quad_eq *eq, \
	const t_sphere *sph, const t_ray *ray)
{
	t_vec3	oc;

	oc = vec3_sub(ray->origin, sph->center);
	eq->a = vec3_dot(ray->dir, ray->dir);
	eq->b = vec3_dot(oc, ray->dir);
	eq->c = vec3_dot(oc, oc) - (sph->radius * sph->radius);
	eq->disc = (eq->b * eq->b) - (eq->a * eq->c);
}

int	hit_shadow(const t_ray *ray, float t_min, float t_max)
{
	int	i;

	i = 0;
	while (i < g()->object_count)
	{
		if (g()->objects[i].ops->shadow_intersect(g()->objects + i, \
		ray, (t_t_bound){t_min, t_max}))
			return (1);
		i++;
	}
	return (0);
}
