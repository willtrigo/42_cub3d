/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:00:03 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/25 17:00:10 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"
#include "core/game.h"
#include "graphic/render.h"
#include "utils/vec2.h"
#include <math.h>
#include <stdbool.h>

t_location	system_player_location_update(
	const t_player *player, const t_location *input, double delta_time)
{
	t_location	update;

	update.angle = (input->angle * delta_time) + player->loc.angle;
	(void) "input has axis based on screen (up, down,...)"
		"and player has axis based on his angle in map(forward, back, ...)"
		"so we need to change input base changing its axis so that"
		"input up goes forward in player angle";
	update.pos.x = ((cosf(update.angle) * input->pos.y \
						+ cosf(update.angle + M_PI_2) * input->pos.x) \
					* delta_time) + player->loc.pos.x;
	update.pos.y = ((sinf(update.angle) * input->pos.y \
						+ sinf(update.angle + M_PI_2) * input->pos.x) \
					* delta_time) + player->loc.pos.y;
	if (update.angle > 2 * M_PI)
		update.angle -= 2 * M_PI;
	else if (update.angle < 0)
		update.angle += 2 * M_PI;
	return (update);
}

void	system_player_location_set(t_player *player, t_location *new_location)
{
	player->loc = *new_location;
}
