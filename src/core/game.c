/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:32:41 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/27 19:26:55 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "ft_memlib.h"
#include "graphic/render.h"
#include "infrastructure/config/config.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils/output.h"
#include "utils/vec2.h"
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
	game_clean(game);
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

t_posdir system_input_posdir(const t_game *game)
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
	// TODO: ? when moving diagonaly normalize xy values
	// so that moving diagonaly is not faster
	return (posdir);
}

t_posdir system_update_posdir(
	const t_player *player, const t_posdir *input, double delta_time)
{
	t_posdir update;

	update.dir = (input->dir * delta_time) + player->angle;
	update.pos.x = ((cosf(update.dir) * input->pos.y   \
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


// TODO: move above functions to some other file


void	game_loop(t_game *game)
{
	t_posdir	input;
	t_posdir	update;

	input = system_input_posdir(game);
	//printf("input: x: %.2f y: %.2f a: %.2f\n", input.pos.x, input.pos.y, input.dir);
	update = system_update_posdir(&game->player, &input, game->mlx->delta_time);
	system_colision_resolve(game, &update);
	system_player_update(&game->player, &update);
	//printf("player_update: x: %.2f y: %.2f a: %.2f\n", game->player.pos.x, game->player.pos.y, game->player.angle);
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
	texture_clean(game);
	// TODO: clear map
	mlx_terminate(game->mlx);
}
