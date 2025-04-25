/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_colision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:48:02 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/25 17:01:58 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"
#include "system_colision_walls_internal.h"

void	system_colision_border(t_manager *manager, t_location *intention)
{
	const float	player_half_size = manager->player.size / 2.0;

	if (intention->pos.x < player_half_size)
		intention->pos.x = player_half_size;
	else if (intention->pos.x > manager->chart.dimen.x - player_half_size)
		intention->pos.x = manager->chart.dimen.x - player_half_size;
	if (intention->pos.y < player_half_size)
		intention->pos.y = player_half_size;
	else if (intention->pos.y > manager->chart.dimen.y - player_half_size)
		intention->pos.y = manager->chart.dimen.y - player_half_size;
}

static bool	has_cross(float new, float old, float player_half_size)
{
	float	min;
	float	max;

	if (new < old)
	{
		min = new - player_half_size;
		max = old + player_half_size;
	}
	else
	{
		min = old - player_half_size;
		max = new + player_half_size;
	}
	return (((int) min) != ((int) max));
}

void	system_colision_walls(t_manager *manager, t_location *intention)
{
	const float		p_half_size = manager->player.size / 2.0;
	const t_vec2i	has_crossv = (t_vec2i){
		has_cross(intention->pos.x, manager->player.loc.pos.x, p_half_size),
		has_cross(intention->pos.y, manager->player.loc.pos.y, p_half_size)};

	if (!has_crossv.x && !has_crossv.y)
		return ;
	else if (has_crossv.x && !has_crossv.y)
		return (system_colision_walls_h(manager, intention, p_half_size));
	else if (!has_crossv.x && has_crossv.y)
		return (system_colision_walls_v(manager, intention, p_half_size));
	else
		return (system_colision_walls_diag(manager, intention, p_half_size));
}

void	system_colision_resolve(\
	t_game *game, t_manager *manager, t_location *intention)
{
	system_colision_border(manager, intention);
	if (game->state.colision)
		system_colision_walls(manager, intention);
}
