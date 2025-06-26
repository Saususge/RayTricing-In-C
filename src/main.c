/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:56:19 by chakim            #+#    #+#             */
/*   Updated: 2025/04/23 17:11:47 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "test.h"
#include "draw_pixels.h"
	
int	main(void)
{
	t_data	img;
	t_scene	scene;
	void	*mlx;
	void	*mlx_win;

	init_test(&scene);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1280, 720, "mini_rt");
	draw_pixels(mlx, mlx_win, &img);
	mlx_loop(mlx);
}
