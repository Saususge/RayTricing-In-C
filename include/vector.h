/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:25:20 by chakim            #+#    #+#             */
/*   Updated: 2025/05/08 16:51:43 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# define EPSILON 0.000001f

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}	t_point;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

// creating vector
t_vec3	vec3_create(float x, float y, float z);
t_point	point_create(float x, float y, float z);

// elementary arithmetic
t_vec3	vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_mul(t_vec3 v, float s);
t_vec3	vec3_div(t_vec3 v, float s);
t_vec3	vec3_neg(t_vec3 v);

// dot product, cross product
float	vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2);

// length and normaize
float	vec3_length(t_vec3 v);
float	vec3_length_squared(t_vec3 v);
t_vec3	vec3_normalize(t_vec3 v);

// reflect and refract of vector
t_vec3	vec3_reflect(t_vec3 v, t_vec3 normal);
t_vec3	vec3_refract(t_vec3 v, t_vec3 normal, float refraction_ratio);

// utility
float	vec3_angle(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_lerp(t_vec3 v1, t_vec3 v2, float t);
int		is_vec3_near_to_zero(t_vec3 v);
t_vec3	vec3_min(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_max(t_vec3 v1, t_vec3 v2);

// conversion
t_vec3	point_to_vec3(t_point p);
t_point	vec3_to_point(t_vec3 v);

// calc between points
float	point_distance(t_point p1, t_point p2);
float	point_distance_squared(t_point p1, t_point p2);
t_point	point_add_vec(t_point p, t_vec3 v);
#endif