/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:13:44 by maurodri          #+#    #+#             */
/*   Updated: 2025/03/09 01:39:20 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "core/game.h"
#include "graphic/camera.h"
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

void	draw_line_p( \
	mlx_image_t *canvas, t_vec2f pa, t_vec2f pb, t_color color)
{
	const t_vec2f	delta = vec2f_to_unit(vec2f_sub(pb, pa));
	t_vec2f			i;

	i = pa;
	while (1)
	{
		draw_square_cs(canvas, i, 4, color);
		i = (t_vec2f) {i.x + delta.x, i.y + delta.y};
		if ((delta.x > 0 && i.x > pb.x) || (delta.x < 0 && i.x < pb.x))
			break ;
		if ((delta.y > 0 && i.y > pb.y) || (delta.y < 0 && i.y < pb.y))
			break ;
	}
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
	const float			height = 256.0f;
	const float			width = 256.0f;
	const mlx_texture_t	*txt = game->ctx.txts.south;
	const t_vec2f		scale = (t_vec2f){((float) txt->height) / height, \
											((float) txt->width) / width};
	int					y;
	t_vec2i				margin_horizontal = (t_vec2i){0, width};
	t_vec2i				margin_vertical = (t_vec2i){\
		(game->ctx.window.height / 2.0f) - (height / 2), \
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

void	draw_level_col2(t_game *game, float ray_angle, int pixel_x)
{
	const t_vec2f	player_unity = vec2f_unit_vector(game->player.angle);
	t_vec2f			diff;
	t_grid_entity	entity;
	float			distance;
	float			wall_height_screen;
	int				pixel_y;
	t_vec2i			top_bottom;

	entity = grid_ray_wall(&game->chart, game->player.pos, ray_angle);
	if (entity.type == '1')
	{
		diff = vec2f_sub(entity.pos, game->player.pos);
		distance = fabs(vec2f_dot_product(player_unity, diff));
		wall_height_screen = (game->ctx.window.height * 0.5f) / pow(2, distance);
		top_bottom = (t_vec2i){(game->ctx.window.height / 2) - ((int)(wall_height_screen / 2)), (game->ctx.window.height / 2) + ((int)(wall_height_screen / 2))};
		pixel_y = top_bottom.x - 1;
		while (++pixel_y < top_bottom.y)
		{
			t_color color = (t_color){0x000000FF};
			color.r = (entity.direction == EAST) * 180;
			color.b = ((entity.direction == WEST) \
							|| (entity.direction == SOUTH)) * 180;
			color.g = (entity.direction == SOUTH) * 180;
			mlx_put_pixel(game->ctx.canvas, pixel_x, pixel_y, color.value);
		}
	}
}


void	draw_level_col3(t_game *game, float ray_angle, int pixel_x)
{
	const t_vec2f	player_unity = vec2f_unit_vector(game->player.angle);
	t_vec2f			diff;
	t_grid_entity	entity;
	float			distance;
	float			wall_height_screen;
	int				pixel_y;
	t_vec2i			top_bottom;

	entity = grid_ray_wall(&game->chart, game->player.pos, ray_angle);
	if (entity.type == '1')
	{
		diff = vec2f_sub(entity.pos, game->player.pos);
		distance = fabs(vec2f_dot_product(player_unity, diff)) * 2;
		wall_height_screen = (game->ctx.window.height * 0.7f) / distance;
		top_bottom = (t_vec2i) {(game->ctx.window.height / 2) - ((int) (wall_height_screen / 2)),
		    (game->ctx.window.height / 2) + ((int) (wall_height_screen / 2))};
		top_bottom = (t_vec2i) {fmax(0, top_bottom.x),
								fmin(game->ctx.window.height, top_bottom.y)};
		pixel_y = top_bottom.x - 1;
		while (++pixel_y < top_bottom.y)
		{
			t_color color = (t_color){0x000000FF};
			color.r = (entity.direction == EAST) * 180;
			color.b = ((entity.direction == WEST) \
							|| (entity.direction == SOUTH)) * 180;
			color.g = (entity.direction == SOUTH) * 180;
			mlx_put_pixel(game->ctx.canvas, pixel_x, pixel_y, color.value);
		}
	}
}


void	draw_level3(t_game *game)
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
				game->player.pos);
		angle = atan2(player_to_camv_step.y, player_to_camv_step.x);
		draw_level_col3(game, angle, i);
	}
}


void	draw_level2(t_game *game)
{
	const float	angle = game->player.angle;
	const float	fov1_2 = game->player.fov / 2.0f;
	const float	step = game->player.fov / game->ctx.window.width;
	float		ray_angle_offset;
	int			x_pixel;

	ray_angle_offset = -fov1_2;
	x_pixel = -1;
	while (++x_pixel < game->ctx.window.width)
	{
		draw_level_col2(game, ray_angle_offset + angle, x_pixel);
		ray_angle_offset += step;
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
