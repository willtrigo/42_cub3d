/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:46:10 by maurodri          #+#    #+#             */
/*   Updated: 2025/02/28 14:34:28 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "core/game.h"
#include "utils/color.h"
#include "utils/vec2.h"
#include <math.h>
#include <stdio.h>
#include "draw.h"

char	chart_entity(t_chart *chart, t_vec2i pos);

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

void	draw_mini_floor(t_game *game, t_mini_args m)
{
	const t_vec2f	screen_pos = vec2f_add(\
		vec2f_scalei(m.grid_pos, m.block_size), m.offset);
	const t_vec2f	limit = vec2f_offset(screen_pos, (float)m.block_size);
	const t_color	color = (t_color){.value = 0xFFFFFFFF};
	t_vec2i			i;

	i.y = screen_pos.y - 1;
	while (++i.y < limit.y)
	{
		i.x = screen_pos.x - 1;
		while (++i.x < limit.x)
			mlx_put_pixel(game->ctx.canvas, i.x, i.y, color.value);
	}
}

void	draw_mini_texture(
	t_game *game, t_mini_args m, const mlx_texture_t *entity_sprite)
{
	const t_vec2f		screen_pos = vec2f_add(\
		vec2f_scalei(m.grid_pos, m.block_size), m.offset);
	const t_vec2f		limit = vec2f_offset(screen_pos, m.block_size);
	const t_vec2f		scale_txt = (t_vec2f){
		((float) entity_sprite->height) / m.block_size,
		((float) entity_sprite->width) / m.block_size
	};
	t_vec2i				px;
	t_vec2i				txt_pos;

	px.y = screen_pos.y - 1;
	while (++px.y < limit.y)
	{
		px.x = screen_pos.x - 1;
		txt_pos.y = (px.y - screen_pos.y) * scale_txt.y;
		while (++px.x < limit.x)
		{
			txt_pos.x = (px.x - screen_pos.x) * scale_txt.x;
			int idx = ((txt_pos.y * entity_sprite->width) + txt_pos.x) * 4;
			t_color color;
			color.value = 0;
			color.r = entity_sprite->pixels[idx + 0];
			color.g = entity_sprite->pixels[idx + 1];
			color.b = entity_sprite->pixels[idx + 2];
			color.a = entity_sprite->pixels[idx + 3];
			mlx_put_pixel(game->ctx.canvas, px.x, px.y, color.value);
		}
	}
}

void	draw_mini_player(t_game *game, t_mini_args m)
{
	const float		player_size = m.block_size / 2.0f;
	const t_vec2f	player_screen_pos_center = \
		vec2f_add(vec2f_scalei(m.grid_pos, m.block_size), m.offset);
	const t_vec2f	head_center = (t_vec2f){\
		player_screen_pos_center.x \
			+ (cosf(game->player.angle) * player_size / 2.0f), \
		player_screen_pos_center.y \
			+ (sinf(game->player.angle) * player_size / 2.0f)
	};
	t_color			color;

	color = (t_color){.value = 0x00FF00FF};
	draw_circle_cs(game->ctx.canvas, \
		player_screen_pos_center, player_size / 2.0f, color);
	color = (t_color){.value = 0x0000FFFF};
	draw_line_cs(game->ctx.canvas, player_screen_pos_center, \
		(t_vec2f){player_size, game->player.angle}, color);
	color = (t_color){.value = 0x000000FF};
	draw_square_cs(game->ctx.canvas, head_center, 4, color);
}

void	draw_mini_grid(t_game *game, t_mini_args m)
{
	const t_color	color = (t_color){.value = 0x0000ffFF};
	const t_vec2f	grid_size = m.grid_pos;
	const t_vec2f	limit = vec2f_scalei(grid_size, m.block_size);
	t_vec2i			i;

	i.y = 1;
	while (++i.y < limit.y)
	{
		i.x = -1;
		while (++i.x < limit.x)
			if ((i.x) % m.block_size == 0
				|| i.y % m.block_size == 0)
				mlx_put_pixel(game->ctx.canvas, i.x + m.offset.x, \
					i.y + m.offset.y, color.value);
	}
}

void	draw_mini_map(t_game *game, int block_size, t_vec2f offset)
{
	t_vec2i	i;
	char	entity;
	// TODO: improve logic draw_mini_map
	// TODO: remove mock values drawn_mini_map
	// TODO: draw player on draw_mini_map
	//const int	height = game->ctx.window.height;
	//const int	width = game->ctx.window.width;
	i = (t_vec2i){-1, -1};
	while (++i.y < game->chart.dimen.y)
	{
		i.x = -1;
		while (++i.x < game->chart.dimen.x)
		{
			entity = chart_entity(&game->chart, i);
			if (entity == '1')
				draw_mini_texture(game, (t_mini_args){\
					vec2i_tof(i), block_size, offset}, game->ctx.txts.north);
			else if (entity == '0')
				draw_mini_floor(game, (t_mini_args){\
					vec2i_tof(i), block_size, offset});
		}
	}
	draw_mini_player(game, (t_mini_args){\
			game->player.pos, block_size, offset});
	draw_mini_grid(game, (t_mini_args){\
			vec2i_tof(game->chart.dimen), block_size, offset});
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
		(game->ctx.window.height / 2.0f) - (height / 2),\
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
