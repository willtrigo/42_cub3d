/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_colision_walls_internal.h                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:57:49 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/25 17:03:13 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSTEM_COLISION_WALLS_INTERNAL_H
# define SYSTEM_COLISION_WALLS_INTERNAL_H

# include "core/game.h"

void	system_colision_walls_h(\
	t_manager *manager, t_location *intention, float p_half_size);
void	system_colision_walls_v(\
	t_manager *manager, t_location *intention, float p_half_size);
void	system_colision_walls_diag(\
	t_manager *manager, t_location *intention, float p_half_size);

#endif
