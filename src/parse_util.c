/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:35:19 by wchoe             #+#    #+#             */
/*   Updated: 2025/06/30 02:33:50 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "libft.h"
#include "parse.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int	parse_float(const char *float_str, float *out)
{
	char	*end;
	float	val;

	if (!float_str)
		return (1);
	val = ft_strtof(float_str, &end);
	if (end == float_str || *end != '\0')
		return (1);
	*out = val;
	return (0);
}

int parse_vec3(char *vec_str, t_vec3 *out)
{
	char	*str[3];
	t_vec3	v;

	if (!vec_str)
		return (1);
	str[0] = ft_strtok(vec_str, ",");
	str[1] = ft_strtok(NULL, ",");
	str[2] = ft_strtok(NULL, ",");
	if (parse_float(str[0], &v.x)
		|| parse_float(str[1], &v.y)
		|| parse_float(str[2], &v.z))
		return (1);
	*out = v;
	return (0);
}

// static int	is_valid_int_token(const char *str)
// {
// 	if (!str || !*str)
// 		return (0);
// 	if (*str == '-' || *str == '+')
// 		++str;
// 	if (!*str)
// 		return (0);
// 	while (*str) {
// 		if (*str < '0' || *str > '9')
// 			return (0);
// 		++str;
// 	}
// 	return (1);
// }

// int	parse_color(const char *rgb_str, t_color *color)
// {
// 	char	*r_str;
// 	char	*g_str;
// 	char	*b_str;
// 	t_color	__color;

// 	if (!rgb_str)
// 		return (1);
// 	r_str = ft_strtok((char *)rgb_str, ",");
// 	g_str = ft_strtok(NULL, ",");
// 	b_str = ft_strtok(NULL, ",");
// 	if (!r_str || !g_str || !b_str)
// 		return (1);
// 	if (!is_valid_int_token(r_str)
// 		|| !is_valid_int_token(g_str)
// 		|| !is_valid_int_token(b_str))
// 		return (1);
// 	__color.r = ft_atoi(r_str);
// 	__color.g = ft_atoi(g_str);
// 	__color.b = ft_atoi(b_str);
// 	if (__color.r < 0 || __color.r > 255
// 		|| __color.g < 0 || __color.g > 255
// 		|| __color.b < 0 || __color.b > 255)
// 		return (1);
// 	*color = __color;
// 	return (0);
// }
