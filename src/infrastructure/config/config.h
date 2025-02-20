/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:31:44 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/20 11:49:59 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "utils/color.h"
# include <stdbool.h>
# include "collection/ft_arraylist.h"

enum e_config
{
	MAX_ARG = 1,
	BUF_SIZE = 1,
	CHMOD_PERMISSION = 0666,
	FD_FAIL = -1,
};

typedef struct s_config_file
{
	char		*texture_north;
	char		*texture_east;
	char		*texture_south;
	char		*texture_west;
	t_color		ceil;
	t_color		floor;
	t_arraylist	map;
}	t_config_file;

bool	config_init(int argc, char **argv, t_config_file *config);
void	config_clean(t_config_file *config);

#endif
