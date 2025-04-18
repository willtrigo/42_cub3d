/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:41:04 by dande-je          #+#    #+#             */
/*   Updated: 2025/04/18 00:32:43 by maurodri         ###   ########.fr       */
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

	if (pos.x < 0 || pos.x >= chart->dimen.x ||
		pos.y < 0 || pos.y >= chart->dimen.y)
		return '1';

	return (chart->buffer[(posi.y * chart->dimen.x) + posi.x]);
}

void	render(t_game *game)
{
	draw_background(game);
	draw_level(game);
	//draw_player(game);
	draw_entities(game);
	if (game->state.show_minimap)
		draw_mini_map(game, 64, (t_vec2f){10.0f, 10.0f});
}
