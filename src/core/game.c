/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:32:41 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/26 12:33:50 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "ft_memlib.h"
#include "graphic/render.h"
#include "infrastructure/config/config.h"
#include <stdlib.h>
#include "utils/output.h"
#include "game.h"

void	window_init(t_game *game)
{
	game->ctx.window.height = DEFAULT_HEIGHT;
	game->ctx.window.width = DEFAULT_WIDTH;
}

bool	texture_to_image(mlx_t *mlx, mlx_texture_t *txt, mlx_image_t **out_img)
{
	*out_img = mlx_texture_to_image(mlx, txt);
	if (out_img == NULL)
		return (false);
	return (true);
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

bool	map_init(t_game *game, t_config_file *config)
{
	// TODO:
	(void) game;
	(void) config;
	return (true);
}

void	texture_clean(t_game *game)
{
	if (game->ctx.txts.north)
		mlx_delete_texture(game->ctx.txts.north);
	if (game->ctx.txts.east)
		mlx_delete_texture(game->ctx.txts.east);
	if (game->ctx.txts.south)
		mlx_delete_texture(game->ctx.txts.south);
	if (game->ctx.txts.west)
		mlx_delete_texture(game->ctx.txts.west);
}

bool	texture_init_fail(t_game *game, t_config_file *config, char *msg_error)
{
	config_clean(config);
	texture_clean(game);
	return (output_ret(msg_error, false));
}

bool	textures_init(t_game *game, t_config_file *config)
{
	game->ctx.txts.north = mlx_load_png(config->texture_north);
	if (!game->ctx.txts.north)
		return (texture_init_fail(game, config, "\nError: invalid north texture"));
	game->ctx.txts.east = mlx_load_png(config->texture_east);
	if (!game->ctx.txts.east)
		return (texture_init_fail(game, config, "\nError: invalid east texture"));
	game->ctx.txts.south = mlx_load_png(config->texture_south);
	if (!game->ctx.txts.south)
		return (texture_init_fail(game, config, "\nError: invalid south texture"));
	game->ctx.txts.west = mlx_load_png(config->texture_west);
	if (!game->ctx.txts.west)
		return (texture_init_fail(game, config, "\nError: invalid west texture"));
	config_clean(config);
	return (true);
}

// TODO: move above functions to some other file

void	game_loop(t_game *game)
{
	// TODO:
	// get input
	// calculate new position
	// check colisions
	// resolve colisions
	// update positions of entities
	// render new game state
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
		return (false);
	if (!map_init(out_game, config))
		return (false);
	if (!textures_init(out_game, config))
		return (false);
	if (!canvas_init(out_game))
		return (false);
	return (true);
}

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

void	game_clean(t_game *game)
{
	// TODO:
	texture_clean(game);
	// clear map
	mlx_terminate(game->mlx);
}
