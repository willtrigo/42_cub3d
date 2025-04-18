/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:40:12 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/18 00:33:58 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "core/game.h"

void	draw_background(t_game *game);
void	draw_level(t_game *game);
void	draw_entities(t_game *game);

#endif
