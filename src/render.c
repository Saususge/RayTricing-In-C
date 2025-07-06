/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:42:59 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/06 14:25:47 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "hit.h"
#include "mlx.h"

typedef struct render_data
{
	void	*mlx;
	void	*mlx_win;
	t_data	*img;
}	t_render_data;

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	render_and_put(void)
{
	t_render_data	data;
	t_vec3			color;
	t_object		*dump;
	int				x;
	int				y;

	data.mlx = g()->mlx;
	data.mlx_win = g()->mlx_win;
	data.img = &g()->img;
	y = 0;
	while (y < g()->viewport.height)
	{
		x = 0;
		while (x < g()->viewport.width)
		{
			color = (t_vec3){0.0f, 0.0f, 0.0f};
			shoot_ray_from_viewport(x, y, &dump, &color);
			my_mlx_pixel_put(&g()->img, x, y,
				(int)color.x << 16
				| (int)color.y << 8
				| (int)color.z);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img->img, 0, 0);
}
