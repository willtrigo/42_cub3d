/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:06:57 by dande-je          #+#    #+#             */
/*   Updated: 2025/04/21 17:38:04 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "core/game.h"
#include "infrastructure/config/config.h"

void	keys_hook(mlx_key_data_t key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(game->mlx);
		return ;
	}
}

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
	mlx_loop_hook(game.mlx, (t_consumer) game_loop, (void *) &game);
	mlx_loop(game.mlx);
	game_clean(&game);
	return (EXIT_SUCCESS);
}
