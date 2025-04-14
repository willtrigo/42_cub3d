/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:01:13 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/13 20:40:53 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSTEM_H
# define SYSTEM_H

# include "core/game.h"

void		system_input_state_switch(t_game *game);
t_location	system_input_location(const t_game *game);
t_location	system_update_location(\
	const t_player *player, const t_location *input, double delta_time);
void		system_colision_resolve(t_game *game, t_location *location);
void		system_player_update(t_player *player, t_location *location);

#endif
