/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:31:44 by dande-je          #+#    #+#             */
/*   Updated: 2025/04/18 20:42:09 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "utils/color.h"
# include <stdbool.h>
# include "collection/ft_arraylist.h"

typedef struct s_config_file
{
	char		*texture_north;
	char		*texture_east;
	char		*texture_south;
	char		*texture_west;
	t_color		ceil;
	t_color		floor;
	t_arraylist	map;
	int			map_width;
}	t_config_file;

bool	config_init(int argc, char **argv, t_config_file *config);
bool	config_validation(t_config_file *config);
void	config_clean(t_config_file *config);

#endif
