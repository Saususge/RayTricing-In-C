/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:56:19 by chakim            #+#    #+#             */
/*   Updated: 2025/04/18 12:25:50 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "test.h"

int	main(int argc, char **argv)
{
	t_data	img;
	t_scene	scene;
	void	*mlx;
	void	*mlx_win;

	init_scene(&scene);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1280, 720, "mini_rt");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
		&img.line_length, &img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
