/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 00:52:38 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/13 20:33:59 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void	camera_init(t_game *game, t_camera *out, int num_rays)
{
	const float	angle = game->player.loc.angle;
	const float	fov1_2 = game->player.fov / 2.0f;

	out->num_rays = num_rays;
	out->caml = vec2f_add(vec2f_unit_vector(angle - fov1_2), \
		game->player.loc.pos);
	out->camr = vec2f_add(vec2f_unit_vector(angle + fov1_2), \
		game->player.loc.pos);
	out->camv = vec2f_sub(out->camr, out->caml);
	out->camv_step = vec2f_scale(out->camv, 1.0f / out->num_rays);
}
