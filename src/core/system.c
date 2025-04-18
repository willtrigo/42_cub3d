/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:00:03 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/18 01:27:45 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"
#include "core/game.h"
#include "utils/vec2.h"
#include <math.h>

t_location	system_input_location(const t_game *game)
{
	t_location	location;

	location = (t_location){{0.0f, 0.0f}, 0.0f};
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		location.angle -= 1.0f;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		location.angle += 1.0f;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		location.pos.y += 1.0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		location.pos.y -= 1.0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		location.pos.x -= 1.0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		location.pos.x += 1.0;
	(void) "when moving diagonaly normalize xy values"
		"so that moving diagonaly is not faster";
	if (location.pos.y != 0 && location.pos.x != 0)
		location.pos = vec2f_scale(location.pos, M_SQRT1_2);
	return (location);
}

void	system_input_state_switch(t_game *game)
{
	if (game->state.time_since_last_update < 0.1)
	{
		game->state.time_since_last_update += game->mlx->delta_time;
		return ;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_M))
	{
		game->state.show_minimap++;
		game->state.show_minimap %= 3;
		game->state.time_since_last_update = 0.0;
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE) &&!game->bullet.is_alive)
	{
		game->bullet.is_alive = 1;
		game->bullet.loc = game->player.loc;
		game->bullet.velocity = 2.0f;
		game->bullet.size = 8.0f;
		game->state.time_since_last_update = 0.0;
	}
}

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

// TODO: wall colision
// TODO: border colision based on 1/2 *player size variable instead of 0.25
void	system_colision_resolve(t_game *game, t_location *location)
{
	if (location->pos.x < 0.25f)
		location->pos.x = 0.25f;
	else if (location->pos.x > game->chart.dimen.x - 0.25f)
		location->pos.x = game->chart.dimen.x - 0.25f;
	if (location->pos.y < 0.25f)
		location->pos.y = 0.25f;
	else if (location->pos.y > game->chart.dimen.y - 0.25f)
		location->pos.y = game->chart.dimen.y - 0.25f;
}

void	system_player_location_set(t_player *player, t_location *new_location)
{
	player->loc = *new_location;
}
