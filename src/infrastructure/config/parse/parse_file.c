/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:34:24 by dande-je          #+#    #+#             */
/*   Updated: 2025/04/15 13:04:28 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "infrastructure/config/config.h"
#include "infrastructure/config/parse/parse_internal.h"
#include "get_next_line.h"
#include "utils/ft_extensions.h"
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
		return (logerr_ret("could not read config file", false));
	if (!parse_textures_colors(fd, config))
		return (clean_parse(config, fd, false));
	if (!jump_empty_line(fd))
		return (clean_parse(config, fd, false));
	if (!parse_map(fd, config))
		return (clean_parse(config, fd, false));
	return (close_fd_ret(fd, true));
}

bool	jump_empty_line(int fd)
{
	char	*ln;

	ln = ft_chomp(get_next_line(fd));
	if (!ln)
		return (logerr_ret("invalid file format", false));
	if (!ft_is_blank(ln))
	{
		free(ln);
		return (logerr_ret("invalid file format", false));
	}
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
