/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_entities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:51:21 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/19 21:04:52 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"
#include "graphic/render.h"
#include "location.h"

void	manager_bullet_move(t_manager *manager, t_bullet *bullet, t_game *game)
{
	char		scene_entity;
	t_location	new_location;

	if (bullet->is_alive == false)
		return ;
	new_location = location_move(&bullet->loc, \
		bullet->velocity, game->mlx->delta_time);
	scene_entity = chart_entity(&manager->chart, new_location.pos);
	if (scene_entity == '1')
	{
		bullet->is_alive = 0;
	}
	else
		bullet->loc = new_location;
}

void	manager_entities_move(t_manager *manager, t_game *game)
{
	int	i;

	i = -1;
	while (++i < BULLETS_SIZE)
		manager_bullet_move(manager, manager->bullets + i, game);
}

void	entity_manager_bullet_init(
	t_bullet *new_bullet, const t_location *initial)
{
	new_bullet->is_alive = 1;
	new_bullet->loc = *initial;
	new_bullet->velocity = 2.0f;
	new_bullet->size = 8.0f;
}

bool	entity_manager_spawn_bullet(
	t_manager *manager, const t_location *initial, double time)
{
	int	i;

	if ((time - manager->last_bullet_time) < BULLET_MIN_SPAWN_SECONDS)
		return (false);
	i = -1;
	while (++i < BULLETS_SIZE)
	{
		if (!manager->bullets[i].is_alive)
		{
			entity_manager_bullet_init(manager->bullets + i, initial);
			manager->last_bullet_time = time;
			return (true);
		}
	}
	return (false);
}
