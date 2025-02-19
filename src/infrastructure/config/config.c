/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:31:35 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/19 17:40:10 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "infrastructure/config/config.h"
#include "infrastructure/config/config_internal.h"
#include "ft_string.h"
#include "infrastructure/config/parse/parse_file.h"
#include "utils/output.h"


bool	config_init(int argc, char **argv, t_config_file *config)
{
	if (!is_invalid_args(argc, *argv))
		return (false);
	if (!parse_file(*argv, config))
		return (false);
	return (true);
}

void	config_clean(t_config_file *config)
{
	(void) config;
	// TODO: clean texture filenames
}

bool	is_invalid_args(int argc, char *filename)
{
	if (argc != MAX_ARG)
		return (output_ret("Error: invalid number of arguments", false));
	if (!is_invalid_extension(filename, ft_strlen(filename)))
		return (output_ret("Error: invalid extension must be .cub", false));
	// if (!is_invalid_file(filename))
	// 	return (output_ret("Error: invalid file", EXIT_FAILURE));
	return (true);
}

bool	is_invalid_extension(char *filename, size_t filename_len)
{
	const char	*ext = ".cub";
	size_t		ext_len = ft_strlen(ext);

	if (filename_len < ext_len)
		return (false);
	if (ft_strncmp(&filename[filename_len - ext_len], ext, ext_len))
		return (false);
	return (true);
}

bool	is_invalid_file(char *filename)
{
	int32_t	fd;
	int32_t	file;
	char	buf[BUF_SIZE];
	bool	ret;

	ret = true;
	fd = open(filename, O_RDONLY, CHMOD_PERMISSION);
	if (fd <= FD_FAIL)
		ret = false;
	file = read(fd, buf, BUF_SIZE);
	close(fd);
	if (ret && 
		(!file || !(*buf == 'N' || *buf == 'S' || *buf == 'W' || *buf == 'E')))
		ret = false;
	return (ret);
}
