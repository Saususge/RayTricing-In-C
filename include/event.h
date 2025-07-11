/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 06:39:10 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/04 17:48:15 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H
# define RIGHT_ARROW 65363
# define LEFT_ARROW 65361
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define ESC 65307

int	key_hook(int keycode, void *mlx);
int	mouse_hook(int button, int x, int y, void *mlx);
#endif