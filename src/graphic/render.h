/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:41:13 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/24 16:26:29 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "MLX42/MLX42.h"
# include "core/game.h"
# include "utils/color.h"

int		render(t_game *game);
void	set_pixel(int x, int y, mlx_image_t *img, t_color *color);

#endif
