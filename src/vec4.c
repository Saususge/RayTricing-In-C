/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 14:18:59 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/06 14:20:45 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec4	vec4_add(t_vec4 a, t_vec4 b)
{
	return (t_vec4){
		a.v[0] + b.v[0],
		a.v[1] + b.v[1],
		a.v[2] + b.v[2],
		a.v[3] + b.v[3]};
}

t_vec4	vec4_sub(t_vec4 a, t_vec4 b)
{
	return (t_vec4){
		a.v[0] - b.v[0],
		a.v[1] - b.v[1],
		a.v[2] - b.v[2],
		a.v[3] - b.v[3]};
}

t_vec4	vec4_mul(t_vec4 a, float b)
{
	return (t_vec4){
		a.v[0] * b,
		a.v[1] * b,
		a.v[2] * b,
		a.v[3] * b};
}

t_vec4	vec4_div(t_vec4 a, float b)
{
	if (b == 0.0f)
		return (t_vec4){0, 0, 0, 0}; // Handle division by zero
	return (t_vec4){
		a.v[0] / b,
		a.v[1] / b,
		a.v[2] / b,
		a.v[3] / b};
}

t_vec4	vec4_normalize(t_vec4 a)
{
	float	length;

	length = sqrtf(a.v[0] * a.v[0] + a.v[1] * a.v[1] + a.v[2] * a.v[2]);
	if (length < EPSILON)
		return (t_vec4){0, 0, 0, 0}; // Handle zero vector
	return (vec4_div(a, length));
}

float	vec4_dot(t_vec4 a, t_vec4 b)
{
	return (a.v[0] * b.v[0] + a.v[1] * b.v[1] + a.v[2] * b.v[2] + a.v[3] * b.v[3]);
}

t_vec4	vec4_neg(t_vec4 a)
{
	return (t_vec4){
		-a.v[0],
		-a.v[1],
		-a.v[2],
		-a.v[3]};
}
