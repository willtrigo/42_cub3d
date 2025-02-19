/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:34:24 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/19 18:08:01 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/config/config.h"
#include "get_next_line.h"
#include "infrastructure/config/parse/parse_internal.h"
#include "utils/ft_extensions.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

bool	parse_file(char *filename, t_config_file *config)
{
	int	fd;

	fd = open(filename, O_RDONLY, CHMOD_PERMISSION);
	if (fd == FD_FAIL)
		return (false);
	if (!parse_textures(fd, config))
		return (clean_parse(config, fd, false));
	if (parse_colors(fd, config) == EXIT_FAILURE)
		return (clean_parse(config, fd, false));
	// TODO: parse_map;
	return (close_fd_ret(fd, true));
}

bool	parse_textures(int file_fd, t_config_file *config)
{
	char	*line;
	(void) config; // TODO parse textures

	while (1)
	{
		line = get_next_line(file_fd);
		if (line == 0)
			return (false);
		if (ft_is_blank(line))
		{
			// TODO: ? support multiple blank lines
			free(line);
			break ;
		}
		free(line);
	}
	return (true);
}

int	clean_parse(t_config_file *config, int file_fd, int ret)
{
	config_clean(config);
	return (close_fd_ret(file_fd, ret));
}

int	close_fd_ret(int file_fd, int ret)
{
	close(file_fd);
	return (ret);
}
