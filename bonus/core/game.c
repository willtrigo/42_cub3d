/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:32:41 by dande-je          #+#    #+#             */
/*   Updated: 2025/04/23 23:01:31 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "core/manager.h"
#include "ft_memlib.h"
#include "graphic/render.h"
#include "texture.h"
#include "game_init_internal.h"
#include "system.h"
#include <stdio.h>

void	game_loop(t_game *game)
{
	t_location	input;
	t_location	update;

	input = system_input_location(game);
	system_input_state_switch(&game->state, &game->manager, game->mlx);
	update = system_player_location_update(&game->manager.player,
			&input, game->mlx->delta_time);
	manager_entities_move(&game->manager, game);
	system_colision_resolve(game, &game->manager, &update);
	system_player_location_set(&game->manager.player, &update);
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
		return (game_init_fail(out_game, config, NULL));
	if (!textures_init(out_game, config))
		return (game_init_fail(out_game, config, NULL));
	if (!canvas_init(out_game))
		return (game_init_fail(out_game, config, NULL));
	return (true);
}

void	game_clean(t_game *game)
{
	texture_clean(&game->ctx.txts);
	canvas_clean(game->mlx, game->ctx.canvas);
	if (game->manager.chart.buffer)
	{
		free(game->manager.chart.buffer);
		game->manager.chart.buffer = NULL;
	}
	if (game->mlx)
		mlx_terminate(game->mlx);
}
