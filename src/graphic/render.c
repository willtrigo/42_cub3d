/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:41:04 by dande-je          #+#    #+#             */
/*   Updated: 2025/03/09 01:39:18 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic/render.h"
#include "core/game.h"
#include "utils/vec2.h"

#include "draw.h"
#include "draw_mini.h"

char	chart_entity(const t_chart *chart, t_vec2f pos)
{
	const t_vec2i	posi = {pos.x, pos.y};

	return (chart->buffer[(posi.y * chart->dimen.x) + posi.x]);
}

void	render(t_game *game)
{
	draw_background(game);
	draw_level3(game);
	//draw_player(game);
	draw_mini_map(game, 64, (t_vec2f){10.0f, 10.0f});
}
