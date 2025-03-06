/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:46:10 by maurodri          #+#    #+#             */
/*   Updated: 2025/03/06 19:41:09 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "core/game.h"
#include "utils/color.h"
#include "utils/vec2.h"
#include <math.h>
#include <stdio.h>
#include "draw.h"
#include "render.h"
#include "ft_assert.h"
#include "grid.h"

void	draw_circle_cs( \
	mlx_image_t *canvas, t_vec2f center, float radius, t_color color)
{
	const t_vec2f	top_left_square = vec2f_offset(center, -radius);
	const t_vec2f	bottom_right_square = vec2f_offset(center, radius);
	const float		r2 = radius * radius;
	t_vec2i			i;
	float			sum_squares;

	i.y = top_left_square.y - 1;
	while (++i.y < bottom_right_square.y)
	{
		i.x = top_left_square.x - 1;
		while (++i.x < bottom_right_square.x)
		{
			(void)"(x - a)^2 + (y - b)^2 < r^2";
			sum_squares = ((i.x - center.x) * (i.x - center.x)) \
						+ ((i.y - center.y) * (i.y - center.y));
			if (sum_squares < r2)
				mlx_put_pixel(canvas, i.x, i.y, color.value);
		}
	}
}

void	draw_square_cs( \
	mlx_image_t *canvas, t_vec2f center, int size, t_color color)
{
	const t_vec2f	top_left = (t_vec2f){\
		center.x - (size / 2.0f), \
		center.y - (size / 2.0f)
	};
	const t_vec2f	bottom_right = (t_vec2f){\
		center.x + (size / 2.0f), \
		center.y + (size / 2.0f)
	};
	t_vec2f			i;

	i.y = top_left.y - 1;
	while (++i.y < bottom_right.y)
	{
		i.x = top_left.x - 1;
		while (++i.x < bottom_right.x)
		{
			mlx_put_pixel(canvas, i.x, i.y, color.value);
		}
	}
}

void	draw_line_cs( \
	mlx_image_t *canvas, t_vec2f center, t_vec2f size_angle, t_color color)
{
	const t_vec2f	pa = (t_vec2f){\
		center.x - (cosf(size_angle.y) * (size_angle.x / 2.0f)),	\
		center.y - (sinf(size_angle.y) * size_angle.x / 2.0f)
	};
	const t_vec2f	pb = (t_vec2f){\
		center.x + (cosf(size_angle.y) * size_angle.x / 2.0f),	\
		center.y + (sinf(size_angle.y) * size_angle.x / 2.0f)
	};
	t_vec2f			i;

	i = pa;
	while (fabs(i.y - pb.y) > 2.0f || fabs(i.x - pb.x) > 2.0f)
	{
		draw_square_cs(canvas, i, 4, color);
		i = (t_vec2f){i.x + cosf(size_angle.y), i.y + sinf(size_angle.y)};
	}
}

void	draw_background(t_game *game)
{
	const int	height = game->ctx.window.height;
	const int	width = game->ctx.window.width;
	t_vec2i		i;

	i.y = -1;
	while (++i.y < height / 2)
	{
		i.x = -1;
		while (++i.x < width)
			mlx_put_pixel(game->ctx.canvas, i.x, i.y, game->ctx.ceil.value);
	}
	i.y--;
	while (++i.y < height)
	{
		i.x = -1;
		while (++i.x < width)
			mlx_put_pixel(game->ctx.canvas, i.x, i.y, game->ctx.floor.value);
	}
}

void	draw_level_col(t_game *game, int x)
{
	int					y;
	const float			height = 256.0f;
	const float			width = 256.0f;
	const mlx_texture_t	*txt = game->ctx.txts.south;

	t_vec2f				scale = (t_vec2f){((float) txt->height) / height, \
											((float) txt->width) / width};
	t_vec2i				margin_horizontal = (t_vec2i){0, width};
	t_vec2i				margin_vertical = (t_vec2i){\
		(game->ctx.window.height / 2.0f) - (height / 2), \
		(game->ctx.window.height / 2.0f) + (height / 2)};
	t_vec2i				px;

	// TODO: find wall with ray_cast
	// TODO: find wall size and direction
	// TODO: find wall x offset in relation to wall beggining
	// TODO: get wall texture
	// TODO: remove mock values
	// TODO: remove if
	if (x >= margin_horizontal.x && x < margin_horizontal.y)
	{
		y = margin_vertical.x - 1;
		px.x = (x - margin_horizontal.x) * scale.x;
		while (++y < margin_vertical.y)
		{
			px.y = (y - margin_vertical.x) * scale.y;
			int i = ((px.y * txt->width) + px.x) * 4;
			//printf("px_x: %d, px_y: %d, i: %d\n", px_x, px_y, i);
			t_color color;
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
	const int	width = game->ctx.window.width;
	int			x;

	x = -1;
	while (++x < width)
		draw_level_col(game, x);
}
