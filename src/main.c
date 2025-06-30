/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:56:19 by chakim            #+#    #+#             */
/*   Updated: 2025/06/30 14:21:32 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "draw_pixels.h"
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

	for (int i = 0; i < g_object_count; ++i)
	{
		if (g_objects[i].ops->intersect(g_objects + i, ray,
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

int	g_camera_choosed;
int	g_light_choosed;
int	g_light_index;
t_viewport	g_viewport;
t_object	*g_choosen_object;

void	init_viewport(void)
{
	g_viewport.aspect_ratio = 21.0f / 9.0f;
	g_viewport.width = 1680;
	g_viewport.height = (int)(g_viewport.width / g_viewport.aspect_ratio);
	g_viewport.focal_length = 1.0f;
	g_viewport.view_w = 2.0f * g_viewport.focal_length * tan(g_cam.fov * M_PI / 360.0f);
	g_viewport.view_h = g_viewport.view_w / g_viewport.aspect_ratio;
	g_viewport.vup = vec3_create(0.0f, 1.0f, 0.0f);
	g_viewport.view_u = vec3_mul(
		vec3_normalize(vec3_cross(g_cam.dir, g_viewport.vup)),
		g_viewport.view_w);
	g_viewport.view_v = vec3_mul(
		vec3_normalize(vec3_cross(g_viewport.view_u, g_cam.dir)),
		-g_viewport.view_h);
	g_viewport.view_u_per_pixel = vec3_mul(g_viewport.view_u,
		1.0f / (float)g_viewport.width);
	g_viewport.view_v_per_pixel = vec3_mul(g_viewport.view_v,
		1.0f / (float)g_viewport.height);
	g_viewport.view_upper_left = vec3_sub(g_cam.pos,
		vec3_add(
			vec3_mul(g_cam.dir, -g_viewport.focal_length),
			vec3_add(
				vec3_mul(g_viewport.view_u, 0.5f),
				vec3_mul(g_viewport.view_v, 0.5f))));
	g_viewport.pixel_origin = vec3_add(g_viewport.view_upper_left,
		vec3_mul(vec3_add(g_viewport.view_v_per_pixel, g_viewport.view_u_per_pixel), 0.5f));
}

void	translate(t_vec3 offset)
{
	if (g_camera_choosed)
	{
		g_cam.pos = vec3_add(g_cam.pos, offset);
		init_viewport();
	}
	else if (g_light_choosed)
		g_lights[g_light_index].position = vec3_add(g_lights[g_light_index].position, offset);
	else if (g_choosen_object)
		g_choosen_object->ops->translate(g_choosen_object, offset);
}

#include "rotate.h"

void	rotate(t_vec3 angle)
{
	if (g_camera_choosed)
	{
		g_cam.dir = vec3_normalize(rotate_vector(g_cam.dir, angle));
		init_viewport();
	}
	else if (g_light_choosed)
		printf("Cannot rotate light\n");
	else if (g_choosen_object)
		g_choosen_object->ops->rotate(g_choosen_object, angle);
}

t_data	g_img;
void	*g_mlx;
void	*g_mlx_win;

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
		g_camera_choosed = 1;
		g_light_choosed = 0;
		printf("Camera selected\n");
		return (0);
	}
	else if (keycode == '2')
	{
		g_camera_choosed = 0;
		if (g_light_choosed)
			g_light_index = (g_light_index + 1) % g_light_count;
		g_light_choosed = 1;
		printf("Light %d selected\n", g_light_index + 1);
		return (0);
	}
	else if (keycode == 'q')
		translate((t_vec3){0.5f, 0.0f, 0.0f});
	else if (keycode == 'a')
		translate((t_vec3){-0.5f, 0.0f, 0.0f});
	else if (keycode == 'w')
		translate((t_vec3){0.0f, 0.5f, 0.0f});
	else if (keycode == 's')
		translate((t_vec3){0.0f, -0.5f, 0.0f});
	else if (keycode == 'e')
		translate((t_vec3){0.0f, 0.0f, 0.5f});
	else if (keycode == 'd')
		translate((t_vec3){0.0f, 0.0f, -0.5f});
	else if (keycode == 'p')
		rotate((t_vec3){45, 0, 0});
	else if (keycode == 'l')
		rotate((t_vec3){-45, 0, 0});
	else if (keycode == '[')
		rotate((t_vec3){0, 45, 0});
	else if (keycode == ';')
		rotate((t_vec3){0, -45, 0});
	else if (keycode == ']')
		rotate((t_vec3){0, 0, 45});
	else if (keycode == '\'')
		rotate((t_vec3){0, 0, -45});
	render();
	mlx_put_image_to_window(mlx, g_mlx_win, g_img.img, 0, 0);
	return (0);
}

int	mouse_hook(int button, int x, int y, void *mlx)
{
	(void)mlx;
	if (button == 1) // Left mouse button
	{
		t_vec3 pixel_pos = vec3_add(g_viewport.pixel_origin, vec3_add(vec3_mul(g_viewport.view_u_per_pixel, (float)x), vec3_mul(g_viewport.view_v_per_pixel, (float)y)));
		t_vec3 ray_dir = vec3_normalize(vec3_sub(pixel_pos, g_cam.pos));
		t_ray ray = {.origin = g_cam.pos, .dir = ray_dir};
		t_hit hit;
		if (hit_objects(&ray, 0.0f, INFINITY, &hit))
		{
			g_camera_choosed = 0;
			g_light_choosed = 0;
			g_choosen_object = hit.object;
			printf("Object %ld(%s) selected\n",
				g_choosen_object - g_objects + 1,
				g_choosen_object->type == SPHERE ? "Sphere" :
				g_choosen_object->type == PLANE ? "Plane" :
				g_choosen_object->type == CYLINDER ? "Cylinder" : "Unknown");
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
	for (int y = 0; y < g_viewport.height; ++y)
	{
		for (int x = 0; x < g_viewport.width; ++x)
		{
			t_vec3 pixel_pos = vec3_add(g_viewport.pixel_origin, vec3_add(vec3_mul(g_viewport.view_u_per_pixel, (float)x), vec3_mul(g_viewport.view_v_per_pixel, (float)y)));
			t_vec3 ray_direction = vec3_normalize(vec3_sub(pixel_pos, g_cam.pos));
			t_ray ray = {.origin = g_cam.pos, .dir = ray_direction};
			t_hit hit;
			hit.color = (t_vec3){0.0f, 0.0f, 0.0f};
			hit_objects(&ray, 0.0f, INFINITY, &hit);
			my_mlx_pixel_put(&g_img, x, y, (int)hit.color.x << 16 | (int)hit.color.y << 8 | (int)hit.color.z);
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
		free(g_lights);
		free(g_objects);
		return (1);
	}
	close(fd);
	init_viewport();
	g_mlx = mlx_init();
	g_mlx_win = mlx_new_window(g_mlx, g_viewport.width, g_viewport.height, "miniRT");
	mlx_key_hook(g_mlx_win, key_hook, g_mlx);
	mlx_mouse_hook(g_mlx_win, mouse_hook, g_mlx);
	mlx_hook(g_mlx_win, 33, 0, mlx_loop_end, g_mlx);
	g_img.img = mlx_new_image(g_mlx, g_viewport.width, g_viewport.height);
	g_img.addr = mlx_get_data_addr(g_img.img, &g_img.bits_per_pixel, &g_img.line_length, &g_img.endian);
	render();
	mlx_put_image_to_window(g_mlx, g_mlx_win, g_img.img, 0, 0);
	mlx_loop(g_mlx);
	mlx_destroy_image(g_mlx, g_img.img);
	mlx_destroy_window(g_mlx, g_mlx_win);
	mlx_destroy_display(g_mlx);
	free(g_mlx);
	free(g_lights);
	free(g_objects);
	return (0);
}
