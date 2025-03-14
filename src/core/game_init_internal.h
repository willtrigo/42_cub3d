/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:53:38 by maurodri          #+#    #+#             */
/*   Updated: 2025/02/28 14:10:26 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_INIT_INTERNAL_H
# define GAME_INIT_INTERNAL_H

# include "game.h"

void	window_init(t_game *game);
bool	canvas_init(t_game *game);
void	canvas_clean(mlx_t *mlx, mlx_image_t *canvas);
bool	map_init(t_game *game, t_config_file *config);
bool	game_init_fail(t_game *game, t_config_file *config, char *msg_error);

#endif
