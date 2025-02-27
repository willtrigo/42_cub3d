/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:41:04 by dande-je          #+#    #+#             */
//   Updated: 2025/02/27 13:22:49 by maurodri         ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "graphic/render.h"
#include "core/game.h"
#include "utils/color.h"
#include "utils/vec2.h"
#include <math.h>
#include <stdio.h>

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
	const int	width = game->ctx.window.width;
	int			x;

	x = -1;
	while (++x < width)
		draw_level_col(game, x);
}

char	chart_entity(t_chart *chart, t_vec2i pos)
{
	return (chart->buffer[(pos.y * chart->dimen.x) + pos.x]);
}

t_vec2i	vec2i_scale(t_vec2i vec, int scalar)
{
	return (t_vec2i) { vec.x * scalar, vec.y * scalar};
}

t_vec2f	vec2f_scalei(t_vec2f vec, int scalar)
{
	return (t_vec2f) { vec.x * scalar, vec.y * scalar};
}

t_vec2i	vec2i_addf(t_vec2i vec_a, t_vec2f vec_b)
{
	return (t_vec2i) { vec_a.x + (int) vec_b.x, vec_a.y + (int) vec_b.y};
}

t_vec2f	vec2f_add(t_vec2f vec_a, t_vec2f vec_b)
{
	return (t_vec2f) { vec_a.x + (int) vec_b.x, vec_a.y + (int) vec_b.y};
}

t_vec2i	vec2i_offset(t_vec2i vec_a, int scalar)
{
	return (t_vec2i) { vec_a.x + scalar, vec_a.y + scalar};
}

t_vec2f	vec2f_offset(t_vec2f vec_a, float scalar)
{
	return (t_vec2f) { vec_a.x + scalar, vec_a.y + scalar};
}

void	draw_mini_floor(
	t_game *game, t_vec2i grid_pos, int block_size, t_vec2f offset)
{
	t_vec2i screen_pos = vec2i_addf(vec2i_scale(grid_pos, block_size),
									offset);
	t_vec2i limit = vec2i_offset(screen_pos, block_size);
	t_vec2i i;

	i.y = screen_pos.y - 1;
	while (++i.y < limit.y)
	{
		i.x = screen_pos.x - 1;
		while (++i.x < limit.x)
		{
			//printf("i.x: %d, i.y: %d\n", i.x, i.y);
			t_color color;
			color.value = 0xFFFFFFFF;
			mlx_put_pixel(game->ctx.canvas, i.x, i.y, color.value);
		}
	}
}

void	draw_mini_wall(
	t_game *game, t_vec2i grid_pos, int block_size, t_vec2f offset)
{
	const mlx_texture_t	*entity_sprite = game->ctx.txts.south;
	const t_vec2i		screen_pos = \
		vec2i_addf(vec2i_scale(grid_pos, block_size),offset);
	const t_vec2i		limit = vec2i_offset(screen_pos, block_size);
	const t_vec2f		scale_txt = (t_vec2f) {
		((float) entity_sprite->height) / block_size,
		((float) entity_sprite->width) / block_size
	};
	t_vec2i				i;
	t_vec2i				txt_pos;

	i.y = screen_pos.y - 1;
	while (++i.y < limit.y)
	{
		i.x = screen_pos.x - 1;
		txt_pos.y = (i.y - screen_pos.y) * scale_txt.y;
		while (++i.x < limit.x)
		{
			txt_pos.x = (i.x - screen_pos.x) * scale_txt.x;
			int iarr = ((txt_pos.y * entity_sprite->width) + txt_pos.x) * 4;
			//printf("i.x: %d, i.y: %d\n", i.x, i.y);
			t_color color;
			color.value = 0;
			color.r = entity_sprite->pixels[iarr + 0];
			color.g = entity_sprite->pixels[iarr + 1];
			color.b = entity_sprite->pixels[iarr + 2];
			color.a = entity_sprite->pixels[iarr + 3];
			mlx_put_pixel(game->ctx.canvas, i.x, i.y, color.value);
		}
	}
}


