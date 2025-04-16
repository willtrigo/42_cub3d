/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_internal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:51:36 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/16 02:07:23 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_init_internal.h"
#include "core/game.h"
#include "ft_memlib.h"
#include "utils/output.h"

void	window_init(t_game *game)
{
	game->ctx.window.height = DEFAULT_HEIGHT;
	game->ctx.window.width = DEFAULT_WIDTH;
}

bool	canvas_init(t_game *game)
{
	const int	width = game->ctx.window.width;
	const int	height = game->ctx.window.height;

	game->ctx.canvas = mlx_new_image(game->mlx, width, height);
	if (game->ctx.canvas == NULL)
		return (false);
	return (true);
}

void	canvas_clean(mlx_t *mlx, mlx_image_t *canvas)
{
	if (canvas != NULL)
		mlx_delete_image(mlx, canvas);
}

bool	map_init(t_game *game, t_config_file *config)
{
	// TODO:
	ft_bzero(&game->player, sizeof(t_player));
	ft_bzero(&game->chart, sizeof(t_player));
	(void) game;
	(void) config;
	return (true);
}

bool	game_init_fail(t_game *game, t_config_file *config, char *msg_error)
{
	config_clean(config);
	game_clean(game);
	return (logerr_ret(msg_error, false));
}
