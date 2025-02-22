/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:32:41 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/22 11:39:14 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic/render.h"
#include "infrastructure/config/config.h"
#include <stdlib.h>

int	game_manage(int argc, char **argv)
{
	t_config_file	config;

	if (!config_init(--argc, ++argv, &config))
		return (EXIT_FAILURE);
	if (!config_validation(&config))
		return (EXIT_FAILURE);
	return (render_map(&config));
}
