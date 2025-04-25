/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:44:26 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/25 17:42:33 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "game_init_internal.h"
#include <fcntl.h>
#include <unistd.h>

bool	texture_to_image(mlx_t *mlx, mlx_texture_t *txt, mlx_image_t **out_img)
{
	*out_img = mlx_texture_to_image(mlx, txt);
	if (out_img == NULL)
		return (false);
	return (true);
}

void	texture_clean(t_txts *txts)
{
	if (txts->north)
		mlx_delete_texture(txts->north);
	if (txts->east)
		mlx_delete_texture(txts->east);
	if (txts->south)
		mlx_delete_texture(txts->south);
	if (txts->west)
		mlx_delete_texture(txts->west);
}

bool	texture_load_png(char *png_path, mlx_texture_t	**out_txt)
{
	int	fd;

	fd = open(png_path, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		return (false);
	}
	close(fd);
	*out_txt = mlx_load_png(png_path);
	if (*out_txt == NULL)
		return (false);
	return (true);
}

bool	textures_init(t_game *game, t_config_file *config)
{
	t_config_file	*c;

	c = config;
	if (!texture_load_png(c->texture_north, &game->ctx.txts.north))
		return (game_init_fail(game, c, "invalid north texture"));
	if (!texture_load_png(c->texture_east, &game->ctx.txts.east))
		return (game_init_fail(game, c, "invalid east texture"));
	if (!texture_load_png(c->texture_south, &game->ctx.txts.south))
		return (game_init_fail(game, c, "invalid south texture"));
	if (!texture_load_png(c->texture_west, &game->ctx.txts.west))
		return (game_init_fail(game, c, "invalid west texture"));
	config_clean(config);
	return (true);
}
