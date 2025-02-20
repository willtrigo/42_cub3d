/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:05:16 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/20 17:44:55 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collection/ft_arraylist.h"
#include "ft_string.h"
#include "ft_util.h"
#include "get_next_line.h"
#include "infrastructure/config/config.h"
#include "infrastructure/config/parse/parse_internal.h"
#include "utils/ft_extensions.h"
#include "utils/output.h"
#include <stdbool.h>

bool	parse_map(int fd, t_config_file *config)
{
	char	*ln;

	config->map = ft_arraylist_new((t_consumer)free);
	ln = ft_chomp(get_next_line(fd));
	if (!ln)
		return (output_ret("Error: invalid file format", false));
	while (ln)
	{
		config->map = ft_arraylist_add(config->map, ln);
		ln = ft_chomp(get_next_line(fd));
		if (ln && !check_ln_map(ln))
			return (ft_free_retvalue(ln, false));
	}
	return (true);
}

bool	check_ln_map(char *ln)
{
	if (ft_is_blank(ln))
		return (output_ret("Error: invalid map format", false));
	return (true);
}
