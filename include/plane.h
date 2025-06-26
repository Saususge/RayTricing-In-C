/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:08:13 by chakim            #+#    #+#             */
/*   Updated: 2025/06/26 23:45:19 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "object.h"
# include "vector.h"
# include "test.h"

typedef struct s_plane
{
	t_point	point;
	t_vec3	normal;
	t_color	color;
}	t_plane;

t_object	*create_plane(t_point point, t_vec3 normal, t_color color);
int			plane_intersect(t_object *this, t_ray *ray, t_hit *hit);

#endif