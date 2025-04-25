/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_extension.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:13:28 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/22 12:13:55 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdbool.h>
#include <stddef.h>

bool	is_invalid_extension(char *filename, size_t filename_len)
{
	const char		*ext = ".cub";
	const size_t	ext_len = ft_strlen(ext);

	if (filename_len < ext_len)
		return (false);
	if (ft_strncmp(&filename[filename_len - ext_len], ext, ext_len))
		return (false);
	return (true);
}
