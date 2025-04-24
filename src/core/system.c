/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:00:03 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/24 20:44:53 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"
#include "MLX42/MLX42.h"
#include "core/game.h"
#include "graphic/render.h"
#include "utils/vec2.h"
#include <math.h>
#include <stdbool.h>
#include "core/manager.h"

void		system_input_angle(const t_game *game, t_location *location)
{
	t_vec2i	mouse_pos;

	mlx_get_mouse_pos(game->mlx, &mouse_pos.x, &mouse_pos.y);
	if (game->state.mouse && mouse_pos.x != 400)
	{
		if (mouse_pos.x < 400)
			location->angle -= 1.0f;
		else
			location->angle += 1.0f;
		mlx_set_mouse_pos(game->mlx, 400, 400);
		return ;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		location->angle -= 1.0f;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		location->angle += 1.0f;
}

t_location	system_input_location(const t_game *game)
{
	t_location	location;

	location = (t_location){{0.0f, 0.0f}, 0.0f};
	system_input_angle(game, &location);
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

void	system_input_state_switch( \
	t_state *state, t_manager *manager, mlx_t *mlx)
{
	if (state->time_since_last_update < 0.1)
	{
		state->time_since_last_update += mlx->delta_time;
		return ;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_SPACE))
	{
		if (entity_manager_spawn_bullet(manager, &manager->player.loc, \
				mlx_get_time()))
			state->time_since_last_update = 0.0;
		return ;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_M))
	{
		state->show_minimap++;
		state->show_minimap %= 3;
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_C))
		state->colision ^= 1;
	else if (mlx_is_key_down(mlx, MLX_KEY_N))
	{
		state->mouse ^= 1;
		if (state->mouse)
		{
			mlx_set_cursor_mode(mlx, MLX_MOUSE_HIDDEN);
			mlx_set_mouse_pos(mlx, 400, 400);
		}
		else
			mlx_set_cursor_mode(mlx, MLX_MOUSE_NORMAL);
	}
	state->time_since_last_update = 0.0;
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

void	system_colision_border(t_manager *manager, t_location *intention)
{
	const float player_half_size = manager->player.size / 2.0;

	if (intention->pos.x < player_half_size)
		intention->pos.x = player_half_size;
	else if (intention->pos.x > manager->chart.dimen.x - player_half_size)
		intention->pos.x = manager->chart.dimen.x - player_half_size;
	if (intention->pos.y < player_half_size)
		intention->pos.y = player_half_size;
	else if (intention->pos.y > manager->chart.dimen.y - player_half_size)
		intention->pos.y = manager->chart.dimen.y - player_half_size;
}

bool	has_cross(float new, float old, float player_half_size)
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

void system_colision_walls_h(
	t_manager *manager, t_location *intention, float p_half_size)
{
	int		offset;
	char	scene_entity;

	if (intention->pos.x > manager->player.loc.pos.x)
		offset = 1;
	else
		offset = -1;
	scene_entity = chart_entity(&manager->chart, (t_vec2f) {
			intention->pos.x + (p_half_size * offset),
			intention->pos.y
	});
	if (scene_entity != '1')
		return ;
	else if (offset > 0)
		intention->pos.x = ((int) intention->pos.x + 1) - p_half_size;
	else
		intention->pos.x = ((int) intention->pos.x) + p_half_size;
}

void	system_colision_walls_v(
	t_manager *manager, t_location *intention, float p_half_size)
{
	int		offset;
	char	scene_entity;

	if (intention->pos.y > manager->player.loc.pos.y)
		offset = 1;
	else
		offset = -1;
	scene_entity = chart_entity(&manager->chart, (t_vec2f) {
			intention->pos.x,
			intention->pos.y + (p_half_size * offset)
	});
	if (scene_entity != '1')
		return ;
	else if (offset > 0)
		intention->pos.y = ((int) intention->pos.y + 1) - p_half_size;
	else
		intention->pos.y = ((int) intention->pos.y) + p_half_size;
}

