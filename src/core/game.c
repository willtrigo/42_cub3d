/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:32:41 by dande-je          #+#    #+#             */
/*   Updated: 2025/03/08 16:37:21 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "ft_memlib.h"
#include "graphic/render.h"
#include "texture.h"
#include "game_init_internal.h"
#include "system.h"
#include "utils/output.h"
#include <stdio.h>

void	game_loop(t_game *game)
{
	t_posdir	input;
	t_posdir	update;

	input = system_input_posdir(game);
	/* printf("input: x: %.2f y: %.2f a: %.2f\n",\ */
	/* 	input.pos.x, input.pos.y, input.dir); */
	update = system_update_posdir(&game->player, &input, game->mlx->delta_time);
	system_colision_resolve(game, &update);
	system_player_update(&game->player, &update);
	/* printf("player_update: x: %.2f y: %.2f a: %.2f\n", \ */
	/* 	game->player.pos.x, game->player.pos.y, game->player.angle); */
	render(game);
}

int	game_init(t_config_file *config, t_game *out_game)
{
	ft_bzero(out_game, sizeof(t_game));
	out_game->ctx.ceil = config->ceil;
	out_game->ctx.floor = config->floor;
	window_init(out_game);
	out_game->mlx = mlx_init(out_game->ctx.window.width, \
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
	// TODO: clear map
	if (game->mlx)
		mlx_terminate(game->mlx);
}
