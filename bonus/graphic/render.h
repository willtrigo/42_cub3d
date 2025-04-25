/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:41:13 by dande-je          #+#    #+#             */
/*   Updated: 2025/03/12 02:24:16 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "core/game.h"

void	render(t_game *game);
char	chart_entity(const t_chart *chart, t_vec2f pos);
int		texture_get_color(\
	const mlx_texture_t *txt, t_vec2f scale, t_vec2i pixel, t_vec2f margin);

#endif
