/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:56:19 by chakim            #+#    #+#             */
/*   Updated: 2025/07/06 14:35:14 by wchoe            ###   ########.fr       */
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
#include "hit.h"
#include "parse.h"
#include "event.h"

void	render_and_put(void);

static void	init_mlx_var(void)
{
	void		**mlx;
	void		**mlx_win;
	t_viewport	*viewport;
	t_data		*img;

	mlx = &g()->mlx;
	mlx_win = &g()->mlx_win;
	viewport = &g()->viewport;
	img = &g()->img;
	*mlx = mlx_init();
	*mlx_win = mlx_new_window(*mlx, viewport->width, viewport->height, \
		"miniRT");
	// mlx_key_hook(*mlx_win, key_hook, *mlx);
	// mlx_mouse_hook(*mlx_win, mouse_hook, *mlx);
	mlx_hook(*mlx_win, 33, 0, mlx_loop_end, *mlx);
	img->img = mlx_new_image(*mlx, viewport->width, viewport->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
		&img->line_length, &img->endian);
}

void	move_cam_light_to_local(int light_idx, int obj_idx);

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./miniRT <scene_file>\n", STDERR_FILENO);
		return (1);
	}
	parse_scene_file(argv[1]);
	set_viewport();
	for (int i = 0; i < g()->object_count; ++i)
		for (int j = 0; j < g()->light_count; ++j)
			move_cam_light_to_local(j, i);
	init_mlx_var();
	render_and_put();
	mlx_loop(g()->mlx);
	mlx_destroy_image(g()->mlx, g()->img.img);
	mlx_destroy_window(g()->mlx, g()->mlx_win);
	mlx_destroy_display(g()->mlx);
	free(g()->mlx);
	free(g()->lights);
	free(g()->objects);
	return (0);
}
