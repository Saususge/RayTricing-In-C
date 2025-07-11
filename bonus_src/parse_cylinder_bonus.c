/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 03:18:51 by chakim            #+#    #+#             */
/*   Updated: 2025/07/10 20:20:22 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "cylinder.h"
#include "object.h"
#include "libft.h"
#include <stdlib.h>

int	parse_cylinder(void)
{
	struct s_cyl_parse_data	data;
	struct s_cyl_data		cyl_data;

	data.center_str = ft_strtok(NULL, " \t\n");
	data.orient_str = ft_strtok(NULL, " \t\n");
	data.diam_str = ft_strtok(NULL, " \t\n");
	data.height_str = ft_strtok(NULL, " \t\n");
	data.color_str = ft_strtok(NULL, " \t\n");
	if (parse_vec3(data.center_str, &data.center)
		|| parse_vec3(data.orient_str, &data.orient)
		|| fabsf(vec3_length(data.orient) - 1.0f) > EPSILON
		|| parse_float(data.diam_str, &data.diameter)
		|| data.diameter <= 0.0f
		|| parse_float(data.height_str, &data.height)
		|| data.height <= 0.0f
		|| parse_vec3(data.color_str, &data.color)
		|| process_object_arr_size())
		return (1);
	cyl_data.center = data.center;
	cyl_data.axis = vec3_normalize(data.orient);
	cyl_data.radius = data.diameter * 0.5f;
	cyl_data.height = data.height;
	cyl_data.color = data.color;
	g()->objects[g()->object_count++] = create_cylinder(cyl_data);
	return (0);
}
