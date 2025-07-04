/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:05:15 by chakim            #+#    #+#             */
/*   Updated: 2025/07/04 16:58:02 by chakim           ###   ########.fr       */
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
	PLANE = 1,
	CYLINDER = 2,
	CONE = 3,
}	t_type;

// intensity: 0.0 to 1.0
typedef struct s_ambient_light
{
	t_vec3	intensity;
}	t_ambient_light;

// dir: normalized vector
// fov: 0 to 180
typedef struct t_camera
{
	t_point		pos;
	t_vec3		dir;
	float		fov;
}	t_camera;

// intensity: 0.0 to 1.0
typedef struct t_light
{
	t_point		position;
	t_vec3		intensity;
}	t_light;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}	t_ray;

typedef struct s_sphere
{
	t_point	center;
	float	radius;
}	t_sphere;

typedef struct s_plane
{
	t_point	point;
	t_vec3	normal;
}	t_plane;

typedef struct s_cylinder
{
	t_point		p1;
	t_point		p2;
	t_point		center;
	t_vec3		axis;
	float		radius;
	float		height;
}	t_cylinder;

typedef struct s_cone
{
	t_point	center;
	t_vec3	axis;
	float	height;
	float	radius;
}	t_cone;

typedef union u_obj_data
{
	struct s_sphere		sphere;
	struct s_plane		plane;
	struct s_cylinder	cylinder;
	struct s_cone		cone;
}	t_obj_data;

typedef struct s_object
{
	t_type			type;
	t_object_ops	*ops;
	t_obj_data		data;
	t_vec3			color;
	int				checkerboard;
}	t_object;

typedef struct s_hit
{
	float		t;
	t_point		point;
	t_vec3		normal;
	t_vec3		color;
	t_object	*object;
	int			is_front_face;
}	t_hit;

typedef struct s_t_bound
{
	float	min;
	float	max;
}	t_t_bound;

typedef struct s_object_ops
{
	int	
		(*intersect)(const t_object *this, const t_ray *ray,
			t_hit *hit, t_t_bound bound);
	int
		(*shadow_intersect)(const t_object *this,
			const t_ray *ray, t_t_bound bound);
	void
		(*rotate)(t_object *this, t_vec3 axis, float angle);
	void
		(*translate)(t_object *this, t_vec3 offset);
	t_vec3
		(*get_normal)(
			const t_object	*this,
			const t_point	*hit_point
			);
	void	(*scale)(t_object *this, float scale);
}	t_object_ops;

typedef struct s_viewport
{
	int		width;
	int		height;
	float	aspect_ratio;
	float	focal_length;
	float	view_w;
	float	view_h;
	t_vec3	vup;
	t_vec3	view_u;
	t_vec3	view_v;
	t_vec3	view_u_per_pixel;
	t_vec3	view_v_per_pixel;
	t_vec3	view_upper_left;
	t_vec3	pixel_origin;
}	t_viewport;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_gvar
{
	t_ambient_light	amb_light;
	t_camera		cam;
	t_light			*lights;
	int				light_count;
	int				light_capacity;
	t_object		*objects;
	int				object_count;
	int				object_capacity;
	float			k_a;
	float			k_d;
	float			k_s;
	int				camera_choosed;
	int				light_choosed;
	int				light_index;
	t_viewport		viewport;
	t_object		*choosen_object;
	t_data			img;
	void			*mlx;
	void			*mlx_win;
}	t_gvar;

t_gvar	*g(void);
int		process_object_arr_size(void);
void	populate_hit_record(
			t_hit *hit, float t, const t_ray *ray, const t_object *obj);
t_vec3	checkerboard_color_at(float u, float v);
#endif