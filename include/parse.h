/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:41:49 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/06 14:24:20 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "object.h"

int		parse_ambient(void);
int		parse_camera(void);
int		parse_light(void);
int		parse_sphere(void);
int		parse_plane(void);
int		parse_cylinder(void);
int		parse_cone(void);
int		parse_float(const char *float_str, float *out);
int		parse_vec3(char *vec_str, t_vec3 *out);
int		parse_vec4(char *vec_str, t_vec4 *out, float w);
int		parse(int fd);
void	parse_scene_file(const char *filename);
#endif