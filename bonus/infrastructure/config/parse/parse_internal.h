/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:19:52 by dande-je          #+#    #+#             */
/*   Updated: 2025/04/16 11:55:08 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_INTERNAL_H
# define PARSE_INTERNAL_H

# include "infrastructure/config/config.h"
# include <stdbool.h>

enum e_parse_file
{
	CHMOD_PERMISSION = 0666,
	FD_FAIL = -1,
};

enum e_parse_texture
{
	TEXTURE_NO,
	TEXTURE_EA,
	TEXTURE_SO,
	TEXTURE_WE,
	TOTAL_TEXTURE,
	TEX_LEN = 2,
	TEX_ASSERT = 0
};

enum e_parse_color
{
	COLOR_F,
	COLOR_C,
	TOTAL_COLOR,
	COLOR_R = 0,
	COLOR_G,
	COLOR_B,
	COLOR_RGB_LEN,
	RANGE_LOW = 0,
	RANGE_HIGH = 255,
};

bool	parse_textures_colors(int fd, t_config_file *config);
bool	parse_map(int fd, t_config_file *config);
bool	close_fd_ret(int fd, int ret);
bool	clean_parse(t_config_file *config, int fd, int ret);
bool	is_set_textures_colors(bool *is_tex_set, bool *is_clr_set);
bool	is_empty_line(char *ln);
bool	check_color(char *line, t_color *color, bool *is_clr_set);
bool	check_texture(char *tex_ln, t_config_file *config, bool *is_tex_set);
bool	parse_color(char *color_line, t_color *color, bool *is_clr_set);
bool	set_texture(char *tex_ln, char **texture, bool *is_tex_set);
bool	check_ln_map(char *ln);

#endif
