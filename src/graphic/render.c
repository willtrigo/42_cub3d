/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:41:04 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/26 12:47:54 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "graphic/render.h"
#include "core/game.h"
#include "utils/color.h"
#include "utils/vec2.h"

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

t_vec2i	vec2i_addf(t_vec2i vec_a, t_vec2f vec_b)
{
	return (t_vec2i) { vec_a.x + (int) vec_b.x, vec_a.y + (int) vec_b.y};
}

t_vec2i	vec2i_offset(t_vec2i vec_a, int scalar)
{
	return (t_vec2i) { vec_a.x + scalar, vec_a.y + scalar};
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
			color.value = 0;
			color.a = 255;
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

void	draw_mini_map(t_game *game, int block_size, t_vec2f offset)
{
	// TODO: improve logic draw_mini_map
	// TODO: remove mock values drawn_mini_map
	// TODO: draw player on draw_mini_map
	//const int	height = game->ctx.window.height;
	//const int	width = game->ctx.window.width;
	game->chart.buffer = "1111110001100011010111111";
	game->chart.dimen = (t_vec2i) {5, 5};
	game->player.angle = 0;
	game->player.pos = (t_vec2f) {3.5f, 3.5f};
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
}

int	render(t_game *game)
{
	draw_background(game);
	draw_level(game);
	//draw_player(game);
	draw_mini_map(game, 16, (t_vec2f) { 10.0f, 10.0f});
	return (EXIT_SUCCESS);
}

void	set_pixel(int x, int y, mlx_image_t *img, t_color *color)
{
	mlx_put_pixel(img, x, y, color->value);
}
