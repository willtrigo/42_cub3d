/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:02:51 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/19 21:07:26 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_H
# define LOCATION_H

# include "core/game.h"

t_location	location_move(\
	const t_location *old_location, float velocity, float delta_time);
t_location	location_in_player_perspective(\
	const t_location *grid_location, const t_player *player);
bool		location_is_in_field_of_view(\
	const t_location *player_relative_location, const t_player *player);

#endif
