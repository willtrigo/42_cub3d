/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_internal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:51:36 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/22 22:29:18 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_init_internal.h"
#include "collection/ft_arraylist.h"
#include "core/game.h"
#include "core/map.h"
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
	const int	map_height = ft_arraylist_len(config->map);
	int			i;
	int			j;
	int			k;
	char		*ln;

	i = -1;
	k = 0;
	ft_bzero(&game->manager.player, sizeof(t_player));
	ft_bzero(&game->manager.chart, sizeof(t_chart));
	if (!map_validation(&game->manager, config, map_height))
		return (false);
	game->manager.chart.buffer = \
		ft_calloc((--config->map_width * map_height + 1),
			sizeof(char));
	while (++i < map_height)
	{
		j = 0;
		ln = ft_arraylist_get(config->map, i);
		while (ln[j])
			game->manager.chart.buffer[k++] = ln[j++];
	}
	game->manager.chart.dimen = (t_vec2i){config->map_width, map_height};
	game->manager.player.fov = 2.2f;
	return (true);
}

bool	game_init_fail(t_game *game, t_config_file *config, char *msg_error)
{
	config_clean(config);
	game_clean(game);
	if (msg_error)
		return (logerr_ret(msg_error, false));
	return (false);
}
