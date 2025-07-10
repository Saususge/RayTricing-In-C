/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:23:09 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/10 20:22:29 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "object.h"

#define BUMP_TEXTURE_FILE "bump.jpg"

void	load_bump_map(void)
{
	t_tex	*tex;

	tex = &g()->tex;
	tex->tex = stbi_load(BUMP_TEXTURE_FILE,
			&tex->width, &tex->height, &tex->orig_channel, 1);
	if (!tex->tex)
	{
		ft_putstr_fd("Failed to load bump texture\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

float	sample_height(float u, float v)
{
	t_tex	*tex;
	int		x;
	int		y;

	tex = &g()->tex;
	x = (int)(u * (tex->width - 1));
	y = (int)(v * (tex->height - 1));
	return (tex->tex[y * tex->width + x] / 255.0f);
}

t_vec4	get_bumpmap_normal(float u, float v)
{
	float	du;
	float	dv;
	float	h_u;
	float	h_v;
	t_vec4	normal;

	du = 1.0f / g()->tex.width;
	dv = 1.0f / g()->tex.height;
	h_u = (sample_height(u + du, v) - sample_height(u - du, v)) / (2.0f * du);
	h_v = (sample_height(u, v + dv) - sample_height(u, v - dv)) / (2.0f * dv);
	normal = (t_vec4){{-h_u, -h_v, 1.0f, 0.0f}};
	normal = vec4_mul(normal, 1.0f / sqrtf(vec4_dot(normal, normal)));
	return (normal);
}
