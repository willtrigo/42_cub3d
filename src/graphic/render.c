/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:41:04 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/27 16:22:26 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic/render.h"
#include "core/game.h"
#include "utils/vec2.h"

#include "draw.h"

char	chart_entity(t_chart *chart, t_vec2i pos)
{
	return (chart->buffer[(pos.y * chart->dimen.x) + pos.x]);
}

int	render(t_game *game)
{
	draw_background(game);
	draw_level(game);
	//draw_player(game);
	draw_mini_map(game, 64, (t_vec2f){10.0f, 10.0f});
	return (EXIT_SUCCESS);
}
