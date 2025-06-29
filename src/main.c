/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:56:19 by chakim            #+#    #+#             */
/*   Updated: 2025/06/30 01:05:33 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "test.h"
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
	
// int	main(void)
// {
// 	t_data	img;
// 	t_scene	scene;
// 	void	*mlx;
// 	void	*mlx_win;

// 	init_test(&scene);
// 	mlx = mlx_init();
// 	mlx_win = mlx_new_window(mlx, 1280, 720, "mini_rt");
// 	draw_pixels(mlx, mlx_win, &img);
// 	mlx_loop(mlx);
// }

void	print_parsed_elems(void)
{
	printf("Ambient Light: intensity=(%.2f, %.2f, %.2f)\n",
		g_ambient_light.intensity.x,
		g_ambient_light.intensity.y,
		g_ambient_light.intensity.z);
	printf("Camera: position=(%.2f, %.2f, %.2f), orientation=(%.2f, %.2f, %.2f), fov=%.2f\n",
		g_camera.position.x, g_camera.position.y, g_camera.position.z,
		g_camera.orientation.x, g_camera.orientation.y, g_camera.orientation.z,
		g_camera.fov);
	for (int i = 0; i < g_light_count; ++i)
	{
		printf("Light %d: position=(%.2f, %.2f, %.2f), intensity=(%.2f, %.2f, %.2f)\n",
			i + 1,
			g_lights[i].position.x, g_lights[i].position.y, g_lights[i].position.z,
			g_lights[i].intensity.x, g_lights[i].intensity.y, g_lights[i].intensity.z);
	}
	for (int i = 0; i < g_object_count; ++i)
	{
		t_object obj = g_objects[i];
		if (obj.type == SPHERE)
		{
			t_sphere sph = obj.data.sphere;
			printf("Sphere %d: center=(%.2f, %.2f, %.2f), radius=%.2f, color=(%d, %d, %d)\n",
				i + 1,
				sph.center.x, sph.center.y, sph.center.z,
				sph.radius,
				sph.color.r, sph.color.g, sph.color.b);
		}
		else if (obj.type == PLANE)
		{
			t_plane pl = obj.data.plane;
			printf("Plane %d: point=(%.2f, %.2f, %.2f), normal=(%.2f, %.2f, %.2f), color=(%d, %d, %d)\n",
				i + 1,
				pl.point.x, pl.point.y, pl.point.z,
				pl.normal.x, pl.normal.y, pl.normal.z,
				pl.color.r, pl.color.g, pl.color.b);
		}
	}
}

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
		if (g_objects[i].ops->intersect(g_objects + i, ray, &current_hit, (t_t_bound){t_min, closest_so_far}))
		{
			hit_anything = 1;
			closest_so_far = current_hit.t;
			*hit = current_hit;
		}
	}
	return (hit_anything);
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
		return (1);
	}
	close(fd);

	print_parsed_elems();

	clock_t start_time = clock();

	float	aspect_ratio = 1280.0f / 720.0f;
	int		width = 1280;
	int		height = (int)(width / aspect_ratio);
	// float	focal_length = (float)(width / (2.0f * tan(g_camera.fov * M_PI / 360.0f)));
	// float	view_height = 2.0f * focal_length * tan(g_camera.fov * M_PI / 360.0f);
	float	focal_length = 1.0;
	float	view_height = 2.0;
	float	view_width = view_height * aspect_ratio;
	t_vec3	view_u = vec3_create(view_width, 0.0f, 0.0f);
	t_vec3	view_v = vec3_create(0.0f, -view_height, 0.0f);
	t_vec3	view_u_per_pixel = vec3_mul(view_u, 1.0f / (float)width);
	t_vec3	view_v_per_pixel = vec3_mul(view_v, 1.0f / (float)height);
	t_vec3	view_upper_left = vec3_sub(g_camera.position, vec3_add(vec3_create(0.0f, 0.0f, focal_length), vec3_add(vec3_mul(view_u, 0.5f), vec3_mul(view_v, 0.5f))));
	t_vec3	pixel_origin = vec3_add(view_upper_left, vec3_mul(vec3_add(view_v_per_pixel, view_u_per_pixel), 0.5f));
	t_data	img;
	void	*mlx = mlx_init();
	void	*mlx_win = mlx_new_window(mlx, width, height, "miniRT");
	img.img = mlx_new_image(mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			t_vec3	pixel_pos = vec3_add(pixel_origin, vec3_add(vec3_mul(view_u_per_pixel, (float)x), vec3_mul(view_v_per_pixel, (float)y)));
			t_vec3	ray_direction = vec3_normalize(vec3_sub(pixel_pos, g_camera.position));
			t_ray	ray = {point_to_vec3(g_camera.position), ray_direction};
			t_hit	hit;
			hit.color = (t_color){0, 0, 0};
			hit_objects(&ray, 0.0f, INFINITY, &hit);
			my_mlx_pixel_put(&img, x, y, hit.color.r << 16 | hit.color.g << 8 | hit.color.b);
		}
	}

	clock_t end_time = clock();
	double elapsed_sec = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	printf("Rendering time: %.3f seconds\n", elapsed_sec);

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);

	free(g_lights);
	free(g_objects);
	return (0);
}