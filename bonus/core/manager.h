/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:54:54 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/19 21:00:39 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANAGER_H
# define MANAGER_H

# include "game.h"

void	manager_entities_move(t_manager *manager, t_game *game);
bool	entity_manager_spawn_bullet(\
	t_manager *manager, const t_location *initial, double time);
#endif
