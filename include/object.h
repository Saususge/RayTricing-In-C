/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:05:15 by chakim            #+#    #+#             */
/*   Updated: 2025/06/26 16:08:05 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"

typedef struct s_object		t_object;
typedef struct s_object_ops	t_object_ops;

typedef enum e_type
{
	SPHERE = 0,
	PLANE = 1
}	t_type;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

// intensity: 0.0 to 1.0
typedef struct s_ambient_light
{
	t_color	color;
	float	intensity;
}	t_ambient_light;

// orientation: normalized vector
// fov: 0 to 180
typedef struct t_camera
{
	t_point		position;
	t_vec3		orientation;
	float		fov;
}	t_camera;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
	t_color	color;
}	t_ray;

typedef struct s_object
{
	t_type			type;
	t_object_ops	*ops;
	void			*data;
}	t_object;

typedef struct s_hit
{
	float		t;
	t_point		point;
	t_vec3		normal;
	t_color		color;
	t_object	*object;
	int			is_front_face;
}	t_hit;

typedef struct s_object_ops
{
	int			((*intersect)(struct s_object *this, t_ray *ray,
				t_hit *hit));
	t_vec3		((*get_normal)(struct s_object * this,
			t_point * hit_point,
			t_ray * ray));
	void		(*rotate)(struct s_object *this,
			t_vec3 angle);
	void		((*translate)(struct s_object *this,
				t_vec3 offset));
	t_color		((*get_color)(struct s_object * this,
			t_point * hit_point));
	void		(*free)(struct s_object *this);
}	t_object_ops;

#endif