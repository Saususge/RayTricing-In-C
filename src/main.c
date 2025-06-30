/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:56:19 by chakim            #+#    #+#             */
/*   Updated: 2025/06/30 17:01:48 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <unistd.h>
#include <fcntl.h>
#include "parse.h"
#include "sphere.h"
#include "plane.h"
#include "object.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	hit_objects(const t_ray *ray, float t_min, float t_max, t_hit *hit)
{
	t_hit	current_hit;
	int		hit_anything = 0;
	float	closest_so_far = t_max;

	for (int i = 0; i < g()->object_count; ++i)
	{
		if (g()->objects[i].ops->intersect(g()->objects + i, ray,
			&current_hit, (t_t_bound){t_min, closest_so_far}))
		{
			hit_anything = 1;
			closest_so_far = current_hit.t;
			*hit = current_hit;
		}
	}
	return (hit_anything);
}

#include "event.h"

void	init_viewport(void)
{
	g()->viewport.aspect_ratio = 21.0f / 9.0f;
	g()->viewport.width = 1680;
	g()->viewport.height = (int)(g()->viewport.width / g()->viewport.aspect_ratio);
	g()->viewport.focal_length = 1.0f;
	g()->viewport.view_w = 2.0f * g()->viewport.focal_length * tan(g()->cam.fov * M_PI / 360.0f);
	g()->viewport.view_h = g()->viewport.view_w / g()->viewport.aspect_ratio;
	g()->viewport.vup = vec3_create(0.0f, 1.0f, 0.0f);
	g()->viewport.view_u = vec3_mul(
		vec3_normalize(vec3_cross(g()->cam.dir, g()->viewport.vup)),
		g()->viewport.view_w);
	g()->viewport.view_v = vec3_mul(
		vec3_normalize(vec3_cross(g()->viewport.view_u, g()->cam.dir)),
		-g()->viewport.view_h);
	g()->viewport.view_u_per_pixel = vec3_mul(g()->viewport.view_u,
		1.0f / (float)g()->viewport.width);
	g()->viewport.view_v_per_pixel = vec3_mul(g()->viewport.view_v,
		1.0f / (float)g()->viewport.height);
	g()->viewport.view_upper_left = vec3_sub(g()->cam.pos,
		vec3_add(
			vec3_mul(g()->cam.dir, -g()->viewport.focal_length),
			vec3_add(
				vec3_mul(g()->viewport.view_u, 0.5f),
				vec3_mul(g()->viewport.view_v, 0.5f))));
	g()->viewport.pixel_origin = vec3_add(g()->viewport.view_upper_left,
		vec3_mul(vec3_add(g()->viewport.view_v_per_pixel, g()->viewport.view_u_per_pixel), 0.5f));
}

void	translate(t_vec3 offset)
{
	if (g()->camera_choosed)
	{
		g()->cam.pos = vec3_add(g()->cam.pos, offset);
		init_viewport();
	}
	else if (g()->light_choosed)
		g()->lights[g()->light_index].position = vec3_add(g()->lights[g()->light_index].position, offset);
	else if (g()->choosen_object)
		g()->choosen_object->ops->translate(g()->choosen_object, offset);
}

#include "rotate.h"

void	rotate(t_vec3 angle)
{
	if (g()->camera_choosed)
	{
		g()->cam.dir = vec3_normalize(rotate_vector(g()->cam.dir, angle));
		init_viewport();
	}
	else if (g()->light_choosed)
		printf("Cannot rotate light\n");
	else if (g()->choosen_object)
		g()->choosen_object->ops->rotate(g()->choosen_object, angle);
}



void	render(void);

int	key_hook(int keycode, void *mlx)
{
	if (keycode == ESC)
	{
		mlx_loop_end(mlx);
		return (0);
	}
	else if (keycode == '1')
	{
		g()->camera_choosed = 1;
		g()->light_choosed = 0;
		printf("Camera selected\n");
		return (0);
	}
	else if (keycode == '2')
	{
		g()->camera_choosed = 0;
		if (g()->light_choosed)
			g()->light_index = (g()->light_index + 1) % g()->light_count;
		g()->light_choosed = 1;
		printf("Light %d selected\n", g()->light_index + 1);
		return (0);
	}
	else if (keycode == 'q')
		translate((t_vec3){0.1f, 0.0f, 0.0f});
	else if (keycode == 'a')
		translate((t_vec3){-0.1f, 0.0f, 0.0f});
	else if (keycode == 'w')
		translate((t_vec3){0.0f, 0.1f, 0.0f});
	else if (keycode == 's')
		translate((t_vec3){0.0f, -0.1f, 0.0f});
	else if (keycode == 'e')
		translate((t_vec3){0.0f, 0.0f, 0.1f});
	else if (keycode == 'd')
		translate((t_vec3){0.0f, 0.0f, -0.1f});
	else if (keycode == 'p')
		rotate((t_vec3){22.5, 0, 0});
	else if (keycode == 'l')
		rotate((t_vec3){-22.5, 0, 0});
	else if (keycode == '[')
		rotate((t_vec3){0, 22.5, 0});
	else if (keycode == ';')
		rotate((t_vec3){0, -22.5, 0});
	else if (keycode == ']')
		rotate((t_vec3){0, 0, 22.5});
	else if (keycode == '\'')
		rotate((t_vec3){0, 0, -22.5});
	else
		return (0);
	render();
	mlx_put_image_to_window(mlx, g()->mlx_win, g()->img.img, 0, 0);
	return (0);
}

int	mouse_hook(int button, int x, int y, void *mlx)
{
	(void)mlx;
	if (button == 1) // Left mouse button
	{
		t_vec3 pixel_pos = vec3_add(g()->viewport.pixel_origin, vec3_add(vec3_mul(g()->viewport.view_u_per_pixel, (float)x), vec3_mul(g()->viewport.view_v_per_pixel, (float)y)));
		t_vec3 ray_dir = vec3_normalize(vec3_sub(pixel_pos, g()->cam.pos));
		t_ray ray = {.origin = g()->cam.pos, .dir = ray_dir};
		t_hit hit;
		if (hit_objects(&ray, 0.0f, INFINITY, &hit))
		{
			g()->camera_choosed = 0;
			g()->light_choosed = 0;
			g()->choosen_object = hit.object;
			printf("Object %ld(%s) selected\n",
				g()->choosen_object - g()->objects + 1,
				g()->choosen_object->type == SPHERE ? "Sphere" :
				g()->choosen_object->type == PLANE ? "Plane" :
				g()->choosen_object->type == CYLINDER ? "Cylinder" : "Unknown");
		}
	}
	else if (button == 2) // Right mouse button
		printf("Mouse right button clicked at (%d, %d)\n", x, y);
	else if (button == 3) // Middle mouse button
		printf("Mouse middle button clicked at (%d, %d)\n", x, y);
	return (0);
}

void	render(void)
{
	clock_t start_time = clock();
	for (int y = 0; y < g()->viewport.height; ++y)
	{
		for (int x = 0; x < g()->viewport.width; ++x)
		{
			t_vec3 pixel_pos = vec3_add(g()->viewport.pixel_origin, vec3_add(vec3_mul(g()->viewport.view_u_per_pixel, (float)x), vec3_mul(g()->viewport.view_v_per_pixel, (float)y)));
			t_vec3 ray_direction = vec3_normalize(vec3_sub(pixel_pos, g()->cam.pos));
			t_ray ray = {.origin = g()->cam.pos, .dir = ray_direction};
			t_hit hit;
			hit.color = (t_vec3){0.0f, 0.0f, 0.0f};
			hit_objects(&ray, 0.0f, INFINITY, &hit);
			my_mlx_pixel_put(&g()->img, x, y, (int)hit.color.x << 16 | (int)hit.color.y << 8 | (int)hit.color.z);
		}
	}
	clock_t end_time = clock();
	double elapsed_sec = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	printf("Rendering time: %.3f seconds\n", elapsed_sec);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./miniRT <scene_file>\n", STDERR_FILENO);
		return (1);
	}
	int	fd = open(argv[1], O_RDONLY);
	if (parse(fd))
	{
		ft_putstr_fd("Error: Failed to parse scene file.\n", 2);
		free(g()->lights);
		free(g()->objects);
		return (1);
	}
	close(fd);
	init_viewport();
	g()->mlx = mlx_init();
	g()->mlx_win = mlx_new_window(g()->mlx, g()->viewport.width, g()->viewport.height, "miniRT");
	mlx_key_hook(g()->mlx_win, key_hook, g()->mlx);
	mlx_mouse_hook(g()->mlx_win, mouse_hook, g()->mlx);
	mlx_hook(g()->mlx_win, 33, 0, mlx_loop_end, g()->mlx);
	g()->img.img = mlx_new_image(g()->mlx, g()->viewport.width, g()->viewport.height);
	g()->img.addr = mlx_get_data_addr(g()->img.img, &g()->img.bits_per_pixel, &g()->img.line_length, &g()->img.endian);
	render();
	mlx_put_image_to_window(g()->mlx, g()->mlx_win, g()->img.img, 0, 0);
	mlx_loop(g()->mlx);
	mlx_destroy_image(g()->mlx, g()->img.img);
	mlx_destroy_window(g()->mlx, g()->mlx_win);
	mlx_destroy_display(g()->mlx);
	free(g()->mlx);
	free(g()->lights);
	free(g()->objects);
	return (0);
}
