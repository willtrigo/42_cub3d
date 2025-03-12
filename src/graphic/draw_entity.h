/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entity.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:39:16 by maurodri          #+#    #+#             */
/*   Updated: 2025/03/11 21:40:32 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_ENTITY_H
# define DRAW_ENTITY_H

# include "core/game.h"
# include "graphic/grid.h"

void	draw_entity_col(
	t_game *game, t_grid_entity *entity, int pixel_x, float wall_height_screen);

#endif
