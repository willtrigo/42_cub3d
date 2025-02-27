/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:06:57 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/27 18:10:35 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "core/game.h"
#include "infrastructure/config/config.h"

int	main(int argc, char **argv)
{
	t_config_file	config;
	t_game			game;

	if (!config_init(--argc, ++argv, &config))
		return (EXIT_FAILURE);
	if (!game_init(&config, &game))
		return (EXIT_FAILURE);
	mlx_key_hook(game.mlx, keys_hook, &game);
	mlx_image_to_window(game.mlx, game.ctx.canvas, 0, 0);
	game.player = (t_player){.angle = 0, .pos = {3.5f, 3.5f}};
	game.chart.buffer = "1111110001100011010111111";
	game.chart.dimen = (t_vec2i){5, 5};
	mlx_loop_hook(game.mlx, (t_consumer) game_loop, (void *) &game);
	mlx_loop(game.mlx);
	game_clean(&game);
	return (EXIT_SUCCESS);
}
