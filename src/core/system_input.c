/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:09:34 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/25 16:14:43 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/manager.h"
#include "system.h"

static void	system_input_angle(const t_game *game, t_location *location)
{
	t_vec2i	mouse_pos;

	mlx_get_mouse_pos(game->mlx, &mouse_pos.x, &mouse_pos.y);
	if (game->state.mouse && mouse_pos.x != 400)
	{
		location->angle = (2 * (mouse_pos.x < 400)) - 1;
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

static void	system_input_state_switch_options( \
	t_state *state, t_manager *manager, mlx_t *mlx)
{
	(void) manager;
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
	system_input_state_switch_options(state, manager, mlx);
}
