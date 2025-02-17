/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:19:26 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/17 19:22:21 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include "ft_string.h"
#include "get_next_line.h"
#include "infrastructure/parse/parse_internal.h"
#include "utils/ft_extensions.h"

int	parse_colors(int file_fd, t_config_file *config)
{
	char	*line;
	bool	has_set_color[2];

	has_set_color[0] = false;
	has_set_color[1] = false;
	while (!has_set_color[0] || !has_set_color[1])
	{
		line = ft_chomp(get_next_line(file_fd));
		if (line == 0)
			return (EXIT_FAILURE);
		if (ft_is_blank(line))
		{
			free(line);
			break ;
		}
		if (*line == 'F' && parse_color(line, &config->floor, has_set_color))
			return (EXIT_FAILURE);
		else if (*line == 'C' && parse_color(line, &config->ceil, has_set_color + 1))
			return (EXIT_FAILURE);
		free(line);
	}
	if (!has_set_color[0] || !has_set_color[1])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse_color(char *color_line, t_color *color, bool *has_set_color)
{
	char	**split_line;

	*has_set_color = false;
	// andar
	color_line++;
		// assuming line does not contain \n
	while (ft_isspace(*color_line))
		color_line++;
	// split
	split_line = ft_split(color_line, ',');
	if (ft_strarr_len(split_line) != 3)
		return (ft_free_arr_retvalue(split_line, EXIT_FAILURE));
	// parseInt
	color->a = 255;
	if (!ft_atoi8_range(&color->r, split_line[0], 0, 255))
		return (ft_free_arr_retvalue(split_line, EXIT_FAILURE));
	if (!ft_atoi8_range(&color->g, split_line[1], 0, 255))
		return (ft_free_arr_retvalue(split_line, EXIT_FAILURE));
	if (!ft_atoi8_range(&color->b, split_line[2], 0, 255))
		return (ft_free_arr_retvalue(split_line, EXIT_FAILURE));
	// set color && has_set_color
	*has_set_color = true;
	return (ft_free_arr_retvalue(split_line, EXIT_SUCCESS));
}
