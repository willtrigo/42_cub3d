/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_config.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:30:18 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/22 12:31:41 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVALID_CONFIG_H
# define INVALID_CONFIG_H

# include "infrastructure/config/config.h"
# include <stdbool.h>

bool	is_invalid_config(t_config_file *config);

#endif
