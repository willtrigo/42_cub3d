/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:32:41 by dande-je          #+#    #+#             */
/*   Updated: 2025/04/20 21:08:03 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "ft_memlib.h"
#include "graphic/render.h"
#include "texture.h"
#include "game_init_internal.h"
#include "system.h"
#include "utils/vec2.h"
#include <stdio.h>

t_location	location_move(const t_location *old_location, float velocity,
				float delta_time)
{
	const t_vec2f	movement_vec = vec2f_scale(
			vec2f_unit_vector(old_location->angle), velocity * delta_time);

	return ((t_location){
		.pos = vec2f_add(movement_vec, old_location->pos),
		.angle = old_location->angle
	});
}

void	system_entities_move(t_game *game)
{
	char		scene_entity;
	t_location	new_location;

	if (!game->bullet.is_alive)
		return ;
	new_location = location_move(&game->bullet.loc,
			game->bullet.velocity, game->mlx->delta_time);
	scene_entity = chart_entity(&game->chart, new_location.pos);
	if (scene_entity == '1')
	{
		game->bullet.is_alive = 0;
	}
	else
		game->bullet.loc = new_location;
}

void	game_loop(t_game *game)
{
	t_location	input;
	t_location	update;

	input = system_input_location(game);
	system_input_state_switch(game);
	update = system_player_location_update(&game->player, &input,
			game->mlx->delta_time);
	system_entities_move(game);
	system_colision_resolve(game, &update);
	system_player_location_set(&game->player, &update);
	render(game);
}

int	game_init(t_config_file *config, t_game *out_game)
{
	ft_bzero(out_game, sizeof(t_game));
	out_game->ctx.ceil = config->ceil;
	out_game->ctx.floor = config->floor;
	window_init(out_game);
	out_game->mlx = mlx_init(out_game->ctx.window.width,
			out_game->ctx.window.height, "cub3d", false);
	if (out_game->mlx == NULL)
		return (game_init_fail(out_game, config, "failed to initialize mlx"));
	if (!map_init(out_game, config))
		return (false);
	if (!textures_init(out_game, config))
		return (false);
	if (!canvas_init(out_game))
		return (false);
	return (true);
}

void	game_clean(t_game *game)
{
	texture_clean(&game->ctx.txts);
	canvas_clean(game->mlx, game->ctx.canvas);
	free(game->chart.buffer);
	game->chart.buffer = NULL;
	if (game->mlx)
		mlx_terminate(game->mlx);
}
