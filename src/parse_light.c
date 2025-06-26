/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:34:26 by wchoe             #+#    #+#             */
/*   Updated: 2025/06/26 23:43:58 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "libft.h"
#include "parse.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int process_light_arr(void)
{
	t_light	*new_lights;

	if (!g_lights)
	{
		g_lights = malloc(sizeof(t_light) * g_light_capacity);
		if (!g_lights)
			return (1);
	}
	if (g_light_count >= g_light_capacity)
	{
		new_lights = ft_realloc(g_lights,
						sizeof(t_light) * g_light_capacity,
						sizeof(t_light) * g_light_capacity << 1);
		if (!new_lights)
		{
			free(g_lights);
			g_lights = NULL;
			return (1);
		}
		g_lights = new_lights;
		g_light_capacity <<= 1;
	}
	return (0);
}

int parse_light(void)
{
	t_light	light;
	char	*pos_str;
	char	*ratio_str;
	char	*rgb_str;

	if (process_light_arr())
		return (1);
	pos_str = ft_strtok(NULL, " \t\n");
	ratio_str = ft_strtok(NULL, " \t\n");
	rgb_str = ft_strtok(NULL, " \t\n");
	if (parse_vec3(pos_str, &light.position))
		return (1);
	if (parse_float(ratio_str, &light.intensity)
		|| light.intensity < 0.0f || light.intensity > 1.0f)
		return (1);
	if (rgb_str)
	{
		if (parse_color(rgb_str, &light.color))
			return (1);
	}
	else
		light.color = (t_color){255, 255, 255};
	g_lights[g_light_count++] = light;
	return (0);
}
