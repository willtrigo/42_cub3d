/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_grid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:15:52 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/19 21:16:47 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_mini.h"

void	draw_mini_grid(t_game *game, t_mini_args m)
{
	const t_color	color = (t_color){.value = 0x0000ffFF};
	const t_vec2f	grid_size = m.grid_pos;
	const t_vec2f	limit = vec2f_scalei(grid_size, m.block_size);
	t_vec2i			i;

	i.y = 1;
	while (++i.y < limit.y)
	{
		i.x = -1;
		while (++i.x < limit.x)
			if ((i.x) % m.block_size == 0
				|| i.y % m.block_size == 0)
				mlx_put_pixel(game->ctx.canvas, i.x + m.offset.x, \
					i.y + m.offset.y, color.value);
	}
}
