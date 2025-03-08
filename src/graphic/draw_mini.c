/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:15:08 by maurodri          #+#    #+#             */
/*   Updated: 2025/03/08 16:43:14 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_mini.h"
#include "graphic/draw.h"
#include "graphic/render.h"
#include <math.h>
#include <stdio.h>

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
			int		idx = ((txt_pos.y * entity_sprite->width) + txt_pos.x) * 4;
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
	t_game *game, t_mini_args m, const t_grid_entity *entity)
{
	const t_vec2f	screen_pos = grid_pos_to_screen_pos(\
		m.grid_pos, m.block_size, m.offset);
	t_color			wall_color;

	if (entity->type == '1')
	{
		wall_color.a = 255;
		wall_color.r = (entity->direction == EAST) * 255;
		wall_color.b = ((entity->direction == WEST) \
			|| (entity->direction == SOUTH)) * 255;
		wall_color.g = (entity->direction == SOUTH) * 200;
		draw_square_cs(game->ctx.canvas, screen_pos, 8, wall_color);
		return (1);
	}
	else if (entity->type == '0')
		draw_square_cs(game->ctx.canvas, screen_pos, 8, (t_color){0x00FF00FF});
	return (0);
}

void	draw_mini_ray_dotgrid(t_game *game, t_mini_args m, float angle)
{
	const t_vec2f	unity = vec2f_unit_vector(angle);
	t_vec2f			grid_pos;
	t_grid_entity	entity;

	grid_pos = m.grid_pos;
	while (1)
	{
		grid_pos = grid_next_border(grid_pos, angle, unity);
		if (grid_pos.y < 0 || grid_pos.y > game->chart.dimen.y \
				|| grid_pos.x < 0 || grid_pos.x > game->chart.dimen.x)
			break ;
		entity = grid_entity(&game->chart, &grid_pos, &unity);
		if (draw_mini_ray_dotgrid_entity(game, (t_mini_args){\
				grid_pos, m.block_size, m.offset}, &entity))
			break ;
	}
}

void	draw_mini_map(t_game *game, int block_size, t_vec2f offset)
{
	const float	angle = game->player.angle;
	const float	fov1_2 = game->player.fov / 2.0f;
	const float	step = (10.0f * game->player.fov) / (block_size * game->ctx.window.height);
	float		i;

	draw_mini_bg_entities(game, (t_mini_args){\
			vec2i_tof(game->chart.dimen), block_size, offset});
	draw_mini_player(game, (t_mini_args){\
			game->player.pos, block_size, offset});
	draw_mini_grid(game, (t_mini_args){\
			vec2i_tof(game->chart.dimen), block_size, offset});
	i = -fov1_2;
	while (i < fov1_2)
	{
		draw_mini_ray(game, (t_mini_args){\
			game->player.pos, block_size, offset}, angle + i);
		draw_mini_ray_dotgrid(game, (t_mini_args){\
			game->player.pos, block_size, offset}, angle + i);
		i += step;
	}
	/* draw_mini_ray(game, (t_mini_args){\ */
	/* 		game->player.pos, block_size, offset}, angle); */
	/* draw_mini_ray_dotgrid(game, (t_mini_args){\ */
	/* 		game->player.pos, block_size, offset}, angle); */
}
