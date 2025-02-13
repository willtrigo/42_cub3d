/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extensions.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:49:41 by maurodri          #+#    #+#             */
/*   Updated: 2025/02/13 17:02:29 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXTENSIONS_H
# define FT_EXTENSIONS_H

# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>

bool	ft_is_blank(char *str);
size_t	ft_strarr_len(char **strarr);
bool	ft_atoi8_range(uint8_t *out_value, char *str, int range_low, int range_high);

#endif
