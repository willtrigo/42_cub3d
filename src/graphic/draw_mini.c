/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:15:08 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/19 04:13:12 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_mini.h"
#include "graphic/camera.h"
#include "graphic/draw_primitive.h"
#include "graphic/grid.h"
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

void	draw_mini_ray(\
	t_game *game, t_mini_args m, float angle, t_manager *manager)
{
	const t_vec2f	screen_bottom_right = vec2f_add(\
		vec2f_scale(vec2i_tof(manager->chart.dimen), m.block_size), m.offset);
	t_vec2f			grid_pos;
	char			entity;
	t_vec2f			screen_pos;

	grid_pos = m.grid_pos;
	screen_pos = vec2f_add(vec2f_scale(grid_pos, m.block_size), m.offset);
	while (screen_pos.y < screen_bottom_right.y && screen_pos.y > m.offset.y)
	{
		entity = chart_entity(&manager->chart, grid_pos);
		if (entity == '1')
			break ;
		else if (entity == '0')
			draw_square_cs(game->ctx.canvas, screen_pos \
				, (t_brush){{0x000000FF}, 1});
		screen_pos = (t_vec2f){screen_pos.x + cosf(angle), \
			screen_pos.y + sinf(angle)};
		grid_pos = vec2f_scale(\
			vec2f_sub(screen_pos, m.offset), 1.0f / m.block_size);
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
		draw_square_cs(game->ctx.canvas, \
			screen_pos, (t_brush){wall_color, m.block_size / 8});
		return (1);
	}
	else if (entity->type == '0')
		draw_square_cs(game->ctx.canvas, screen_pos, (t_brush){{0x00FF00FF}, m.block_size / 8});
	return (0);
}

void	draw_mini_ray_dotgrid(\
	t_game *game, t_mini_args m, float angle, t_manager *manager)
{
	const t_vec2f	unity = vec2f_unit_vector(angle);
	t_vec2f			grid_pos;
	t_grid_entity	entity;

	grid_pos = m.grid_pos;
	while (1)
	{
		grid_pos = grid_next_border(grid_pos, angle, unity);
		if (grid_pos.y < 0 || grid_pos.y > manager->chart.dimen.y \
				|| grid_pos.x < 0 || grid_pos.x > manager->chart.dimen.x)
			break ;
		entity = grid_entity(&manager->chart, &grid_pos, &unity);
		if (draw_mini_ray_dotgrid_entity(game, (t_mini_args){\
				grid_pos, m.block_size, m.offset}, &entity))
			break ;
	}
}

void	draw_mini_fov(\
	t_game *game, int block_size, t_vec2f offset, const t_camera *c)
{
	const t_vec2f	player_screen = grid_pos_to_screen_pos(\
		game->manager.player.loc.pos, block_size, offset);
	const t_vec2f	caml_screen = \
		grid_pos_to_screen_pos(c->caml, block_size, offset);
	const t_vec2f	camr_screen = \
		grid_pos_to_screen_pos(c->camr, block_size, offset);
	const t_color	color = (t_color){0xFF00FFFF};

	draw_line_p(game->ctx.canvas, \
				player_screen, caml_screen, (t_brush){color, block_size / 16});
	draw_line_p(game->ctx.canvas, \
		player_screen, camr_screen, (t_brush){color, block_size / 16});
	draw_line_p(game->ctx.canvas, \
		camr_screen, caml_screen, (t_brush){color, block_size / 16});
}

void	draw_mini_rays(t_game *game, t_mini_args m, t_manager *manager)
{
	t_camera	c;
	int			i;
	t_vec2f		player_to_camv_step;
	float		angle;

	camera_init(&manager->player, &c, 40);
	draw_mini_fov(game, m.block_size, m.offset, &c);
	i = -1;
	while (++i <= c.num_rays)
	{
		draw_square_cs(game->ctx.canvas,
			grid_pos_to_screen_pos(\
				vec2f_add(c.caml, vec2f_scale(c.camv_step, i)), \
				m.block_size, m.offset), \
					(t_brush){{0x000000FF}, m.block_size / 16});
		player_to_camv_step = vec2f_sub(\
				vec2f_add(c.caml, vec2f_scale(c.camv_step, i)), \
				manager->player.loc.pos);
		angle = atan2(player_to_camv_step.y, player_to_camv_step.x);
		draw_mini_ray(game, m, angle, manager);
		draw_mini_ray_dotgrid(game, m, angle, manager);
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
