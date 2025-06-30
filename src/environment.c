/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:28:22 by wchoe             #+#    #+#             */
/*   Updated: 2025/06/30 09:55:21 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

t_ambient_light	g_amb_light;
t_camera		g_cam;
t_light			*g_lights;
int				g_light_count;
int				g_light_capacity = 4;
float			g_k_a = 0.2;
float			g_k_d = 10;
float			g_k_s = 10;