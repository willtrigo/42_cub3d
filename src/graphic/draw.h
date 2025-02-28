/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:40:12 by maurodri          #+#    #+#             */
/*   Updated: 2025/02/28 03:46:39 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "utils/vec2.h"
# include "core/game.h"

typedef struct s_mini_args
{
	t_vec2f	grid_pos;
	int		block_size;
	t_vec2f offset;
}	t_mini_args;


void	draw_mini_floor(t_game *game, t_mini_args m);
void	draw_mini_wall(t_game *game, t_mini_args m);
void	draw_mini_player(t_game *game, t_mini_args m);
void	draw_mini_map(t_game *game, int block_size, t_vec2f offset);
void	draw_background(t_game *game);
void	draw_level_col(t_game *game, int x);
void	draw_level(t_game *game);

void	draw_circle(\
	mlx_image_t *canvas, t_vec2f center, float radius, t_color color);
void	draw_square_cs(\
	mlx_image_t *canvas, t_vec2f center, int size, t_color color);
void	draw_line_cs(\
	mlx_image_t *canvas, t_vec2f center, t_vec2f size_angle, t_color color);

#endif
