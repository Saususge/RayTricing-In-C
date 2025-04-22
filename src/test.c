/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:56:33 by chakim            #+#    #+#             */
/*   Updated: 2025/04/22 17:06:24 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "mlx.h"

void	init_test(t_scene *scene)
{
	scene->cam.pos = (t_vec3){0, 0, -20};
	scene->cam.dir = (t_vec3){0, 0, 1};
	scene->cam.fov = 70;
	scene->sp.center = (t_vec3){0, 0, 20};
	scene->sp.radius = 10;
	scene->sp.color = (t_vec3){255, 0, 0};
}

t_ray	generate_camera_ray(int x, int y, t_camera cam)
{
	t_ray	ray;

	ray.origin = cam.pos;
	
}

void	render_test(t_scene *scene)
{
    for (int y = 0; y < HEIGHT; ++y)
	{
        for (int x = 0; x < WIDTH; ++x) 
		{
			t_ray ray = generate_camera_ray(x, y, scene->cam);
			if (ray_hits_sphere(ray, scene->sp))
				draw_pixel(x, y, scene->sp.color);
			else
                draw_pixel(x, y, (t_vec3){0, 0, 0});
        }
    }
}
