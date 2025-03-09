/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:40:12 by maurodri          #+#    #+#             */
/*   Updated: 2025/03/09 01:16:15 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "utils/vec2.h"
# include "core/game.h"

void	draw_background(t_game *game);
void	draw_level_col(t_game *game, int x);
void	draw_level(t_game *game);
void	draw_level2(t_game *game);
void	draw_level3(t_game *game);

void	draw_circle_cs(\
	mlx_image_t *canvas, t_vec2f center, float radius, t_color color);
void	draw_square_cs(\
	mlx_image_t *canvas, t_vec2f center, int size, t_color color);
void	draw_line_cs(\
	mlx_image_t *canvas, t_vec2f center, t_vec2f size_angle, t_color color);
void	draw_line_p( \
	mlx_image_t *canvas, t_vec2f pa, t_vec2f pb, t_color color);

#endif
