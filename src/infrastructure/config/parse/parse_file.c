/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:34:24 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/18 18:15:33 by dande-je         ###   ########.fr       */
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

int	parse_file(char *filename, t_config_file *config)
{
	int	fd;

	fd = open(filename, O_RDONLY, CHMOD_PERMISSION);
	if (fd == FD_FAIL)
		return (close_fd_ret(fd, EXIT_FAILURE));
	if (parse_textures(fd, config) == EXIT_FAILURE)
		return (clean_parse(config, fd, EXIT_FAILURE));
	if (parse_colors(fd, config) == EXIT_FAILURE)
		return (clean_parse(config, fd, EXIT_FAILURE));
	// TODO: parse_map;
	return (close_fd_ret(fd, EXIT_SUCCESS));
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
