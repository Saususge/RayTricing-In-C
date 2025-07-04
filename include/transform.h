/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:45:18 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/04 17:45:18 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORM_H
# define TRANSFORM_H
# include "vector.h"

void	translate(t_vec3 offset);
void	scale(float scale_factor);
void	rotate(t_vec3 axis, float angle);
#endif
