/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:32:28 by dande-je          #+#    #+#             */
/*   Updated: 2025/04/15 13:02:51 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memlib.h"
#include "ft_string.h"
#include "get_next_line.h"
#include "infrastructure/config/config.h"
#include "infrastructure/config/parse/parse_internal.h"
#include "utils/ft_extensions.h"
#include "utils/output.h"
#include <stdbool.h>

bool	parse_textures_colors(int fd, t_config_file *config)
{
	char	*ln;
	bool	is_tex_set[TOTAL_TEXTURE];
	bool	is_clr_set[TOTAL_COLOR];

	ft_bzero(is_tex_set, sizeof(is_tex_set));
	ft_bzero(is_clr_set, sizeof(is_clr_set));
	while (!is_set_textures_colors(is_tex_set, is_clr_set))
	{
		ln = ft_chomp(get_next_line(fd));
		if (!ln)
			return (logerr_ret("invalid file format", false));
		if (is_empty_line(ln))
			continue ;
		if (*ln == 'F' && !check_color(ln, &config->floor, is_clr_set))
			return (ft_free_retvalue(ln, false));
		else if (*ln == 'C' && !check_color(ln, &config->ceil, is_clr_set))
			return (ft_free_retvalue(ln, false));
		else if (!(*ln == 'F' || *ln == 'C') \
			&& !check_texture(ln, config, is_tex_set))
			return (ft_free_retvalue(ln, false));
		free(ln);
	}
	if (!is_set_textures_colors(is_tex_set, is_clr_set))
		return (logerr_ret("invalid set of texture", false));
	return (true);
}

bool	is_set_textures_colors(bool *is_tex_set, bool *is_clr_set)
{
	if (is_tex_set[TEXTURE_NO] && is_tex_set[TEXTURE_EA] \
		&& is_tex_set[TEXTURE_SO] && is_tex_set[TEXTURE_WE] \
		&& is_clr_set[COLOR_F] && is_clr_set[COLOR_C])
		return (true);
	return (false);
}

bool	is_empty_line(char *ln)
{
	if (ft_is_blank(ln))
	{
		free(ln);
		return (true);
	}
	return (false);
}
