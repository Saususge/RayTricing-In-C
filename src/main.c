/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:56:19 by chakim            #+#    #+#             */
/*   Updated: 2025/07/01 17:15:20 by chakim           ###   ########.fr       */
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
#include "event.h"
#include "rotate.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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

void	init_viewport(void)
{
	t_viewport	*viewport;

	viewport = &g()->viewport;
	viewport->aspect_ratio = 21.0f / 9.0f;
	viewport->width = 1680;
	viewport->height = (int)(viewport->width / viewport->aspect_ratio);
	viewport->focal_length = 1.0f;
	viewport->view_w = 2.0f * viewport->focal_length * tan(g()->cam.fov * M_PI / 360.0f);
	viewport->view_h = viewport->view_w / viewport->aspect_ratio;
	viewport->vup.y = 1.0f;
	viewport->view_u = vec3_mul(
		vec3_normalize(vec3_cross(g()->cam.dir, viewport->vup)),
		viewport->view_w);
	viewport->view_v = vec3_mul(
		vec3_normalize(vec3_cross(viewport->view_u, g()->cam.dir)),
		-viewport->view_h);
	viewport->view_u_per_pixel = vec3_mul(viewport->view_u,
		1.0f / (float)viewport->width);
	viewport->view_v_per_pixel = vec3_mul(viewport->view_v,
		1.0f / (float)viewport->height);
	viewport->view_upper_left = vec3_sub(g()->cam.pos,
		vec3_add(
			vec3_mul(g()->cam.dir, -viewport->focal_length),
			vec3_add(
				vec3_mul(viewport->view_u, 0.5f),
				vec3_mul(viewport->view_v, 0.5f))));
	viewport->pixel_origin = vec3_add(viewport->view_upper_left,
		vec3_mul(vec3_add(viewport->view_v_per_pixel, viewport->view_u_per_pixel), 0.5f));
}

void	translate(t_vec3 offset)
{
	t_gvar *gvar;
	t_camera *cam;
	t_light *light;
	t_object *obj;

	gvar = g();
	cam = NULL;
	light = NULL;
	obj = NULL;
	if (gvar->camera_choosed)
	{
		cam = &gvar->cam;
		cam->pos = vec3_add(cam->pos, offset);
		init_viewport();
	}
	else if (gvar->light_choosed)
	{
		light = &gvar->lights[gvar->light_index];
		light->position = vec3_add(light->position, offset);
	}
	else if (gvar->choosen_object)
	{
		obj = gvar->choosen_object;
		obj->ops->translate(obj, offset);
	}
}

void	rotate(t_vec3 angle)
{
	t_gvar *gvar;
	t_camera *cam;
	t_object *obj;

	gvar = g();
	cam = NULL;
	obj = NULL;
	if (gvar->camera_choosed)
	{
		cam = &gvar->cam;
		cam->dir = vec3_normalize(rotate_vector(cam->dir, angle));
		init_viewport();
	}
	else if (gvar->light_choosed)
		printf("Cannot rotate light\n");
	else if (gvar->choosen_object)
	{
		obj = gvar->choosen_object;
		obj->ops->rotate(obj, angle);
	}
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
	if (button == 1)
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
				g()->choosen_object->type == CYLINDER ? "Cylinder" : "Cone");
		}
	}
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
	void		**mlx;
	void		**mlx_win;
	t_viewport	*viewport;
	t_data		*img;
	int			fd;

	fd = open(argv[1], O_RDONLY);
	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./miniRT <scene_file>\n", STDERR_FILENO);
		return (1);
	}
	if (parse(fd))
	{
		ft_putstr_fd("Error: Failed to parse scene file.\n", 2);
		free(g()->lights);
		free(g()->objects);
		return (1);
	}
	close(fd);
	init_viewport();
	mlx = &g()->mlx;
	mlx_win = &g()->mlx_win;
	viewport = &g()->viewport;
	img = &g()->img;
	*mlx = mlx_init();
	*mlx_win = mlx_new_window(*mlx, viewport->width, viewport->height, \
		"miniRT");
	mlx_key_hook(*mlx_win, key_hook, *mlx);
	mlx_mouse_hook(*mlx_win, mouse_hook, *mlx);
	mlx_hook(*mlx_win, 33, 0, mlx_loop_end, *mlx);
	img->img = mlx_new_image(*mlx, viewport->width, viewport->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
		&img->line_length, &img->endian);
	render();
	mlx_put_image_to_window(*mlx, *mlx_win, img->img, 0, 0);
	mlx_loop(*mlx);
	mlx_destroy_image(*mlx, img->img);
	mlx_destroy_window(*mlx, *mlx_win);
	mlx_destroy_display(*mlx);
	free(*mlx);
	free(g()->lights);
	free(g()->objects);
	return (0);
}
