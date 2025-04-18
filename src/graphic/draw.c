/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:13:44 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/14 00:40:49 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "core/game.h"
#include "graphic/camera.h"
#include "graphic/draw_entity.h"
#include "graphic/draw_mini.h"
#include "utils/color.h"
#include "utils/vec2.h"
#include <math.h>
#include <stdio.h>
#include <sys/types.h>
#include "draw.h"
#include "render.h"
#include "ft_assert.h"
#include "grid.h"

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

void	draw_level_col(t_game *game, float ray_angle, int pixel_x)
{
	t_vec2f			diff;
	t_grid_entity	entity;
	float			distance;
	float			wall_height_screen;

	entity = grid_ray_wall(&game->chart, game->player.loc.pos, ray_angle);
	if (entity.type == '1')
	{
		diff = vec2f_sub(entity.pos, game->player.loc.pos);
		distance = fabs(vec2f_dot_product(\
			vec2f_unit_vector(game->player.loc.angle), diff));
		wall_height_screen = (game->ctx.window.height * 0.60f) / distance;
		draw_entity_col(game, &entity, pixel_x, wall_height_screen);
	}
}

void	draw_level(t_game *game)
{
	t_camera	c;
	int			i;
	t_vec2f		player_to_camv_step;
	float		angle;

	camera_init(game, &c, game->ctx.window.width - 1);
	i = -1;
	while (++i <= c.num_rays)
	{
		player_to_camv_step = vec2f_sub(\
				vec2f_add(c.caml, vec2f_scale(c.camv_step, i)), \
				game->player.loc.pos);
		angle = atan2(player_to_camv_step.y, player_to_camv_step.x);
		draw_level_col(game, angle, i);
	}
}
