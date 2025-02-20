/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:32:41 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/20 18:13:51 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/config/config.h"
#include <stdlib.h>

int	game_manage(int argc, char **argv)
{
	t_config_file 	config;

	if (!config_init(--argc, ++argv, &config))
		return (EXIT_FAILURE);
	if (!config_validation(&config))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
