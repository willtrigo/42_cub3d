/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 08:32:06 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/28 13:16:27 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include "ft_memlib.h"
#include "ft_string.h"
#include "get_next_line.h"
#include "infrastructure/config/config.h"
#include "infrastructure/config/parse/parse_internal.h"
#include "utils/ft_extensions.h"
#include "utils/output.h"

bool	parse_textures(int fd, t_config_file *config)
{
	char	*ln;
	bool	is_tex_set[TOTAL_TEXTURE];

	ft_bzero(is_tex_set, sizeof(is_tex_set));
	while (!is_tex_set[TEXTURE_NO] || !is_tex_set[TEXTURE_EA] \
		|| !is_tex_set[TEXTURE_SO] || !is_tex_set[TEXTURE_WE])
	{
		ln = ft_chomp(get_next_line(fd));
		if (!ln)
			return (logerr_ret("invalid file format", false));
		if (ft_is_blank(ln))
		{
			free(ln);
			break ;
		}
		if (!check_texture(ln, config, is_tex_set))
			return (ft_free_retvalue(ln, false));
		free(ln);
	}
	if (!is_tex_set[TEXTURE_NO] || !is_tex_set[TEXTURE_EA] \
		|| !is_tex_set[TEXTURE_SO] || !is_tex_set[TEXTURE_WE])
		return (logerr_ret("invalid set of texture", false));
	return (true);
}

bool	check_texture(char *tex_ln, t_config_file *config, bool *is_tex_set)
{
	if (ft_strncmp(tex_ln, "NO", TEX_LEN) == TEX_ASSERT)
		return (set_texture(tex_ln, &config->texture_north, \
			is_tex_set + TEXTURE_NO));
	else if (ft_strncmp(tex_ln, "EA", TEX_LEN) == TEX_ASSERT)
		return (set_texture(tex_ln, &config->texture_east, \
			is_tex_set + TEXTURE_EA));
	else if (ft_strncmp(tex_ln, "SO", TEX_LEN) == TEX_ASSERT)
		return (set_texture(tex_ln, &config->texture_south, \
			is_tex_set + TEXTURE_SO));
	else if (ft_strncmp(tex_ln, "WE", TEX_LEN) == TEX_ASSERT)
		return (set_texture(tex_ln, &config->texture_west, \
			is_tex_set + TEXTURE_WE));
	return (logerr_ret("invalid direction", false));
}

bool	set_texture(char *tex_ln, char **texture, bool *is_tex_set)
{
	if (*is_tex_set)
		return (logerr_ret("double set of texture", false));
	tex_ln++;
	tex_ln++;
	while (ft_isspace(*tex_ln))
		tex_ln++;
	if (!*tex_ln)
		return (logerr_ret("invalid set of texture", false));
	*texture = ft_strdup(tex_ln);
	*is_tex_set = true;
	return (true);
}
