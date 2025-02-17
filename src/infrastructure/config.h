/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:31:44 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/17 18:38:49 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "utils/color.h"

typedef struct s_config_file
{
	// TODO: include textures fields
	t_color	ceil;
	t_color	floor;

	// TODO: ? map
} t_config_file;

int	  config_init(int argc, char **argv, t_config_file *config);
void	config_clean(t_config_file *config);

#endif
