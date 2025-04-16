/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:41:04 by dande-je          #+#    #+#             */
/*   Updated: 2025/04/16 07:27:55 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic/render.h"
#include "core/game.h"
#include "graphic/camera.h"
#include "graphic/draw_primitive.h"
#include "graphic/grid.h"
#include "utils/vec2.h"
#include "draw.h"
#include "draw_mini.h"
#include <math.h>
#include <stdio.h>

char	chart_entity(const t_chart *chart, t_vec2f pos)
{
	const t_vec2i	posi = {pos.x, pos.y};

	if (pos.x < 0 || pos.x >= chart->dimen.x ||
		pos.y < 0 || pos.y >= chart->dimen.y)
		return '1';

	return (chart->buffer[(posi.y * chart->dimen.x) + posi.x]);
}

void	draw_entities(t_game *game)
{
	if (!game->bullet.is_alive)
		return ;
	const t_vec2f diff = vec2f_sub(game->bullet.loc.pos, game->player.loc.pos);
	float	angle =  atan2(diff.y, diff.x) - game->player.loc.angle;

	if (angle < -M_PI)
		angle += 2 * M_PI;
	printf("diff.x; %.2f, diff.y: %.2f\n", diff.x, diff.y);
	printf("player angle; %.2f, diff_angle: %.2f\n", game->player.loc.angle, angle);
	// TODO: improve condition on angle overflow while operating with fov
	if (-(0.5 * game->player.fov) <= angle
		&& angle < (0.5 * game->player.fov))
	{
		printf("is inside fov\n");
		t_grid_entity wall = grid_ray_wall(&game->chart, \
			game->player.loc.pos, angle + game->player.loc.angle);
		float wall_dist = fabs(vec2f_dot_product(vec2f_unit_vector(angle + game->player.loc.angle), \
				vec2f_sub(wall.pos, game->player.loc.pos)));
		float bullet_dist = fabs(vec2f_dot_product(vec2f_unit_vector(angle + game->player.loc.angle), \
			diff));
		t_vec2f bullet = vec2f_scale(vec2f_unit_vector(angle + M_PI_2), bullet_dist);
		bullet.x *= -1;
		/* float bullet_y = vec2f_dot_product(diff, vec2f_unit_vector(game->player.loc.angle)); */
		/* float bullet_x = vec2f_dot_product(diff, vec2f_unit_vector(game->player.loc.angle + M_PI_2)); */
		printf("bullet_dist %.2f, bullet_dist_x %.2f, bullet_dist_y %.2f, diff_y %.2f\n", bullet_dist, bullet.x, bullet.y, diff.y);
		if (bullet_dist < wall_dist)
		{
			printf("is visible\n");
			int px_x = ((cosf(game->player.fov * 0.5f) * bullet.x / bullet.y) * (game->ctx.window.width * 0.6) + (0.5 * game->ctx.window.width));
			printf("px_x: %d\n", px_x);
			draw_circle_cs(game->ctx.canvas,
						   (t_vec2f){px_x, game->ctx.window.height * 0.5f}, (t_brush) {0xFFFFFFFF, 8.0 / bullet.y});
		}
	}
}

void	render(t_game *game)
{
	draw_background(game);
	draw_level(game);
	//draw_player(game);
	draw_entities(game);
	if (game->state.show_minimap)
		draw_mini_map(game, 64, (t_vec2f){10.0f, 10.0f});
}
