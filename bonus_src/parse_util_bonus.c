/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:35:19 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/06 14:24:06 by wchoe            ###   ########.fr       */
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

int	parse_vec3(char *vec_str, t_vec3 *out)
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

int	parse_vec4(char *vec_str, t_vec4 *out, float w)
{
	char	*str[3];
	t_vec4	v;

	if (!vec_str)
		return (1);
	str[0] = ft_strtok(vec_str, ",");
	str[1] = ft_strtok(NULL, ",");
	str[2] = ft_strtok(NULL, ",");
	if (parse_float(str[0], &v.v[0])
		|| parse_float(str[1], &v.v[1])
		|| parse_float(str[2], &v.v[2]))
		return (1);
	v.v[3] = w;
	*out = v;
	return (0);
}
