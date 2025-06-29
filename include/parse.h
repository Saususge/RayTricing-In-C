/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:41:49 by wchoe             #+#    #+#             */
/*   Updated: 2025/06/30 02:33:39 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "object.h"

int	parse_ambient(void);
int	parse_camera(void);
int	parse_light(void);
int	parse_sphere(void);
int	parse_plane(void);
int	parse_cylinder(void);
// int	parse_color(const char *color_str, t_color *out);
int	parse_float(const char *float_str, float *out);
int	parse_vec3(char *vec_str, t_vec3 *out);
int	parse(int fd);
#endif