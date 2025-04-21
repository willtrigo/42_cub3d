/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:38:58 by dande-je          #+#    #+#             */
/*   Updated: 2025/04/20 20:59:34 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "core/game.h"
# include "infrastructure/config/config.h"
# include <stdbool.h>

bool	map_validation(t_game *game, t_config_file *config, size_t map_height);

#endif
