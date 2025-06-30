/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:34:26 by wchoe             #+#    #+#             */
/*   Updated: 2025/06/30 16:57:02 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "libft.h"
#include "parse.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int	parse_ambient(void)
{
	t_vec3			temp_color;
	float			temp_float;
	char			*intensity_str;
	char			*rgb_str;

	intensity_str = ft_strtok(NULL, " \t\n");
	rgb_str = ft_strtok(NULL, " \t\n");
	if (parse_float(intensity_str, &temp_float)
		|| temp_float < 0.0f || temp_float > 1.0f)
		return (1);
	if (parse_vec3(rgb_str, &temp_color))
		return (1);
	g()->amb_light = (t_ambient_light){
		.intensity = (t_vec3){
		.x = temp_color.x / 255.0f * temp_float,
		.y = temp_color.y / 255.0f * temp_float,
		.z = temp_color.z / 255.0f * temp_float
	}};
	return (0);
}
