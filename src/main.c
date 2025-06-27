/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:56:19 by chakim            #+#    #+#             */
/*   Updated: 2025/06/27 15:52:10 by wchoe            ###   ########.fr       */
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
	printf("Ambient Light: intensity=%.2f, color=(%d, %d, %d)\n",
		g_ambient_light.intensity,
		g_ambient_light.color.r,
		g_ambient_light.color.g,
		g_ambient_light.color.b);
	printf("Camera: position=(%.2f, %.2f, %.2f), orientation=(%.2f, %.2f, %.2f), fov=%.2f\n",
		g_camera.position.x, g_camera.position.y, g_camera.position.z,
		g_camera.orientation.x, g_camera.orientation.y, g_camera.orientation.z,
		g_camera.fov);
	for (int i = 0; i < g_light_count; ++i)
	{
		printf("Light %d: position=(%.2f, %.2f, %.2f), intensity=%.2f, color=(%d, %d, %d)\n",
			i + 1,
			g_lights[i].position.x, g_lights[i].position.y, g_lights[i].position.z,
			g_lights[i].intensity,
			g_lights[i].color.r, g_lights[i].color.g, g_lights[i].color.b);
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
	free(g_lights);
	free(g_objects);
	return (0);
}