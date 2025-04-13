/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:01:13 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/12 20:55:03 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSTEM_H
# define SYSTEM_H

# include "core/game.h"

void		system_input_state_switch(t_game *game);
t_posdir	system_input_posdir(const t_game *game);
t_posdir	system_update_posdir(\
	const t_player *player, const t_posdir *input, double delta_time);
void		system_colision_resolve(t_game *game, t_posdir *posdir);
void		system_player_update(t_player *player, t_posdir *posdir);

#endif
