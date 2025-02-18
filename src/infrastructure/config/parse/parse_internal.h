/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:19:52 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/18 18:52:25 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_INTERNAL_H
# define PARSE_INTERNAL_H

# include "infrastructure/config/config.h"
# include <stdbool.h>

int	  parse_color(char *color_line, t_color *color, bool *has_set_color);
int	  parse_colors(int file_fd, t_config_file *config);
int	  parse_textures(int file_fd, t_config_file *config);
int	  clean_parse(t_config_file *config, int file_fd, int ret);
int	  close_fd_ret(int file_fd, int ret);
bool	check_color(char *line, t_color *color, bool *has_set_color);

#endif
