/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_primitive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:51:18 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/18 01:25:10 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_primitive.h"
#include <math.h>

void	draw_circle_cs( \
	mlx_image_t *canvas, t_vec2f center, t_brush brush)
{
	const t_vec2f	top_left_square = vec2f_offset(center, -brush.size);
	const t_vec2f	bottom_right_square = vec2f_offset(center, brush.size);
	const float		r2 = brush.size * brush.size;
	t_vec2i			i;
	float			sum_squares;

	i.y = top_left_square.y - 1;
	while (++i.y < bottom_right_square.y)
	{
		i.x = top_left_square.x - 1;
		while (++i.x < bottom_right_square.x)
		{
			if (i.x < 0.0f || i.y < 0.0f \
				|| (uint32_t)i.x >= canvas->width
				|| (uint32_t)i.y >= canvas->height)
				continue ;
			(void)"(x - a)^2 + (y - b)^2 < r^2";
			sum_squares = ((i.x - center.x) * (i.x - center.x)) \
						+ ((i.y - center.y) * (i.y - center.y));
			if (sum_squares < r2)
				mlx_put_pixel(canvas, i.x, i.y, brush.color.value);
		}
	}
}

void	draw_square_cs( \
	mlx_image_t *canvas, t_vec2f center, t_brush brush)
{
	const t_vec2f	top_left = (t_vec2f){\
		center.x - (brush.size / 2.0f), \
		center.y - (brush.size / 2.0f)
	};
	const t_vec2f	bottom_right = (t_vec2f){\
		center.x + (brush.size / 2.0f), \
		center.y + (brush.size / 2.0f)
	};
	t_vec2f			i;

	i.y = top_left.y - 1;
	while (++i.y < bottom_right.y)
	{
		i.x = top_left.x - 1;
		while (++i.x < bottom_right.x)
		{
			if (i.x >= 0.0f && i.y >= 0.0f)
				mlx_put_pixel(canvas, i.x, i.y, brush.color.value);
		}
	}
}

void	draw_line_cs( \
	mlx_image_t *canvas, t_vec2f center, t_vec2f size_angle, t_brush brush)
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
		draw_square_cs(canvas, i, brush);
		i = (t_vec2f){i.x + cosf(size_angle.y), i.y + sinf(size_angle.y)};
	}
}

void	draw_line_p( \
	mlx_image_t *canvas, t_vec2f pa, t_vec2f pb, t_brush brush)
{
	const t_vec2f	delta = vec2f_to_unit(vec2f_sub(pb, pa));
	t_vec2f			i;

	i = pa;
	while (1)
	{
		draw_square_cs(canvas, i, brush);
		i = (t_vec2f){i.x + delta.x, i.y + delta.y};
		if ((delta.x > 0 && i.x > pb.x) || (delta.x < 0 && i.x < pb.x))
			break ;
		if ((delta.y > 0 && i.y > pb.y) || (delta.y < 0 && i.y < pb.y))
			break ;
	}
}
