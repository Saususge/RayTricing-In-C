/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:02:31 by chakim            #+#    #+#             */
/*   Updated: 2025/04/24 13:33:24 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# define WIDTH 1280;
# define HEIGHT 720;

# include <math.h>
# include "object.h"

typedef struct s_object		t_object;
typedef struct s_object_ops	t_object_ops;

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	dir;
	float	fov;
}	t_camera;

typedef struct s_sphere
{
	t_vec3	center;
	float	radius;
	t_vec3	color;
}	t_sphere;

typedef struct s_scene
{
	t_camera	cam;
	t_sphere	sp;
}	t_scene;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

void	init_test(t_scene *scene);

#endif
