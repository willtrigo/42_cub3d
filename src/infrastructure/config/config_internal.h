/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:53:15 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/18 16:56:41 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_INTERNAL_H
# define CONFIG_INTERNAL_H

# include <stdbool.h>
# include <stddef.h>

int		is_invalid_args(int argc, char *filename);
bool	is_invalid_extension(char *filename, size_t filename_len);
bool	is_invalid_file(char *filename);

#endif
