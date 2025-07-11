/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:05:15 by chakim            #+#    #+#             */
/*   Updated: 2025/07/10 20:28:00 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"
# include "viewport.h"
# include "matrix.h"

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
	t_vec3		pos;
	t_vec3		dir;
	float		fov;
}	t_camera;

// intensity: 0.0 to 1.0
typedef struct t_light
{
	t_vec4		position;
	t_vec3		intensity;
}	t_light;

typedef struct s_ray
{
	t_vec4	o;
	t_vec4	d;
}	t_ray;

// T-> translation
// R -> rotation
// S -> scaling
// M -> TRS: local to world
// M_inv -> M^-1: world to local
typedef struct s_object
{
	t_type			type;
	t_object_ops	*ops;
	t_vec3			color;
	int				checkerboard;
	t_mat			t;
	t_mat			r;
	t_mat			s;
	t_mat			m;
	t_mat			m_inv;
	t_mat			n;
	int				bump;
}	t_object;

typedef struct s_intersect
{
	float		t;
	t_vec4		p_local;
	t_vec4		n_world;
	t_object	*obj;
}	t_intersect;

typedef struct s_hit
{
	float		t;
	t_vec4		point;
	t_vec4		normal;
	t_vec3		color;
	t_object	*object;
	int			is_front_face;
}	t_hit;

typedef struct s_t_bound
{
	float	min;
	float	max;
}	t_interval;

typedef struct s_object_ops
{
	int	
		(*intersect)(const t_object *obj, const t_ray *ray_world,
			t_intersect *intersect_record, t_interval t_world_bound);
	t_vec3
		(*get_color)(const t_intersect *record);
}	t_object_ops;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_tex
{
	unsigned char	*tex;
	int				width;
	int				height;
	int				orig_channel;
}	t_tex;

typedef struct render_data
{
	void	*mlx;
	void	*mlx_win;
	t_data	*img;
}	t_render_data;

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
	int				camera_choosed;
	int				light_choosed;
	int				light_index;
	t_viewport		viewport;
	t_object		*choosen_object;
	t_data			img;
	t_tex			tex;
	void			*mlx;
	void			*mlx_win;
}	t_gvar;

t_gvar	*g(void);
int		process_object_arr_size(void);
void	populate_hit_record(
			t_hit *hit, float t, const t_ray *ray, const t_object *obj);
t_vec3	checkerboard_color_at(float u, float v);
#endif