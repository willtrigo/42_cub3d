/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:02:44 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/19 21:06:38 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "location.h"

t_location	location_move(\
	const t_location *old_location, float velocity, float delta_time)
{
	const t_vec2f	movement_vec = vec2f_scale(\
		vec2f_unit_vector(old_location->angle), velocity * delta_time);

	return ((t_location){
		.pos = vec2f_add(movement_vec, old_location->pos),
		.angle = old_location->angle
	});
}

t_location	location_in_player_perspective(\
	const t_location *grid_location, const t_player *player)
{
	t_location	relative;

	relative.pos = vec2f_sub(grid_location->pos, player->loc.pos);
	relative.angle = atan2(relative.pos.y, relative.pos.x) \
						- player->loc.angle;
	if (relative.angle < -M_PI)
		relative.angle += 2 * M_PI;
	return (relative);
}

bool	location_is_in_field_of_view(\
	const t_location *player_relative_location, const t_player *player)
{
	return ((-0.5 * player->fov) <= player_relative_location->angle
		&& player_relative_location->angle < (0.5 * player->fov));
}
