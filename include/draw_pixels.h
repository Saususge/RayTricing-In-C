/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:46:16 by chakim            #+#    #+#             */
/*   Updated: 2025/06/30 00:54:54 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_PIXELS_H
# define DRAW_PIXELS_H

void	draw_pixels(void *mlx, void *mlx_win, t_data *img);
void	pixel_put(t_data *data, int x, int y, int color);

#endif