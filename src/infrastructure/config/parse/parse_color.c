/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:19:26 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/19 18:17:08 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_assert.h"
#include "ft_ctype.h"
#include "ft_string.h"
#include "get_next_line.h"
#include "infrastructure/config/config.h"
#include "infrastructure/config/parse/parse_internal.h"
#include "utils/ft_extensions.h"
#include "utils/output.h"
#include <stdbool.h>

bool	parse_colors(int file_fd, t_config_file *config)
{
	char	*ln;
	bool	is_clr_set[2];

	is_clr_set[0] = false;
	is_clr_set[1] = false;
	while (!is_clr_set[0] || !is_clr_set[1])
	{
		ln = ft_chomp(get_next_line(file_fd));
		if (ln == 0)
			return (false);
		if (ft_is_blank(ln))
		{
			free(ln);
			break ;
		}
		if (*ln == 'F' && !check_color(ln, &config->floor, is_clr_set))
			return (false);
		else if (*ln == 'C' && \
			!check_color(ln, &config->ceil, is_clr_set + 1))
			return (false);
		free(ln);
	}
	if (!is_clr_set[0] || !is_clr_set[1])
		return (false);
	return (true);
}

bool	check_color(char *ln, t_color *color, bool *is_clr_set)
{
	ft_assert((*ln == 'F' || *ln == 'C'), "Error: unexpected color line");
	if (*is_clr_set)
		return (output_ret("Error: double set of color", true));
	return (parse_color(ln, color, is_clr_set));
}

bool	parse_color(char *color_ln, t_color *color, bool *is_clr_set)
{
	char	**split_ln;

	*is_clr_set = false;
	// andar
	color_ln++;
		// assuming ln does not contain \n
	while (ft_isspace(*color_ln))
		color_ln++;
	// split
	split_ln = ft_split(color_ln, ',');
	if (ft_strarr_len(split_ln) != 3)
		return (ft_free_arr_retvalue(split_ln, false));
	// parseInt
	color->a = 255;
	if (!ft_atoi8_range(&color->r, split_ln[0], 0, 255))
		return (ft_free_arr_retvalue(split_ln, false));
	if (!ft_atoi8_range(&color->g, split_ln[1], 0, 255))
		return (ft_free_arr_retvalue(split_ln, false));
	if (!ft_atoi8_range(&color->b, split_ln[2], 0, 255))
		return (ft_free_arr_retvalue(split_ln, false));
	// set color && is_clr_set
	*is_clr_set = true;
	return (ft_free_arr_retvalue(split_ln, true));
}
