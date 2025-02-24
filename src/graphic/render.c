/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:41:04 by dande-je          #+#    #+#             */
//   Updated: 2025/02/24 19:23:53 by maurodri         ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "graphic/render.h"
#include "core/game.h"
#include "utils/color.h"

void	draw_background(t_game *game)
{
	const int	height = game->ctx.window.height;
	const int	width = game->ctx.window.width;
	int			y;
	int			x;

	y = -1;
	while (++y < height / 2)
	{
		x = -1;
		while (++x < width)
			set_pixel(x, y, game->ctx.canvas, &game->ctx.ceil);
	}
	y--;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
			set_pixel(x, y, game->ctx.canvas, &game->ctx.floor);
	}
}

void	draw_level_col(t_game *game, int x)
{
	int				y;
	float			height = 256.0f;
	float			width = 256.0f;
	mlx_texture_t	*txt = game->ctx.txts.south;

	float scale_height = ((float) txt->height) / height;
	float scale_width = ((float) txt->width) / width;
	int left_margin = 0;
	int top_margin = (game->ctx.window.height / 2.0f) - (height / 2);
	int bottom_margin = (game->ctx.window.height / 2.0f) + (height / 2);
	if (x >= left_margin && x < left_margin + width)
	{
		y = top_margin - 1;
		int px_x = (x - left_margin) * scale_width;
		while (++y < bottom_margin)
		{
			int px_y = (y - top_margin) * scale_height;
			int i = ((px_y * txt->width) + px_x) * 4;
			//printf("px_x: %d, px_y: %d, i: %d\n", px_x, px_y, i);
			t_color color;
			color.value = 0;
			color.r = txt->pixels[i + 0];
			color.g = txt->pixels[i + 1];
			color.b = txt->pixels[i + 2];
			color.a = txt->pixels[i + 3];
			mlx_put_pixel(game->ctx.canvas, x, y, color.value);
		}
	}
}

void	draw_level(t_game *game)
{
	// TODO: temporary test implementation, reimplement with raycasting
	const int	height = game->ctx.window.height;
	const int	width = game->ctx.window.width;
	int			x;

	x = -1;
	while (++x < width)
		draw_level_col(game, x);
}

int	render(t_game *game)
{
	draw_background(game);
	draw_level(game);
	//draw_player(game);
	return (EXIT_SUCCESS);
}

void	set_pixel(int x, int y, mlx_image_t *img, t_color *color)
{
	mlx_put_pixel(img, x, y, color->value);
}
