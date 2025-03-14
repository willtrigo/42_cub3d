/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:19:26 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/28 13:16:33 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_assert.h"
#include "ft_ctype.h"
#include "ft_memlib.h"
#include "ft_string.h"
#include "get_next_line.h"
#include "infrastructure/config/config.h"
#include "infrastructure/config/parse/parse_internal.h"
#include "utils/ft_extensions.h"
#include "utils/output.h"
#include <stdbool.h>

bool	parse_colors(int fd, t_config_file *config)
{
	char	*ln;
	bool	is_clr_set[TOTAL_COLOR];

	ft_bzero(is_clr_set, sizeof(is_clr_set));
	while (!is_clr_set[COLOR_F] || !is_clr_set[COLOR_C])
	{
		ln = ft_chomp(get_next_line(fd));
		if (!ln)
			return (logerr_ret("invalid file format", false));
		if (ft_is_blank(ln))
		{
			free(ln);
			break ;
		}
		if (*ln == 'F' && !check_color(ln, &config->floor, is_clr_set))
			return (ft_free_retvalue(ln, false));
		else if (*ln == 'C' && \
			!check_color(ln, &config->ceil, is_clr_set + COLOR_C))
			return (ft_free_retvalue(ln, false));
		free(ln);
	}
	if (!is_clr_set[COLOR_F] || !is_clr_set[COLOR_C])
		return (logerr_ret("invalid set of color", false));
	return (true);
}

bool	check_color(char *ln, t_color *color, bool *is_clr_set)
{
	ft_assert((*ln == 'F' || *ln == 'C'), "Error: unexpected color line");
	if (*is_clr_set)
		return (logerr_ret("double set of color", false));
	if (!parse_color(ln, color, is_clr_set))
		return (logerr_ret("invalid color", false));
	return (true);
}

bool	parse_color(char *color_ln, t_color *color, bool *is_clr_set)
{
	char	**split_ln;

	*is_clr_set = false;
	color_ln++;
	while (ft_isspace(*color_ln))
		color_ln++;
	split_ln = ft_split(color_ln, ',');
	if (ft_strarr_len(split_ln) != COLOR_RGB_LEN)
		return (ft_free_arr_retvalue(split_ln, false));
	color->a = 255;
	if (!ft_atoi8_range(&color->r, split_ln[COLOR_R], RANGE_LOW, RANGE_HIGH))
		return (ft_free_arr_retvalue(split_ln, false));
	if (!ft_atoi8_range(&color->g, split_ln[COLOR_G], RANGE_LOW, RANGE_HIGH))
		return (ft_free_arr_retvalue(split_ln, false));
	if (!ft_atoi8_range(&color->b, split_ln[COLOR_B], RANGE_LOW, RANGE_HIGH))
		return (ft_free_arr_retvalue(split_ln, false));
	*is_clr_set = true;
	return (ft_free_arr_retvalue(split_ln, true));
}