void	draw_circle( \
	mlx_image_t *canvas, t_vec2f center, float radius, t_color color)
{
	const t_vec2f	top_left_square = vec2f_offset(center, -radius);
	const t_vec2f	bottom_right_square = vec2f_offset(center, radius);
	const float		r2 = radius * radius;
	t_vec2i			i;

	i.y = top_left_square.y - 1;
	while (++i.y < bottom_right_square.y)
	{
		i.x = top_left_square.x - 1;
		while (++i.x < bottom_right_square.x)
		{
			// (x - a)^2 + (y - b)^2 < r^2
			float pos2 = ((i.x - center.x) * (i.x - center.x)) \
						+ ((i.y - center.y) * (i.y - center.y));
			if (pos2 < r2)
				mlx_put_pixel(canvas, i.x, i.y, color.value);
		}
	}
}

void	draw_square_sc( \
	mlx_image_t *canvas, t_vec2f center, int size, t_color color)
{
	const t_vec2f	top_left = (t_vec2f) { \
		center.x - (size / 2.0f) ,			 \
		center.y - (size / 2.0f)
	};
	const t_vec2f	bottom_right = (t_vec2f) { \
		center.x + (size / 2.0f) ,			 \
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

void	draw_line_sc( \
	mlx_image_t *canvas, t_vec2f center, t_vec2f size_angle, t_color color)
{
	const t_vec2f	pa = (t_vec2f) { \
		center.x - (cosf(size_angle.y) * (size_angle.x / 2.0f)),	\
		center.y - (sinf(size_angle.y) * size_angle.x / 2.0f)
	};
	const t_vec2f	pb = (t_vec2f) { \
		center.x + (cosf(size_angle.y) * size_angle.x / 2.0f),	\
		center.y + (sinf(size_angle.y) * size_angle.x / 2.0f)
	};
	t_vec2f			i;

	i = pa;
	while (fabs(i.y - pb.y) > 2.0f || fabs(i.x - pb.x) > 2.0f)
	{
		//mlx_put_pixel(canvas, i.x, i.y, color.value);
		draw_square_sc(canvas, i, 4, color);
		i = (t_vec2f){ i.x + cosf(size_angle.y), i.y + sinf(size_angle.y) };
	}
}

void	draw_mini_player(t_game *game, int block_size, t_vec2f offset)
{
	const float		player_size = block_size / 2.0f;
	const t_vec2f	player_screen_pos_center = \
		vec2f_add(vec2f_scalei(game->player.pos, block_size), offset);
	t_color	color;

	color = (t_color){.value = 0x00FF00FF};
	draw_circle(game->ctx.canvas, \
		player_screen_pos_center, player_size / 2.0f, color);
	color = (t_color){.value = 0x0000FFFF};
	draw_line_sc(game->ctx.canvas, player_screen_pos_center, \
				 (t_vec2f) { player_size, game->player.angle }, color);

	const t_vec2f	pb = (t_vec2f) { \
		player_screen_pos_center.x + (cosf(game->player.angle) * player_size / 2.0f), \
		player_screen_pos_center.y + (sinf(game->player.angle) * player_size / 2.0f)
	};
	color = (t_color) {.value = 0x000000FF};
	draw_square_sc(game->ctx.canvas, pb, 4, color);

}

void	draw_mini_map(t_game *game, int block_size, t_vec2f offset)
{
	// TODO: improve logic draw_mini_map
	// TODO: remove mock values drawn_mini_map
	// TODO: draw player on draw_mini_map
	//const int	height = game->ctx.window.height;
	//const int	width = game->ctx.window.width;
	game->chart.buffer = "1111110001100011010111111";
	game->chart.dimen = (t_vec2i) {5, 5};
	game->player.angle += 1 * game->mlx->delta_time;
	game->player.pos = (t_vec2f) {2.5f, 2.5f};
	t_vec2i	i;

	i = (t_vec2i) { -1, -1};
	while (++i.y < game->chart.dimen.y)
	{
		i.x = -1;
		while (++i.x < game->chart.dimen.x)
		{
			char entity = chart_entity(&game->chart, i);
			if (entity == '1')
				draw_mini_wall(game, i, block_size, offset);
			else if (entity == '0')
				draw_mini_floor(game, i, block_size, offset);
		}
	}
	draw_mini_player(game, block_size, offset);
}

int	render(t_game *game)
{
	draw_background(game);
	draw_level(game);
	//draw_player(game);
	draw_mini_map(game, 64, (t_vec2f) { 10.0f, 10.0f});
	return (EXIT_SUCCESS);
}

void	set_pixel(int x, int y, mlx_image_t *img, t_color *color)
{
	mlx_put_pixel(img, x, y, color->value);
}
