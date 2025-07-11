/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:34:26 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/06 14:24:29 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "libft.h"
#include "parse.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int	process_light_arr(void)
{
	t_light	*new_lights;

	if (!g()->lights)
	{
		g()->lights = malloc(sizeof(t_light) * g()->light_capacity);
		if (!g()->lights)
			return (1);
	}
	if (g()->light_count >= g()->light_capacity)
	{
		new_lights = ft_realloc(g()->lights, \
		sizeof(t_light) * g()->light_capacity, \
		sizeof(t_light) * g()->light_capacity << 1);
		if (!new_lights)
		{
			free(g()->lights);
			g()->lights = NULL;
			return (1);
		}
		g()->lights = new_lights;
		g()->light_capacity <<= 1;
	}
	return (0);
}

static int	parse_light_fields(t_light *light, float *intensity, t_vec3 *color)
{
	char	*pos_str;
	char	*intensity_str;
	char	*rgb_str;

	pos_str = ft_strtok(NULL, " \t\n");
	intensity_str = ft_strtok(NULL, " \t\n");
	rgb_str = ft_strtok(NULL, " \t\n");
	if (parse_vec4(pos_str, &light->position, 1.0f))
		return (1);
	if (parse_float(intensity_str, intensity) || *intensity < 0.0f \
	|| *intensity > 1.0f)
		return (1);
	if (rgb_str)
	{
		if (parse_vec3(rgb_str, color))
			return (1);
	}
	else
		*color = (t_vec3){255, 255, 255};
	return (0);
}

int	parse_light(void)
{
	t_light	light;
	float	intensity;
	t_vec3	color;

	if (process_light_arr())
		return (1);
	if (parse_light_fields(&light, &intensity, &color))
		return (1);
	light.intensity.x = (color.x / 255.0f) * intensity;
	light.intensity.y = (color.y / 255.0f) * intensity;
	light.intensity.z = (color.z / 255.0f) * intensity;
	g()->lights[g()->light_count++] = light;
	return (0);
}