void	system_colision_walls_diag_resolve(
	t_manager *manager, t_location *intention, float p_half_size)
{
	const t_vec2f	movement_vec = vec2f_sub(\
		intention->pos, manager->player.loc.pos);
	float		diag_component = p_half_size * M_SQRT1_2 + 0.08;

	if (fabs(movement_vec.y) >= fabs(movement_vec.x))
	{
		if (movement_vec.x > 0)
			intention->pos.x = ((int) intention->pos.x + 1) - p_half_size;
		else
			intention->pos.x = ((int) intention->pos.x) + p_half_size;
		return ;
	}
	else if (fabs(movement_vec.x) > fabs(movement_vec.y))
	{
		if (movement_vec.y > 0)
			intention->pos.y = ((int) intention->pos.y + 1) - p_half_size;
		else
			intention->pos.y = ((int) intention->pos.y) + p_half_size;
		return ;
	}
	if (movement_vec.x > 0)
		intention->pos.x = ((int) intention->pos.x + 1) - diag_component;
	else
		intention->pos.x = ((int) intention->pos.x) + diag_component;
	if (movement_vec.y > 0)
		intention->pos.y = ((int) intention->pos.y + 1) - diag_component;
	else
		intention->pos.y = ((int) intention->pos.y) + diag_component;
}


void	system_colision_walls_diag(
	t_manager *manager, t_location *intention, float p_half_size)
{
	t_vec2i		offset;
	char		scene_entity_x;
	char		scene_entity_y;
	char		scene_entity_diag;

	if (intention->pos.y > manager->player.loc.pos.y)
		offset.y = 1;
	else
		offset.y = -1;
	if (intention->pos.x > manager->player.loc.pos.x)
		offset.x = 1;
	else
		offset.x = -1;

	scene_entity_y = chart_entity(&manager->chart, (t_vec2f) {
			intention->pos.x,
			intention->pos.y + (p_half_size * offset.y)
	});
	scene_entity_x = chart_entity(&manager->chart, (t_vec2f) {
			intention->pos.x + (p_half_size * offset.x),
			intention->pos.y
	});
	scene_entity_diag = chart_entity(&manager->chart, (t_vec2f) {
			intention->pos.x + (p_half_size * offset.x),
			intention->pos.y + (p_half_size * offset.y)
	});
	if (scene_entity_x == '1' && scene_entity_y == '1')
	{
		system_colision_walls_h(manager, intention, p_half_size);
		system_colision_walls_v(manager, intention, p_half_size);
	}
	else if (scene_entity_x == '1')
		system_colision_walls_h(manager, intention, p_half_size);
	else if (scene_entity_y == '1')
		system_colision_walls_v(manager, intention, p_half_size);
	else if (scene_entity_diag == '1')
		system_colision_walls_diag_resolve(manager, intention, p_half_size);
}

void	system_colision_walls(t_manager *manager, t_location *intention)
{
	const float		p_half_size = manager->player.size / 2.0;
	const t_vec2i   has_crossv = (t_vec2i) {
		has_cross(intention->pos.x, manager->player.loc.pos.x, p_half_size),
		has_cross(intention->pos.y, manager->player.loc.pos.y, p_half_size),
	};

	if (!has_crossv.x && !has_crossv.y)
		return;
	else if (has_crossv.x && !has_crossv.y)
		return system_colision_walls_h(manager, intention, p_half_size);
	else if (!has_crossv.x && has_crossv.y)
		return system_colision_walls_v(manager, intention, p_half_size);
	else
		return system_colision_walls_diag(manager, intention, p_half_size);
}


void system_colision_resolve( \
	t_game *game, t_manager *manager, t_location *intention)
{
	system_colision_border(manager, intention);
	if (game->state.colision)
		system_colision_walls(manager, intention);
}

void	system_player_location_set(t_player *player, t_location *new_location)
{
	player->loc = *new_location;
}
