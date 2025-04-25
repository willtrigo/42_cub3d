/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_args_internal.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:14:05 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/22 12:14:51 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVALID_ARGS_INTERNAL_H
# define INVALID_ARGS_INTERNAL_H

# include <stdbool.h>
# include <stddef.h>

bool	is_invalid_extension(char *filename, size_t filename_len);

#endif
