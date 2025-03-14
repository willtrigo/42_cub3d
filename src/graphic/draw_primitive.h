/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_primitive.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:51:47 by maurodri          #+#    #+#             */
/*   Updated: 2025/03/11 21:53:28 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_PRIMITIVE_H
# define DRAW_PRIMITIVE_H

# include "MLX42/MLX42.h"
# include "utils/color.h"
# include "utils/vec2.h"

void	draw_circle_cs( \
	mlx_image_t *canvas, t_vec2f center, float radius, t_color color);
void	draw_square_cs( \
	mlx_image_t *canvas, t_vec2f center, int size, t_color color);
void	draw_line_cs( \
	mlx_image_t *canvas, t_vec2f center, t_vec2f size_angle, t_color color);
void	draw_line_p( \
	mlx_image_t *canvas, t_vec2f pa, t_vec2f pb, t_color color);

#endif
