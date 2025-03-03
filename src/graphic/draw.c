/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:46:10 by maurodri          #+#    #+#             */
/*   Updated: 2025/03/03 12:41:06 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "core/game.h"
#include "utils/color.h"
#include "utils/vec2.h"
#include <math.h>
#include <stdio.h>
#include "draw.h"

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
			int 	idx = ((txt_pos.y * entity_sprite->width) + txt_pos.x) * 4;
			t_color	color;
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

void	draw_mini_bg_entities(t_game *game, t_mini_args m)
{
	const t_vec2f	grid_size = m.grid_pos;
	t_vec2i			i;
	char			entity;

	i = (t_vec2i){-1, -1};
	while (++i.y < grid_size.y)
	{
		i.x = -1;
		while (++i.x < grid_size.x)
		{
			entity = chart_entity(&game->chart, vec2i_tof(i));
			if (entity == '1')
				draw_mini_texture(game, (t_mini_args){vec2i_tof(i), \
					m.block_size, m.offset}, game->ctx.txts.north);
			else if (entity == '0')
				draw_mini_floor(game, (t_mini_args){\
					vec2i_tof(i), m.block_size, m.offset});
		}
	}
}

void	draw_mini_ray(t_game *game, t_mini_args m, float angle)
{
	const t_vec2f	screen_bottom_right = vec2f_add(\
		vec2f_scale(vec2i_tof(game->chart.dimen), m.block_size), m.offset);
	t_vec2f			grid_pos;
	char			entity;
	t_vec2f			screen_pos;

	//const int	height = game->ctx.window.height;
	//const int	width = game->ctx.window.width;
	grid_pos = m.grid_pos;
	screen_pos = vec2f_add(vec2f_scale(grid_pos, m.block_size), m.offset);
	while (screen_pos.y < screen_bottom_right.y && screen_pos.y > m.offset.y)
	{
		entity = chart_entity(&game->chart, grid_pos);
		if (entity == '1')
			break ;
		else if (entity == '0')
			draw_square_cs(game->ctx.canvas, screen_pos \
				, 1, (t_color){0x000000FF});
		screen_pos = (t_vec2f){screen_pos.x + cosf(angle), \
			screen_pos.y + sinf(angle)};
		grid_pos = vec2f_scale(vec2f_add(\
			screen_pos, vec2f_scale(m.offset, -1.0f)), 1.0f / m.block_size);
	}
}

int	draw_mini_ray_dotgrid_entity(
	t_game *game, t_mini_args m, const t_vec2f *unity)
{
	const t_vec2i	is_on_grid = (t_vec2i){\
		fmod(m.grid_pos.x, 1.0f) == 0, \
		fmod(m.grid_pos.y, 1.0f) == 0};
	const t_vec2i	off_i = (t_vec2i){\
		-(unity->x < 0 && is_on_grid.x), \
		-(unity->y < 0 && is_on_grid.y)};
	t_color			wall_color;
	t_vec2f			screen_pos;
	char			entity;

	entity = chart_entity(&game->chart, vec2f_addi(m.grid_pos, off_i));
	screen_pos = vec2f_add(vec2f_scale(m.grid_pos, m.block_size), m.offset);
	if (entity == '1')
	{
		wall_color.a = 255;
		wall_color.r = (unity->x > 0 && is_on_grid.x) * 255;
		wall_color.b = (unity->x < 0 && is_on_grid.x \
			|| (unity->y > 0 && is_on_grid.y)) * 255;
		wall_color.g = (unity->y > 0 && is_on_grid.y) * 200;
		draw_square_cs(game->ctx.canvas, screen_pos, 8, wall_color);
		return (1);
	}
	else if (entity == '0')
		draw_square_cs(game->ctx.canvas, screen_pos, 8, (t_color){0x00FF00FF});
	return (0);
}

void	draw_mini_ray_dotgrid(t_game *game, t_mini_args m, float angle)
{
	const t_vec2f	unity = vec2f_unit_vector(angle);
	t_vec2f			grid_pos;
	t_vec2f			v;
	t_vec2f			h;
	t_vec2f			mag;

	grid_pos = m.grid_pos;
	while (grid_pos.y > 0 && grid_pos.y < game->chart.dimen.y
		&& grid_pos.x > 0 && grid_pos.x < game->chart.dimen.x)
	{
		v.y = ((int)(grid_pos.y + ((unity.y > 0) * 1 + (unity.y < 0 \
			&& fmod(grid_pos.y, 1.0f) == 0.f) * (-1)))) - grid_pos.y;
		v.x = tanf(M_PI_2 - angle) * v.y;
		h.x = ((int)(grid_pos.x + ((unity.x > 0) * 1 + (unity.x < 0 \
			&& fmod(grid_pos.x, 1.0f) == 0.f) * (-1)))) - grid_pos.x;
		h.y = -tanf(M_PI - angle) * h.x;
		mag = (t_vec2f){vec2f_magnitude2(h), vec2f_magnitude2(v)};
		if ((mag.x > 0.0000000001f && mag.x < mag.y) || mag.y < 0.0000000001f)
			grid_pos = vec2f_add(grid_pos, h);
		else
			grid_pos = vec2f_add(grid_pos, v);
		if (draw_mini_ray_dotgrid_entity(game, (t_mini_args){\
				grid_pos, m.block_size, m.offset}, &unity))
			break ;
	}
}

void	draw_mini_map(t_game *game, int block_size, t_vec2f offset)
{
	const float	angle = game->player.angle;

	draw_mini_bg_entities(game, (t_mini_args){\
			vec2i_tof(game->chart.dimen), block_size, offset});
	draw_mini_player(game, (t_mini_args){\
			game->player.pos, block_size, offset});
	draw_mini_grid(game, (t_mini_args){\
			vec2i_tof(game->chart.dimen), block_size, offset});
	draw_mini_ray(game, (t_mini_args){\
			game->player.pos, block_size, offset}, angle);
	draw_mini_ray_dotgrid(game, (t_mini_args){\
			game->player.pos, block_size, offset}, angle);
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
