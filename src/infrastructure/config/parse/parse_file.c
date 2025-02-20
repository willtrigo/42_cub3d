/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:34:24 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/20 15:31:11 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "infrastructure/config/config.h"
#include "infrastructure/config/parse/parse_internal.h"
#include "get_next_line.h"
#include "utils/output.h"
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
	if (!jump_empty_line(fd))
		return (clean_parse(config, fd, false));
	if (!parse_colors(fd, config))
		return (clean_parse(config, fd, false));
	if (!jump_empty_line(fd))
		return (clean_parse(config, fd, false));
	// TODO: parse_map;
	return (close_fd_ret(fd, true));
}

bool	jump_empty_line(int fd)
{
	char	*ln;

	ln = ft_chomp(get_next_line(fd));
	if (!ln)
		return (output_ret("Error: invalid file format", false));
	free(ln);
	return (true);
}

bool	clean_parse(t_config_file *config, int fd, int ret)
{
	config_clean(config);
	return (close_fd_ret(fd, ret));
}

bool	close_fd_ret(int fd, int ret)
{
	char	*str;

	close(fd);
	str = get_next_line(fd);
	while (str != NULL)
	{
		(void) "forcing buffer reset on gnl";
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	return (ret);
}
