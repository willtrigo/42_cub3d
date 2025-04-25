/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:10:25 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/19 21:13:56 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_mini.h"
#include "graphic/camera.h"
#include "graphic/draw_primitive.h"
#include "graphic/render.h"

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
		draw_square_cs(game->ctx.canvas, screen_pos, \
			(t_brush){{0x00FF00FF}, m.block_size / 8});
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
