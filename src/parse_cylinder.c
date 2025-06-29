/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 03:18:51 by chakim            #+#    #+#             */
/*   Updated: 2025/06/30 04:25:55 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "cylinder.h"
#include "object.h"
#include "libft.h"
#include <stdlib.h>

int parse_cylinder(void)
{
    t_point center;
    t_vec3  orient;
    float   diameter;
    float   radius;
    float   height;
    t_vec3  color;
    char    *center_str;
    char    *orient_str;
    char    *diam_str;
    char    *height_str;
    char    *color_str;

    center_str = ft_strtok(NULL, " \t\n");
    orient_str = ft_strtok(NULL, " \t\n");
    diam_str   = ft_strtok(NULL, " \t\n");
    height_str = ft_strtok(NULL, " \t\n");
    color_str  = ft_strtok(NULL, " \t\n");

    if ( parse_vec3(center_str, (t_vec3 *)&center)
      || parse_vec3(orient_str, &orient)
      || parse_float(diam_str, &diameter) || diameter <= 0.0f
      || parse_float(height_str, &height) || height <= 0.0f
      || parse_vec3(color_str, &color)
      || process_object_arr_size() )
        return (1);

    radius = diameter * 0.5f;
    t_vec3 axis = vec3_normalize(orient);

    g_objects[g_object_count++] = create_cylinder(center, axis, radius, height, color);
    return (0);
}