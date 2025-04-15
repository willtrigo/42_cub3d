/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 08:32:06 by dande-je          #+#    #+#             */
/*   Updated: 2025/04/15 13:04:46 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include "ft_string.h"
#include "infrastructure/config/config.h"
#include "infrastructure/config/parse/parse_internal.h"
#include "utils/output.h"

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
