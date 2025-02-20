/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 08:32:06 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/20 13:24:06 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/config/config.h"
#include "get_next_line.h"
#include "utils/ft_extensions.h"

bool	parse_textures(int fd, t_config_file *config)
{
	char	*ln;

	(void) config; // TODO parse textures
	while (1)
	{
		ln = get_next_line(fd);
		if (ln == 0)
			return (false);
		if (ft_is_blank(ln))
		{
			// TODO: ? support multiple blank lns
			free(ln);
			break ;
		}
		free(ln);
	}
	return (true);
}
