/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:12:52 by chakim            #+#    #+#             */
/*   Updated: 2025/05/26 16:23:09 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"
#include "unistd.h"

static t_object_ops	g_plane_ops = {
	.intersect = &plane_intersect,
	.get_normal = NULL,
	.rotate = NULL,
	.translate = NULL,
	.get_color = NULL,
	.free = NULL
};

t_object	*create_plane(t_point point, t_vec3 normal, t_vec3 color)
{
	t_object	*obj;
	t_plane		*pl;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	pl = malloc(sizeof(t_plane));
	if (!pl)
	{
		free(obj);
		return (NULL);
	}
	pl->point = point;
	pl->normal = normal;
	pl->color = color;
	obj->type = PLANE;
	obj->data = pl;
	obj->ops = &g_plane_ops;
	return (obj);
}

int	plane_intersect(t_object *this, t_ray *ray, t_hit *hit)
{
	;
}
