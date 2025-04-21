/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:05:16 by dande-je          #+#    #+#             */
/*   Updated: 2025/04/19 16:53:44 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collection/ft_arraylist.h"
#include "ft_memlib.h"
#include "ft_string.h"
#include "ft_util.h"
#include "get_next_line.h"
#include "infrastructure/config/config.h"
#include "infrastructure/config/parse/parse_internal.h"
#include "utils/ft_extensions.h"
#include "utils/output.h"
#include <stdbool.h>
#include <stddef.h>

static void	check_map_witdh(t_config_file *config, char *ln);
static void	normalize_map(t_config_file *config, size_t map_height);

bool	parse_map(int fd, t_config_file *config)
{
	char	*ln;

	ln = ft_chomp(get_next_line(fd));
	if (!ln)
		return (logerr_ret("invalid file format", false));
	while (ft_is_blank(ln))
	{
		free(ln);
		ln = ft_chomp(get_next_line(fd));
		if (!ln)
			return (logerr_ret("invalid file format", false));
	}
	config->map = ft_arraylist_new((t_consumer)free);
	while (ln)
	{
		check_map_witdh(config, ln);
		config->map = ft_arraylist_add(config->map, ln);
		ln = ft_chomp(get_next_line(fd));
		if (ln && !check_ln_map(ln))
			return (ft_free_retvalue(ln, false));
	}
	normalize_map(config, ft_arraylist_len(config->map));
	return (true);
}

static void	normalize_map(t_config_file *config, size_t map_height)
{
	size_t	i;
	char	*ln;
	size_t	ln_len;

	i = -1;
	ln_len = 0;
	while (++i < map_height)
	{
		ln = ft_calloc(config->map_width, sizeof(char));
		ln_len = ft_strlcpy(ln,
				(char *)ft_arraylist_get(config->map, i), config->map_width);
		while (ln_len < (size_t)(config->map_width - 1))
			ln[ln_len++] = ' ';
		ft_arraylist_replace(config->map, ln, i);
	}
}

static void	check_map_witdh(t_config_file *config, char *ln)
{
	const int	current_width = ft_strlen(ln) + 1;

	if (current_width >= config->map_width)
		config->map_width = current_width;
}

bool	check_ln_map(char *ln)
{
	if (ft_is_blank(ln))
		return (logerr_ret("invalid map format", false));
	return (true);
}
