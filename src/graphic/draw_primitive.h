/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_primitive.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:51:47 by maurodri          #+#    #+#             */
/*   Updated: 2025/03/14 20:15:27 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_PRIMITIVE_H
# define DRAW_PRIMITIVE_H

# include "MLX42/MLX42.h"
# include "utils/color.h"
# include "utils/vec2.h"

typedef struct s_brush
{
	t_color color;
	int		size;
}	t_brush;

void	draw_circle_cs( \
	mlx_image_t *canvas, t_vec2f center, t_brush brush);
void	draw_square_cs( \
	mlx_image_t *canvas, t_vec2f center, t_brush brush);
void	draw_line_cs( \
	mlx_image_t *canvas, t_vec2f center, t_vec2f size_angle, t_brush brush);
void	draw_line_p( \
	mlx_image_t *canvas, t_vec2f pa, t_vec2f pb, t_brush brush);

#endif
