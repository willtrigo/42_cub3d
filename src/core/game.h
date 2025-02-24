/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:34:12 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/24 11:42:46 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

#include "MLX42/MLX42.h"
# include "infrastructure/config/config.h"

# define DEFAULT_WIDTH 1920
# define DEFAULT_HEIGHT 995

typedef struct s_context
{
	struct
	{
		mlx_image_t	*bg;
	} imgs;
	struct
	{
		// TODO: add textures
		mlx_texture_t	*some_texture;
	} txt;
	struct
	{
		int	height;
		int	width;
	}	window;
}	t_context;

typedef struct s_game
{
	t_context	ctx;
	mlx_t		*mlx;
	// map
	// player
}	t_game;

int		game_init(t_config_file *config, t_game *out_game);
void	game_loop(t_game *game);
void	game_clean(t_game *game);

#endif
