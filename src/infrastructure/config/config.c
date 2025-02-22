/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:31:35 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/22 12:32:32 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/config/config.h"
#include "ft_memlib.h"
#include "infrastructure/config/args/invalid_args.h"
#include "infrastructure/config/parse/parse_file.h"
#include "infrastructure/config/validation/invalid_config.h"
#include <stdbool.h>

bool	config_init(int argc, char **argv, t_config_file *config)
{
	ft_bzero(config, sizeof(t_config_file));
	if (!is_invalid_args(argc, *argv))
		return (false);
	if (!parse_file(*argv, config))
		return (false);
	return (true);
}

bool	config_validation(t_config_file *config)
{
	if (!is_invalid_config(config))
		return (false);
	return (true);
}

void	config_clean(t_config_file *config)
{
	if (config->texture_north)
		free(config->texture_north);
	if (config->texture_east)
		free(config->texture_east);
	if (config->texture_south)
		free(config->texture_south);
	if (config->texture_west)
		free(config->texture_west);
	if (config->map)
		ft_arraylist_destroy(config->map);
}
