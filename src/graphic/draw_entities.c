/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 00:31:32 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/25 04:42:37 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/game.h"
#include "graphic/draw_primitive.h"
#include "graphic/grid.h"
#include "utils/vec2.h"
#include <math.h>
#include "core/location.h"

float	distance_if_visible(\
	const t_location *p_relative, const t_player *player, const t_chart *chart)
{
	const t_grid_entity	wall = grid_ray_wall(chart, \
			player->loc.pos, p_relative->angle + player->loc.angle);
	const float			wall_dist = fabs(vec2f_dot_product(\
		vec2f_unit_vector(p_relative->angle + player->loc.angle), \
		vec2f_sub(wall.pos, player->loc.pos)));
	const float			entity_dist = fabs(vec2f_dot_product(\
			vec2f_unit_vector(p_relative->angle + player->loc.angle), \
			p_relative->pos));

	if (entity_dist > wall_dist)
	{
		(void) "there is a wall blocking view";
		return (-1.0f);
	}
	else
		return (entity_dist);
}

t_vec2f	screen_pos_from_cam_relative(\
	const t_vec2f *cam_relative, float fov, const t_window *window)
{
	return ((t_vec2f){
		.x = ((cosf(fov * 0.5f) * (cam_relative->x / cam_relative->y)) \
					* (window->width * 0.55)) \
				+ (0.5 * window->width),
		.y = window->height * 0.5f
	});
}

void	draw_bullet(t_game *game, t_manager *manager, t_bullet *bullet)
{
	t_location	p_relative_bullet;
	float		distance;
	t_vec2f		cam_relative;
	t_vec2f		screen_pos;

	if (!bullet->is_alive)
		return ;
	p_relative_bullet = location_in_player_perspective(\
		&bullet->loc, &manager->player);
	if (!location_is_in_field_of_view(&p_relative_bullet, &manager->player))
		return ;
	distance = distance_if_visible(\
		&p_relative_bullet, &manager->player, &manager->chart);
	if (distance <= 0.0f)
		return ;
	cam_relative = vec2f_scale(vec2f_unit_vector(\
		p_relative_bullet.angle + M_PI_2), distance);
	cam_relative.x *= -1;
	screen_pos = screen_pos_from_cam_relative(\
		&cam_relative, manager->player.fov, &game->ctx.window);
	draw_circle_cs(game->ctx.canvas, screen_pos, \
		(t_brush){{0xFFFFFFFF}, bullet->size / cam_relative.y});
}

void	draw_entities(t_game *game, t_manager *manager)
{
	int	i;

	i = -1;
	while (++i < BULLETS_SIZE)
	{
		draw_bullet(game, manager, manager->bullets + i);
	}
}
