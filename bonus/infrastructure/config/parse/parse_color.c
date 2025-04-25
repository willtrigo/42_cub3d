/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:19:26 by dande-je          #+#    #+#             */
/*   Updated: 2025/04/15 13:04:18 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_assert.h"
#include "ft_ctype.h"
#include "ft_string.h"
#include "infrastructure/config/parse/parse_internal.h"
#include "utils/ft_extensions.h"
#include "utils/output.h"
#include <stdbool.h>

bool	check_color(char *ln, t_color *color, bool *is_clr_set)
{
	ft_assert((*ln == 'F' || *ln == 'C'), "Error: unexpected color line");
	if (*ln == 'C')
		is_clr_set += COLOR_C;
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
