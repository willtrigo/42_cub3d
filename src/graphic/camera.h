/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 00:52:04 by maurodri          #+#    #+#             */
/*   Updated: 2025/03/09 00:53:43 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "core/game.h"
# include "utils/vec2.h"

typedef struct s_camera
{
	int		num_rays;
	float	fov1_2;
	t_vec2f	caml;
	t_vec2f	camr;
	t_vec2f	camv;
	t_vec2f	camv_step;
}	t_camera;

void	camera_init(t_game *game, t_camera *out, int num_rays);

#endif
