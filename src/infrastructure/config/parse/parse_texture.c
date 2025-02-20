/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 08:32:06 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/20 08:33:40 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/config/config.h"
#include "get_next_line.h"
#include "utils/ft_extensions.h"

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
