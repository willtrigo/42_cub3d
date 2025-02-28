/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:00:03 by maurodri          #+#    #+#             */
/*   Updated: 2025/02/28 14:09:46 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"
#include <math.h>

t_posdir	system_input_posdir(const t_game *game)
{
	t_posdir	posdir;

	posdir = (t_posdir){{0.0f, 0.0f}, 0.0f};
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		posdir.dir -= 1.0f;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		posdir.dir += 1.0f;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		posdir.pos.y += 1.0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		posdir.pos.y -= 1.0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		posdir.pos.x -= 1.0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		posdir.pos.x += 1.0;
	(void) "when moving diagonaly normalize xy values"
		"so that moving diagonaly is not faster";
	if (posdir.pos.y != 0 && posdir.pos.x != 0)
		posdir.pos = vec2f_scale(posdir.pos, M_SQRT1_2);
	return (posdir);
}

t_posdir	system_update_posdir(
	const t_player *player, const t_posdir *input, double delta_time)
{
	t_posdir	update;

	update.dir = (input->dir * delta_time) + player->angle;
	update.pos.x = ((cosf(update.dir) * input->pos.y \
						+ cosf(update.dir + M_PI_2) * input->pos.x) \
					* delta_time) + player->pos.x;
	update.pos.y = ((sinf(update.dir) * input->pos.y \
						+ sinf(update.dir + M_PI_2) * input->pos.x) \
					* delta_time) + player->pos.y;
	return (update);
}

void	system_colision_resolve(t_game *game, t_posdir *posdir)
{
	// TODO: wall colision
	// TODO: border colision based on 1/2 *player size variable instead of 0.25
	if (posdir->pos.x < 0.25f)
		posdir->pos.x = 0.25f;
	else if (posdir->pos.x > game->chart.dimen.x - 0.25f)
		posdir->pos.x = game->chart.dimen.x - 0.25f;
	if (posdir->pos.y < 0.25f)
		posdir->pos.y = 0.25f;
	else if (posdir->pos.y > game->chart.dimen.y - 0.25f)
		posdir->pos.y = game->chart.dimen.y - 0.25f;
}

void	system_player_update(t_player *player, t_posdir *posdir)
{
	player->pos = posdir->pos;
	player->angle = posdir->dir;
}
