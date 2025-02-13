/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:46:59 by maurodri          #+#    #+#             */
/*   Updated: 2025/02/13 16:52:01 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <stdbool.h>
# include "color.h"

int	cube_main(int argc, char **argv);
int	parse_color(char *color_line, t_color *color, bool *has_set_color);

#endif
