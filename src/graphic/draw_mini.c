/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:15:08 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/19 21:17:30 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_mini.h"
#include "graphic/draw_primitive.h"
#include "graphic/render.h"
#include "utils/vec2.h"
#include <math.h>

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

	px.y = screen_pos.y - 1;
	while (++px.y < limit.y)
	{
		px.x = screen_pos.x - 1;
		while (++px.x < limit.x)
			mlx_put_pixel(game->ctx.canvas, px.x, px.y, \
				texture_get_color(entity_sprite, scale_txt, px, screen_pos));
	}
}

void	draw_mini_player(t_game *game, t_mini_args m, t_manager *manager)
{
	const float		player_size = m.block_size / 2.0f;
	const t_vec2f	player_screen_pos_center = \
		vec2f_add(vec2f_scalei(m.grid_pos, m.block_size), m.offset);
	const t_vec2f	head_center = (t_vec2f){\
		player_screen_pos_center.x \
			+ (cosf(manager->player.loc.angle) * player_size / 2.0f), \
		player_screen_pos_center.y \
			+ (sinf(manager->player.loc.angle) * player_size / 2.0f)
	};
	t_brush			brush;

	brush = (t_brush){{0x00FF00FF}, player_size / 2.0f};
	draw_circle_cs(game->ctx.canvas, \
		player_screen_pos_center, brush);
	brush = (t_brush){.color = {0x0000FFFF}, player_size / 4};
	draw_line_cs(game->ctx.canvas, player_screen_pos_center, \
		(t_vec2f){player_size, game->manager.player.loc.angle}, brush);
	brush = (t_brush){{0x000000FF}, player_size / 4};
	draw_square_cs(game->ctx.canvas, head_center, brush);
}

void	draw_mini_bg_entities(t_game *game, t_mini_args m, t_manager *manager)
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
			entity = chart_entity(&manager->chart, vec2i_tof(i));
			if (entity == '1')
				draw_mini_texture(game, (t_mini_args){vec2i_tof(i), \
					m.block_size, m.offset}, game->ctx.txts.north);
			else if (entity == '0')
				draw_mini_floor(game, (t_mini_args){\
					vec2i_tof(i), m.block_size, m.offset});
		}
	}
}

void	draw_mini_map(t_game *game, int block_size, t_vec2f offset)
{
	const t_mini_args	player_args = (t_mini_args){\
		game->manager.player.loc.pos, block_size, offset};
	const t_mini_args	dimen_args = (t_mini_args){\
		vec2i_tof(game->manager.chart.dimen), block_size, offset};

	draw_mini_bg_entities(game, dimen_args, &game->manager);
	draw_mini_player(game, player_args, &game->manager);
	if (game->state.show_minimap == 2)
	{
		draw_mini_grid(game, dimen_args);
		draw_mini_rays(game, player_args, &game->manager);
	}
}
