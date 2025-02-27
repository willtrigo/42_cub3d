/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:34:12 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/27 16:16:43 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "MLX42/MLX42.h"
# include "infrastructure/config/config.h"
# include "utils/color.h"
# include "utils/vec2.h"

# define DEFAULT_WIDTH 1920
# define DEFAULT_HEIGHT 955

// angle: radians
typedef struct s_player
{
	t_vec2f	pos;
	float	angle;
}	t_player;

typedef struct s_chart
{
	t_vec2i	dimen;
	char	*buffer;
}	t_chart;

typedef struct s_txts
{
	mlx_texture_t	*north;
	mlx_texture_t	*east;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
}	t_txts;

typedef struct s_window
{
	int	height;
	int	width;
	int	block_size;
}	t_window;

typedef struct s_context
{
	mlx_image_t	*canvas;
	t_txts		txts;
	t_window	window;
	t_color		ceil;
	t_color		floor;
}	t_context;

typedef struct s_game
{
	t_context	ctx;
	mlx_t		*mlx;
	t_chart		chart;
	t_player	player;
}	t_game;

int		game_init(t_config_file *config, t_game *out_game);
void	game_loop(t_game *game);
void	keys_hook(mlx_key_data_t key, void *param);
void	game_clean(t_game *game);

#endif
