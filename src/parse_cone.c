/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:06:20 by chakim            #+#    #+#             */
/*   Updated: 2025/06/30 15:10:15 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "cone.h"
#include "object.h"
#include "libft.h"
#include <stdlib.h>

struct s_cone_parse_data {
	t_point center;
	t_vec3 orient;
	float diameter;
	float height;
	t_vec3 color;
	char *center_str;
	char *orient_str;
	char *diam_str;
	char *height_str;
	char *color_str;
};

int	parse_cone(void)
{
	struct s_cone_parse_data data;

	data.center_str = ft_strtok(NULL, " \t\n");
	data.orient_str = ft_strtok(NULL, " \t\n");
	data.diam_str = ft_strtok(NULL, " \t\n");
	data.height_str = ft_strtok(NULL, " \t\n");
	data.color_str = ft_strtok(NULL, " \t\n");
	if (parse_vec3(data.center_str, &data.center)
		|| parse_vec3(data.orient_str, &data.orient)
		|| parse_float(data.diam_str, &data.diameter)
		|| data.diameter <= 0.0f
		|| parse_float(data.height_str, &data.height)
		|| data.height <= 0.0f
		|| parse_vec3(data.color_str, &data.color)
		|| process_object_arr_size())
		return (1);
	g()->objects[g()->object_count++] = create_cone((struct s_cone_data){
		.center = data.center,
		.axis = vec3_normalize(data.orient),
		.radius = data.diameter * 0.5f,
		.height = data.height,
		.color = data.color,
	});
	return (0);
}
