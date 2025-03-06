/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:54:33 by maurodri          #+#    #+#             */
/*   Updated: 2025/03/06 19:40:31 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grid.h"
#include "ft_assert.h"
#include "graphic/render.h"
#include <math.h>

t_grid_entity	grid_entity(\
	const t_chart *chart, const t_vec2f *grid_pos, const t_vec2f *unity)
{
	const t_vec2i	is_on_grid = (t_vec2i){\
		fmod(grid_pos->x, 1.0f) == 0, \
		fmod(grid_pos->y, 1.0f) == 0};
	const t_vec2i	off_i = (t_vec2i){\
		-(unity->x < 0 && is_on_grid.x), \
		-(unity->y < 0 && is_on_grid.y)};
	const char		ch_entity = chart_entity(\
		chart, vec2f_addi(*grid_pos, off_i));
	t_grid_entity	entity;

	entity = (t_grid_entity){ch_entity, CENTER};
	if (unity->y < 0 && is_on_grid.y)
		entity.direction = NORTH;
	else if (unity->x > 0 && is_on_grid.x)
		entity.direction = EAST;
	else if (unity->y > 0 && is_on_grid.y)
		entity.direction = SOUTH;
	else if (unity->x < 0 && is_on_grid.x)
		entity.direction = WEST;
	return (entity);
}

t_vec2f	grid_next_border(t_vec2f grid_pos, float angle, t_vec2f unity)
{
	t_vec2f	vert;
	t_vec2f	horiz;
	t_vec2f	mag;

	vert.y = ((int)(grid_pos.y + ((unity.y > 0) * 1 + (unity.y < 0 \
			&& fmod(grid_pos.y, 1.0f) == 0.f) * (-1)))) - grid_pos.y;
	vert.x = tanf(M_PI_2 - angle) * vert.y;
	horiz.x = ((int)(grid_pos.x + ((unity.x > 0) * 1 + (unity.x < 0 \
		&& fmod(grid_pos.x, 1.0f) == 0.f) * (-1)))) - grid_pos.x;
	horiz.y = -tanf(M_PI - angle) * horiz.x;
	mag = (t_vec2f){vec2f_magnitude2(horiz), vec2f_magnitude2(vert)};
	if ((mag.x > 0.000000000001f && mag.x < mag.y) || mag.y < 0.000000000001f)
		return (vec2f_add(grid_pos, horiz));
	else
		return (vec2f_add(grid_pos, vert));
}

t_vec2f	grid_pos_to_screen_pos(t_vec2f grid_pos, float block_size, t_vec2f offset)
{
	return (vec2f_add(vec2f_scale(grid_pos, block_size), offset));
}
