/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:00:10 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/28 13:17:56 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/config/args/invalid_args.h"
#include "infrastructure/config/args/invalid_args_internal.h"
#include "ft_string.h"
#include "utils/output.h"
#include <stdbool.h>

bool	is_invalid_args(int argc, char *filename)
{
	if (argc != MAX_ARG)
		return (logerr_ret("invalid number of arguments", false));
	if (!is_invalid_extension(filename, ft_strlen(filename)))
		return (logerr_ret("extension must be .cub", false));
	return (true);
}
