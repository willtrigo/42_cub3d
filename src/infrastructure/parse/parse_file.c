/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:34:24 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/17 19:23:45 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/config.h"
#include "get_next_line.h"
#include "infrastructure/parse/parse_internal.h"
#include "utils/ft_extensions.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>

int	parse_file(char *filename, t_config_file *config)
{
	int	fd;

	fd = open(filename, O_RDONLY, 0666);
	if (fd < 0)
		return (EXIT_FAILURE);
	if (parse_textures(fd, config) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parse_colors(fd, config) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// TODO: parse_map;
	return (EXIT_SUCCESS);
}

int	parse_textures(int file_fd, t_config_file *config)
{
	char	*line;

	while (1)
	{
		line = get_next_line(file_fd);
		if (line == 0)
			return (EXIT_FAILURE);
		if (ft_is_blank(line))
		{
			// TODO: ? support multiple blank lines
			free(line);
			break ;
		}
		free(line);
	}
	return (EXIT_SUCCESS);
}
