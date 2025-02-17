/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:31:35 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/17 20:31:31 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "infrastructure/config.h"
#include "infrastructure/parse/parse_file.h"
#include "utils/outut.h"

static int	is_invalid_args(int argc, char **argv);

int	config_init(int argc, char **argv, t_config_file *config)
{
	if (is_invalid_args(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parse_file(*argv, config) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	config_clean(t_config_file *config)
{
	// TODO: clean texture filenames
}

static int	is_invalid_args(int argc, char **argv)
{
	if (argc != MAX_ARG)
		return (output_ret("Error: invalid number of arguments", EXIT_FAILURE));
	(void)argv;
	//TODO: validade filename on arg[0] 
	return (EXIT_SUCCESS);
}

