/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:38:33 by maurodri          #+#    #+#             */
/*   Updated: 2025/03/12 02:24:37 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_entity.h"
#include <math.h>

int	texture_get_color(
	const mlx_texture_t *txt, t_vec2f scale, t_vec2i pixel, t_vec2f margin)
{
	t_color	color;
	t_vec2i	txt_px;
	int		i;

	txt_px.x = (pixel.x - margin.x) * scale.x;
	txt_px.y = (pixel.y - margin.y) * scale.y;
	i = ((txt_px.y * txt->width) + txt_px.x) * 4;
	color.r = txt->pixels[i + 0];
	color.g = txt->pixels[i + 1];
	color.b = txt->pixels[i + 2];
	color.a = txt->pixels[i + 3];
	return (color.value);
}

static t_vec2i	get_top_bottom(
	const t_context *ctx, float wall_height_screen)
{
	t_vec2i		top_bottom;

	top_bottom = (t_vec2i){\
		(ctx->window.height / 2) - ((int)(wall_height_screen / 2)),
		(ctx->window.height / 2) + ((int)(wall_height_screen / 2))};
	top_bottom = (t_vec2i){\
		fmax(0, top_bottom.x),
		fmin(ctx->window.height, top_bottom.y)};
	return (top_bottom);
}

static t_vec2f	get_margin(
	const t_game *game, const t_grid_entity *entity, float wall_height_screen)
{
	t_vec2f		margin;

	margin = (t_vec2f){\
		0,
		(game->ctx.window.height / 2.0f) - ((wall_height_screen / 2.0f))};
	if (entity->direction == NORTH)
		margin.x = entity->pos.x - floor(entity->pos.x);
	else if (entity->direction == EAST)
		margin.x = entity->pos.y - floor(entity->pos.y);
	else if (entity->direction == SOUTH)
		margin.x = 1 - (entity->pos.x - floor(entity->pos.x));
	else if (entity->direction == WEST)
		margin.x = 1 - (entity->pos.y - floor(entity->pos.y));
	return (margin);
}

void	draw_entity_col(
	t_game *game, t_grid_entity *entity, int pixel_x, float wall_height_screen)
{
	const mlx_texture_t	*txt = grid_entity_texture(&game->ctx, entity);
	const t_vec2f		scale = (t_vec2f){\
		((float) txt->width),
		((float) txt->height) / wall_height_screen};
	const t_vec2i		top_bottom = (\
		get_top_bottom(&game->ctx, wall_height_screen));
	const t_vec2f		margin = \
		get_margin(game, entity, wall_height_screen);
	t_vec2i				pixel;

	pixel.x = 0;
	pixel.y = top_bottom.x - 1;
	while (++pixel.y < top_bottom.y)
		mlx_put_pixel(game->ctx.canvas, pixel_x, pixel.y, \
			texture_get_color(txt, scale, pixel, margin));
}
